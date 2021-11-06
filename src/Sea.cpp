#include "Sea.h"
#include "gui_generated.h"
#include "ofxKuMessageLog.h"
#include "Common.h"
#include "Morph.h"
#include "SoundFX.h"

extern ofxKuTextGui gui;
Sea SEA;

//--------------------------------------------------------------
void Sea::setup() {
	words_.resize(PRM max_words);
	for (int i=0; i<words_.size(); i++) {
		words_[i].setup(i);
	}

	MACHINE.setup();
	MORPH.setup();

	//Ёффекты
	SOUNDFX.setup();

	recbuttons_setup();
}

//--------------------------------------------------------------
void Sea::update(float dt) {
	//выводим, сколько слов используетс€
	int count = 0;
	for (auto &w : words_) {
		if (w.is_live()) {
			count++;
		}
	}
	string s = ofToString(count) + " / " + ofToString(PRM max_words);
	if (count >= PRM max_words - 2) s += "  !!!!!";	//предупреждение
	PRM WORDS_ = s;

	//слова - генераци€ построений
	for (auto &w : words_) {
		if (w.is_live()) {
			w.update();
		}
	}

	//Ёффекты
	SOUNDFX.update();

	//техно
	recbuttons_update();
	MACHINE.update(dt);

	//load recorded samples
	if (PRM load1) load_sample(0);
	if (PRM load2) load_sample(1);
	if (PRM load3) load_sample(2);
	if (PRM load4) load_sample(3);
	if (PRM load5) load_sample(4);
	if (PRM load6) load_sample(5);
}

//--------------------------------------------------------------
void Sea::draw() {
	//лини€ после техно-машин
	ofSetColor(128);
	float sepx = PRM thumb_x7 + 0.5 - 10;
	ofLine(sepx, 0, sepx, ofGetHeight()); //лини€ после техно-машин

	//звуки
	MACHINE.draw_thumbs();

	//backups
	auto *tone = MACHINE.tone[maxTones_part1];
	if (tone) {
		tone->draw_backups(PRM backup_x, PRM backup_y);
	}
	
}

//--------------------------------------------------------------
//добавить слово
//buffer с запасом, надо использовать n
//pedal_index 0 - техно, 1 - повторы
void Sea::push_word(const vector<float> &sound0, int n0, int pedal_index) {
	vector<float> sound;
	crop(sound0, n0, sound);	//подрезаем звук выбранным алгоритмом
	if (sound.empty()) return;

	//ѕовторы
	if (pedal_index == 1) {
		//if (PRM REP_REC) {
		SeaWordParam param;
		param.read_from_GUI();

		//ищем "умерший"
		bool found = false;
		for (auto &w : words_) {
			if (!w.is_live()) {
				w.run(sound0, n0, param);
				found = true;
				break;
			}
		}
		//не нашли - тогда берем произвольное
		if (!found) {
			int k = ofRandom(words_.size());
			if (k >= 0 && k < words_.size()) {
				words_[k].run(sound0, n0, param);
			}
		}

	}
	else {
		//Techno 
		int i = PRM REC;
		//int BPM = PRM BPM * 2;	//умножаем на 2, чтобы были быстрее самые короткие длительности				
		MACHINE.push_tone(i, sound);

		recbuttons_set_next();	//переключаемс€ на следующую дорожку, если не нажата красна€

		/*for (int i = 0; i < maxTones; i++) {
			if (*gui.findVarStringList("REC" + ofToString(i + 1))) {
				int BPM = PRM BPM * 2;	//умножаем на 2, чтобы были быстрее самые короткие длительности				
				MACHINE.push_tone(i, sound, BPM);
			}
		}*/
	}
}

