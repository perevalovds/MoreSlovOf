#include "SoundEngine.h"
#include "ofxKuMessageLog.h"
#include "gui_generated.h"
#include "ofxAudioFile.h"
#include "Common.h"

SoundEngine SOUND;

//--------------------------------------------------------------------------------
void SoundEngine::setup() {
	PRM vol_in_ = 0;
	PRM vol_out_ = 0;

	PRM SND_CALLB_ = "audioin:NO audioout:NO";

	start_stream();
}

//--------------------------------------------------------------------------------
void SoundEngine::exit() {
	ofSoundStreamClose();
}

//--------------------------------------------------------------------------------
bool SoundEngine::setup_emulation_in() {
	emulation_in = 0;

	if (!PRM EMULATE_IN) {
		return false;
	}

	int in_ch = PRM in_channels;
	string file_name = "sounds/emulate_in" + ofToString(in_ch) + ".wav";
	MLOG("  Эмуляция микрофона из файла " + file_name,
		"Mic emulation from " + file_name, ofColor(255, 255, 0));
	ofxAudioFile audiofile;

	if (!ofFile::doesFileExist(file_name)) {
		MLOG("   Нет файла", "   No file", ofColor(255, 0, 0));
		return false;
	}

	audiofile.load(ofToDataPath(file_name));
	if (!audiofile.loaded()) {
		MLOG("   Ошибка загрузки файла", "   Error loading file", ofColor(255, 0, 0));
		return false;
	}

	int channels = audiofile.channels();

	if (audiofile.channels() != in_ch) {
		MLOG("   Ошибка загрузки файла, неверное число каналов: " + ofToString(channels),
			"   Error loading file, bad channels count: " + ofToString(channels),
			ofColor(255, 0, 0));
		return false;
	}


	//считывание данных
	int n = audiofile.length();
	int ch = audiofile.channels();

	emulation_data.resize(n * ch);
	for (int i = 0; i < n; i++) {
		for (int c = 0; c < ch; c++) {
			emulation_data[i*ch + c] = audiofile.sample(i, c);
		}
	}

	emulation_in = 1;
	return true;
}

//--------------------------------------------------------------------------------
//поисе устройства по заданной строке вида namepart:portsin:out
int SoundEngine::find_device_by_string(const string &nameports, vector<ofSoundDevice> &devices) {
	//разбор строки
	vector<string> items = ofSplitString(nameports, ":", false, true);
	if (items.size() < 3) {
		MLOG("Некорректное описание зв. устр. '" + nameports + "', ожидается частьимени:входов:выходов",
			"Incorrect description of sound device '" + nameports + "', expected namepart:portsin:out",
			ofColor(255, 0, 0));
	}
	string namepart = items[0];
	int ports_in = ofToInt(items[1]);
	int ports_out = ofToInt(items[2]);
	for (int i = 0; i < devices.size(); i++) {
		auto &device = devices[i];
		if ((namepart.empty() || ofStringTimesInString(device.name, namepart) > 0)
			&& device.inputChannels == ports_in && device.outputChannels == ports_out) {
			return i;
		}
	}
	return -1;

}

