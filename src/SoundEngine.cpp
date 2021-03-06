#include "SoundEngine.h"
#include "ofxKuMessageLog.h"
#include "gui_generated.h"
#include "ofxAudioFile.h"
#include "Common.h"
#include "Sea.h"

SoundEngine SOUND;

//--------------------------------------------------------------------------------
void SoundEngine::setup() {
	PRM vol_in_ = 0;
	PRM vol_out_ = 0;

	PRM SND_CALLB_ = "audioin:NO audioout:NO";

	//Pass thru
	pass_thru_buf_n = PRM sound_buffer * 2;
	pass_thru_buf_.resize(pass_thru_buf_n);

	PRM pass_thru_delta_ = "...";
	pass_write_pos_ = 0; //pass_thru_buf_n;// 0;
	pass_read_pos_ = 0;

	//Запись
	max_mic_rec_n_ = Common::max_mic_rec_n();
	mic_recording_.resize(max_mic_rec_n_);

	//Запись WAV
	recfile_setup();

	//Запуск звука
	start_stream();
}

//--------------------------------------------------------------------------------
void SoundEngine::exit() {
	ofSoundStreamClose();
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
	if (!in_ok) {
		if (device_in >= 0 && device_in < devices.size()) {
			auto &device = devices[device_in];
			MLOG("  Входное устройство " + device.name, "  Input device " + device.name);
			if (PRM in_channels > device.inputChannels) {
				MLOG("   Неверное число входов, требуется не менее *in_channels=" + ofToString(PRM in_channels) + ", имеется " + ofToString(device.inputChannels),
					"   Bad input channels, expected at least *in_channels=" + ofToString(PRM in_channels) + ", has " + ofToString(device.inputChannels),
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
		if (PRM out_channel_start - 1 + PRM out_channels > device.outputChannels) {
			MLOG("   Неверное число выходов, требуется не менее *out_channel_start - 1 + *out_channels = " + ofToString(PRM out_channel_start - 1 + PRM out_channels) + ", имеется " + ofToString(device.outputChannels),
			 	"   Bad output channels, expected at least *out_channel_start - 1 + *out_channels" + ofToString(PRM out_channel_start - 1 + PRM out_channels) + ", has " + ofToString(device.outputChannels),
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
		int sample_rate = SR;
		int buffer_size = Common::get_sound_buffer_size(PRM sound_buffer);
		int buffers = PRM sound_buffers;


		settings.sampleRate = sample_rate;
		settings.bufferSize = buffer_size;
		settings.numBuffers = buffers;
		soundStream.setup(settings);

		//Пишем, какой в итоге получился размер буфера (может ставиться звуковой картой в ее настройках)
		PRM sound_buffer_ = soundStream.getBufferSize();

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
	
	PRM RECFILE = wav_recfile_;		//чтобы пользователь только Shift+R запускал запись, а не мышкой

	PRM pass_thru_delta_ = ofToString(pass_write_pos_ - pass_read_pos_);

	//педаль
	//0 - техно, 1 - повторы, у техно - приоритет
	int pedal = PRM PEDAL_ || PRM PEDAL2_;

	//если идет запись повторов, но нажата техно - то остановить запись, чтобы в другом блоке запись техно
	if (mic_rec_on_ && pedal_index_ == 1 && PRM PEDAL_) {
		mic_rec_on_ = 0;
	}

	//начало записи
	if (!mic_rec_on_ && pedal) {	//start rec
		mic_rec_n_ = 0;
		mic_rec_on_ = 1;
		pedal_index_ = PRM PEDAL_?0:1;	//у техно - приоритет
	}
	else {
		//отпустили педаль, которая записывала
		if (mic_rec_on_ && ((pedal_index_ == 0 && !PRM PEDAL_) || (pedal_index_ == 1 && !PRM PEDAL2_))) {
			mic_rec_on_ = 0;
			SEA.push_word(mic_recording_, mic_rec_n_, pedal_index_);
			mic_rec_n_ = 0;
		}
	}


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

	int n = input.getNumFrames();
	int ch = input.getNumChannels();
	int IN_CH = PRM in_channels;
	if (n <= 0 || IN_CH <= 0) return;

		 
	float sum = 0; //RMS
	for (int c = 0; c < IN_CH; c++) {
		for (int i = 0; i < n; i++) {
			//меняем громкость микрофона
			auto &inp = input[i*ch + c];
			inp = min(max(inp, -1.0f), 1.0f);	//иногда попадает бесконечность в начале
			inp *= mic_vol;

			//фильтруем микрофон
			inp = mic_filter[c].process(inp, PRM mic_cutoff, PRM MIC_FILTER);
			sum += inp*inp;  //RMS
		}
	}
	//volume
	//float vol = input.getRMSAmplitude(); //реализовал сам
	float vol = sqrt(fabs(sum)) / (IN_CH * n);
	float &Vol = PRM vol_in_;
	Vol = max(Vol * 0.93f, vol);

	//pass thru
	for (int i = 0; i < n; i++) {
		pass_thru_buf_[pass_write_pos_ % pass_thru_buf_n] = input[i*ch];	//0-й канал
		pass_write_pos_++;
		//pass_write_pos_ %= pass_thru_buf_n;
	}

	//pedal recording
	if (mic_rec_on_) {
		int m = min(n, max_mic_rec_n_ - mic_rec_n_);	//смотрим, сколько дозаполнить
		for (int i = 0; i < m; i++) {
			mic_recording_[mic_rec_n_++] = input[i*ch];
		}
		//cout << mic_rec_n_ << " / " << max_mic_rec_n_ << endl;
	}

	//processing
	//DEMONS.audioIn(input);

}


//--------------------------------------------------------------
void SoundEngine::audioOut(ofSoundBuffer &output) {
	sound_out_called = 1;

	int n = output.getNumFrames();
	int ch = output.getNumChannels();
	int OUT_CH_START = PRM out_channel_start - 1;
	int OUT_CH = PRM out_channels;

	stereo_buffer_.resize(n * 2);
	fill(stereo_buffer_.begin(), stereo_buffer_.end(), 0);
	float vol_pass = PRM PASS_VOL;
	float vol_sea = PRM SEA_VOL;

	//звуки моря слов, также добавляют send в эффекты
	SEA.audioOut(stereo_buffer_, n);
	for (auto &v : stereo_buffer_) {
		v *= vol_sea;		//Громкость
	}

	//добавляем звук с микрофона
	if (pass_read_pos_ + n > pass_write_pos_) {
		cout << "WARNING: PASS_THRU read buffer " << pass_read_pos_ << " can be further than write " << pass_write_pos_ << endl;
	}
	
	for (int i = 0; i < n; i++) {
		float mic = pass_thru_buf_[pass_read_pos_ % pass_thru_buf_n] * vol_pass;
		pass_read_pos_++;

		//запись WAV
		if (wav_recfile_) {
			wav_write_sound_sample(mic, stereo_buffer_[i * 2], stereo_buffer_[i * 2 + 1]);
		}

		//отправка микрофона в микс
		if (PRM PASS_THRU) {
			stereo_buffer_[i * 2] = stereo_buffer_[i * 2 + 1] += mic;
		}
	}
	
	/*else {
		pass_read_pos_ += n;

		//запись WAV
		if (wav_recfile_) {
			float mic = 0;
			for (int i = 0; i < n; i++) {
				wav_write_sound_sample(mic, stereo_buffer_[i * 2], stereo_buffer_[i * 2 + 1]);
			}
		}
	}*/

	//заполнение выхода
	float out_vol = PRM OUT_VOL;
	for (int i = 0; i < n; i++) {
		for (int c = 0; c < OUT_CH; c++) {
			output[i*ch + OUT_CH_START + c] += stereo_buffer_[i*2 + c%2] * out_vol;
		}
	}


	//volume
	float vol = output.getRMSAmplitude();
	float &Vol = PRM vol_out_;
	Vol = max(Vol * 0.93f, vol);

}

//--------------------------------------------------------------------------------
bool SoundEngine::toggleFileRecording() {	//запись в WAV
	wav_recfile_ = !wav_recfile_;
	PRM RECFILE = wav_recfile_;

	if (wav_recfile_) {
		recfile_start();
	}
	else {
		recfile_stop();
	}

	return wav_recfile_;

}

//--------------------------------------------------------------------------------
void SoundEngine::recfile_setup() {
	PRM RECFILE = 0;
	wav_recfile_ = 0;

	wavpos_ = 0;

	wav_duration_samples = SR * wav_duration_sec * 2;

	wavmic_.resize(wav_duration_samples);
	wavsnd_.resize(wav_duration_samples);
}

//--------------------------------------------------------------------------------
void SoundEngine::recfile_start() {
	wavpos_ = 0;
	wav_file_name_ = ofGetTimestampString("%Y_%m_%d-%H%M%S");
}

//--------------------------------------------------------------------------------
void SoundEngine::recfile_stop() { //Внимание, после этой функции  wavsnd_ портится - в него пишем микс

	if (wavpos_ <= 0) return;
	string file_mic = "temp/" + wav_file_name_ + "_mic.wav";
	string file_snd = "temp/" + wav_file_name_ + "_snd.wav";
	string file_mix = "temp/" + wav_file_name_ + "_xmix.wav";
	ofxAudioFile::save_wav_16bit_stereo(ofToDataPath(file_mic), wavmic_.data(), wavpos_);
	ofxAudioFile::save_wav_16bit_stereo(ofToDataPath(file_snd), wavsnd_.data(), wavpos_);

	//микс - пишем в snd, чтобы не выделять память
	for (int i = 0; i < wavpos_; i++) {
		int v = int(wavmic_[i]) + int(wavsnd_[i]);
		wavsnd_[i] = min(max(v, -32767), 32767);
	}
	ofxAudioFile::save_wav_16bit_stereo(ofToDataPath(file_mix), wavsnd_.data(), wavpos_);

	cout << "Saved " << "temp/" + wav_file_name_ << endl;
}

//--------------------------------------------------------------------------------
//уменьшаем громкость - чтобы не было перегрузки в WAV
const float wav_decrease_vol = 4.0f;
#define FLOAT_TO_SHORT_DECVOL(x) (min(max(int(x*32767.0f / wav_decrease_vol), -32767),32767))


void SoundEngine::wav_write_sound_sample(float mic, float sndL, float sndR) {
	if (wavpos_ >= wav_duration_samples) return;
	wavmic_[wavpos_] = wavmic_[wavpos_ + 1] = FLOAT_TO_SHORT_DECVOL(mic);
	wavsnd_[wavpos_] = FLOAT_TO_SHORT_DECVOL(sndL);
	wavpos_++;
	wavsnd_[wavpos_] = FLOAT_TO_SHORT_DECVOL(sndR);
	wavpos_++;
}

//--------------------------------------------------------------------------------