//--------------------------------------------------------------
//подрезка звука - выкл, ручна€ подрезка начала, авто подрезка начала и конца
void Sea::crop(const vector<float> &sound0, int n0, vector<float> &sound) {
	int mode = PRM Crop_Mode;

	int start = 0;
	int end = n0 - 1;
	if (mode == 0) { // off, ничего не подрезаем
	}
	if (mode == 1) { // manual, отрезаем начало
		int cut_samples = PRM Crop_ms * SR / 1000;	
		start = cut_samples;
	}
	if (mode == 2) { // auto, вычисл€ем начало и конец по адаптивному порогу от максимальной амплитуды 
		float max_v = 0.0001;
		for (auto &v : sound0) {
			max_v = max(max_v, fabs(v));
		}
		float thresh = max_v * PRM Crop_thresh / 100.0f;
		//начало
		while (start < n0 && fabs(sound0[start]) <= thresh) {
			start++;
		}
		//конец
		while (end > start && fabs(sound0[end]) <= thresh) {
			end--;
		}

	}
	//подрезаем
	int n = end+1-start;
	if (start >= n0 || n <= 1) {
		sound.clear();
		return;
	}
	sound.resize(n);
	for (int i = 0; i < n; i++) {
		sound[i] = sound0[start + i];
	}

	//фейд
	int fade = min(int(PRM Crop_fade_ms * SR / 1000), n/2);
	if (fade > 0) {
		for (int i = 0; i < fade; i++) {
			float f = float(i + 1) / fade;
			sound[i] *= f;
			sound[n-1-i] *= f;
		}
	}

	//повышение минимальной громкости
	float min_vol = PRM Min_Vol;
	if (min_vol > 0) {
		float max_v = 0.0001;
		for (auto &v : sound) {
			max_v = max(max_v, fabs(v));
		}
		if (max_v < min_vol) {
			float koef = min_vol / max_v;
			for (auto &v : sound) {
				v *= koef;
			}
		}
	}
}

//--------------------------------------------------------------
void Sea::audioOut(vector<float> &stereo_buffer, int n) {


	StereoSample mach_sample;
	for (int i = 0; i < n; i++) {
		SOUNDFX.send_clear();	//очистка сэмпла эффектов
		MACHINE.audioOut(mach_sample);	//генераци€ звука, а также отправка на эффекты
		SOUNDFX.process_add(mach_sample); //добавление эффекта в микс

		stereo_buffer[2 * i] += mach_sample.L;
		stereo_buffer[2 * i + 1] += mach_sample.R;
	}
	for (auto &w : words_) {
		if (w.is_live()) {
			w.audioOut(stereo_buffer, n);
		}
	}
	
}

//--------------------------------------------------------------
void Sea::recbuttons_setup() {
	PRM REC = maxTones-1;	//Techno6, и чтобы сразу перешел на Techno1

	//считываем указатели из GUI дл€ удобства использовани€
	rec_gui_.resize(maxTones);
	for (int i = 0; i < maxTones; i++) {
		rec_gui_[i] = gui.findVarStringList("REC" + ofToString(i + 1));
	}

	rec_state_.resize(maxTones,-1);		
}

//--------------------------------------------------------------
void Sea::recbuttons_update() {	//обновить GUI кнопки записи и номер дорожки дл€ записи
	int pressed_id = -1;	//кака€ только что нажата
	//bool unpressed = false;	//кака€-то только что отжата
	int is_pressed_id = -1;	//в целом есть нажата€

	int rec_last = PRM REC;
	bool rec_was_released = false;

	for (int i = 0; i < maxTones; i++) {
		if (*rec_gui_[i] != rec_state_[i]) {
			auto &v = rec_state_[i];
			v = *rec_gui_[i];
			if (v) pressed_id = i;
			else {
				if (i == rec_last) {
					rec_was_released = true;	//была отпущена та, где REC
				}
			}
		}

		//если есть нажата€ - первую запомним
		if (rec_state_[i] && is_pressed_id == -1) {
			is_pressed_id = i;
		}
	}
	//если была кака€-то нажата - то это REC
	if (pressed_id >= 0) PRM REC = pressed_id;
	else {
		//иначе текуща€ отжата - если есть другие нажатые, то поставить самую первую из них
		if (rec_was_released) {
			if (is_pressed_id >= 0) {
				PRM REC = is_pressed_id;
			}
			else {
				//а иначе - следующую
				recbuttons_set_next();
			}
		}
	}
	
}

//--------------------------------------------------------------
void Sea::recbuttons_set_next() {	//сдвиг на следующую дорожку, если не нажата красна€ кнопка пульта Record Arm
	if (PRM Auto_Rec_Next) {
		int &v = PRM REC;
		if (rec_state_[v] == 0) {	//вообще нет нажатых
			v++;
			v %= maxTones_part1;	//скидываем из 7 в 0
			v %= (maxTones_part1 - 1);	//-1 так как последн€€ не должна записыватьс€ автоматически
		}
	}
}

//--------------------------------------------------------------
//загрузить сэмпл из предзаписанных в заданную дорожку
void Sea::load_sample(int i) {
	int k = maxTones_part1 + PRM load_to;
	x_assert(k >= 0 && k < maxTones, "Sea::load_sample error - wrong track " + ofToString(k));
	auto *tone = MACHINE.tone[k];
	if (tone) {
		tone->load_sample(i);
	}
}

//--------------------------------------------------------------