//--------------------------------------------------------------------------------
void SoundEngine::start_stream() {
	show_devices();

	MLOG("Запуск звука...", "Starting sound...", ofColor(255));
	int api_id = Common::get_api_id(PRM _engine_);
	string api_name = Common::get_api_name(PRM _engine_);
	ofColor color(255, 255, 140);
	auto devices = soundStream.getDeviceList(ofSoundDevice::Api(api_id));

	ofSoundStreamSettings settings;

	bool emulate = setup_emulation_in();

	//выбор ID
	int device_in = PRM device_in;
	int device_out = PRM device_out;
	//запускать устройства по имени
	if (PRM selectby == 1) {	//NAME
		device_in = find_device_by_string(PRM devin_nameports, devices);
		device_out = find_device_by_string(PRM devout_nameports, devices);
	}

	//Вход
	bool in_ok = false;
	if (emulate) {
		in_ok = true;
		PRM device_in_name_ = "emulation";
		in_started_ = 1;
	}
	if (!in_ok) {
		if (device_in >= 0 && device_in < devices.size()) {
			auto &device = devices[device_in];
			MLOG("  Входное устройство " + device.name, "  Input device " + device.name);
			if (PRM in_channels != device.inputChannels) {
				MLOG("   Неверное число входов, требуется *in_channels=" + ofToString(PRM in_channels) + ", имеется " + ofToString(device.inputChannels),
					"   Bad input channels, expected *in_channels=" + ofToString(PRM in_channels) + ", has " + ofToString(device.inputChannels),
					ofColor(255, 0, 0));
			}
			else {
				PRM device_in_name_ = device.name;
				in_started_ = 1;
				settings.setInDevice(device);
				settings.setInListener(this);
				settings.numInputChannels = PRM in_channels;

				in_ok = true;
			}
		}
	}
	
	if (!in_ok) {
		MLOG("Входное устройство не запущено - нет устройства с id *device_in=" + ofToString(device_in), 
			"Input device is not started - no device with id *device_in=" + ofToString(device_in), ofColor(255, 0, 0));
		PRM device_in_name_ = "---";
		in_started_ = 0;
	}

	//Выход
	bool out_ok = false;
	if (device_out >= 0 && device_out < devices.size()) {
		auto &device = devices[device_out];
		MLOG("  Выходное устройство " + device.name, "  Output device " + device.name);
		if (PRM out_channels != device.outputChannels) {
			MLOG("   Неверное число выходов, требуется *out_channels=" + ofToString(PRM out_channels) + ", имеется " + ofToString(device.outputChannels),
			 	"   Bad output channels, expected *out_channels=" + ofToString(PRM out_channels) + ", has " + ofToString(device.outputChannels),
				ofColor(255, 0, 0));
		}
		else {
			PRM device_out_name_ = device.name;
			out_started_ = 1;
			settings.setOutDevice(device);
			settings.setOutListener(this);
			settings.numOutputChannels = PRM out_channels;

			out_ok = true;
		}
	}
	if (!out_ok) {
		MLOG("Выходное устройство не запущено - нет устройства с id *device_out=" + ofToString(device_out),
			"Output device is not started - no device with id *device_out=" + ofToString(device_out), ofColor(255, 0, 0));
		PRM device_out_name_ = "---";
		out_started_ = 0;
	}

	started_ = in_started_ && out_started_;
	PRM SOUND_STATUS_ = started_;

	if (started_) {
		int sample_rate = Common::sample_rate();
		int buffer_size = Common::get_sound_buffer_size(PRM sound_buffer);
		int buffers = PRM sound_buffers;


		settings.sampleRate = sample_rate;
		settings.bufferSize = buffer_size;
		settings.numBuffers = buffers;
		soundStream.setup(settings);

		std::ostringstream out_ru, out_en;
		out_ru << "Звук запущен " << PRM in_channels << ":" << PRM out_channels 
			<< "   " << sample_rate << "   " << buffers << "," << buffer_size;
		out_en << "Sound is started " << PRM in_channels << ":" << PRM out_channels
			<< "   " << sample_rate << "   " << buffers << "," << buffer_size;
		MLOG(out_ru.str(), out_en.str(), ofColor(0,255,0));
	}
	else {
		MLOG("Звук не запущен, проверьте настройки звука на странице Sound", 
			"Sound is not started, check sound settings at Sound page", ofColor(255, 0, 0));
	}

}

//--------------------------------------------------------------------------------
void SoundEngine::show_devices() {
	int api_id = Common::get_api_id(PRM _engine_);
	string api_name = Common::get_api_name(PRM _engine_);
	ofColor color(255, 255, 140);
	MLOG("");
	MLOG("Звуковые устройства (" + api_name + "):", color);

	//soundStream.printDeviceList();
	auto devices = soundStream.getDeviceList(ofSoundDevice::Api(api_id));
	for (int i = 0; i < devices.size(); i++) {
		std::ostringstream str1, str2;
		str1 << "  " << i << ": " << devices[i].name;
		str2 << "         входов: " << devices[i].inputChannels << ", выходов: " << devices[i].outputChannels;
		//разбил на две строки - так как в первой, если не-латиница, то не выдает на экран
		MLOG(str1.str(), color);
		MLOG(str2.str());
	}
}

//--------------------------------------------------------------------------------
string SoundEngine::callbacks_status_string() { //информация о callbacks - были или нет
	return string("audioin:") + string((sound_in_called) ? "yes" : "NO!")
		+ string(" audioout:") + string((sound_out_called) ? "yes" : "NO!");
}

//--------------------------------------------------------------------------------
void SoundEngine::update() {
	if (PRM ShowDevices) {
		show_devices();
	}

	PRM SND_CALLB_ = callbacks_status_string();
	//if (key == ' ') {
	//	recording = 1;
	//	recorded = 0;
	//	record_pos = 0;
	//}
}

//--------------------------------------------------------------------------------
void SoundEngine::draw() {

	/*ofSetColor(225);
	ofDrawBitmapString("press ' ' to record 1 second sample and constantly replay it", 20, 40);

	std::ostringstream str;
	str << "sound_in_called: " << sound_in_called << ", sound_out_called " << sound_out_called << endl;
	str << "input volume: " << in_volume << endl;
	str << "recording: " << recording << " (press Space to record)" << endl;
	str << "playing: " << recorded << endl;
	ofDrawBitmapString(str.str(), 20, 70);
	*/

}

//--------------------------------------------------------------
void SoundEngine::audioIn(ofSoundBuffer &input) {
	sound_in_called = 1;
	
	float &mic_vol = PRM MIC_VOL;

	//коррекция громкости микрофона
	int n = input.getNumFrames();
	int ch = input.getNumChannels();
	for (int c = 0; c < ch; c++) {
		for (int i = 0; i < n; i++) {
			//меняем громкость микрофона
			auto &inp = input[i*ch + c];
			inp *= mic_vol;

			//фильтруем микрофон
			inp = mic_filter[c].process(inp, PRM infilter_cutoff, PRM INFILTER);
		}
	}
	//volume
	float vol = input.getRMSAmplitude();
	float &Vol = PRM vol_in_;
	Vol = max(Vol * 0.93f, vol);

	//processing
	//DEMONS.audioIn(input);

}


//--------------------------------------------------------------
void SoundEngine::audioOut(ofSoundBuffer &output) {
	//в режиме эмуляции, мы делаем вид, что пришли данные такой же длины, как output
	emulate_in_perform(output);

	sound_out_called = 1;

	//TEST прямо тут отправляем данные с эмуляции в колонки
	if (PRM PASS_THRU) {
		if (emulation_in) {
			//из считанного эмуляционного буфера
			//int n = output.getNumFrames();
			//int in_ch = PRM in_channels;
			//int out_ch = PRM out_channels;
			//for (int i = 0; i < n; i++) {
			//	for (int c = 0; c < out_ch; c++) {
			//		output[i*out_ch + c] = emulate_buffer[i*in_ch + 0];	//только один канал звука посылаем	
			//	}
			//}
			//return;

			//прямо из исходного буфера
			//int n = output.getNumFrames();
			//int in_ch = PRM in_channels;
			//int out_ch = PRM out_channels;
			//int emu_size = emulation_data.size();
			//static int emu_pos = 0;		//ВНИМАНИЕ!!! статичная переменная
			//for (int i = 0; i < n; i++) {
			//	for (int c = 0; c < out_ch; c++) {
			//		output[i*out_ch + c] = emulation_data[emu_pos + 0];	//только один канал звука посылаем
			//	}
			//	emu_pos += in_ch;
			//	emu_pos %= emu_size;
			//}
			//return;
		}
	}

	//processing
	//DEMONS.audioOut(output);

	//volume
	float vol = output.getRMSAmplitude();
	float &Vol = PRM vol_out_;
	Vol = max(Vol * 0.93f, vol);

}


//--------------------------------------------------------------------------------
//при эмуляции мы посылаем на audioIn данные по столько же, как приходит в audioOut
void SoundEngine::emulate_in_perform(const ofSoundBuffer &such_this_buffer) {
	if (emulation_in) {
		int n = such_this_buffer.getNumFrames();
		int in_ch = PRM in_channels;
		int emu_size = emulation_data.size();
		emulate_buffer.allocate(n, in_ch);

		emulation_pos %= emu_size;
		for (int i = 0; i < n*in_ch; i++) {
			emulate_buffer[i] = emulation_data[emulation_pos++] * PRM emulate_vol;
			emulation_pos %= emu_size;
		}
		audioIn(emulate_buffer);
	}
}

//--------------------------------------------------------------------------------
