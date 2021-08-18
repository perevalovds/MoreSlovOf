#include "Sea.h"
#include "gui_generated.h"
#include "ofxKuMessageLog.h"

extern ofxKuTextGui gui;
Sea SEA;

//--------------------------------------------------------------
void Sea::setup() {
	words_.resize(PRM max_words);
	for (int i=0; i<words_.size(); i++) {
		words_[i].setup(i);
	}

	MACHINE.setup();
}

//--------------------------------------------------------------
void Sea::update(float dt) {
	//выводим, сколько слов используется
	int count = 0;
	for (auto &w : words_) {
		if (w.is_live()) {
			count++;
		}
	}
	string s = ofToString(count) + " / " + ofToString(PRM max_words);
	if (count >= PRM max_words - 2) s += "  !!!!!";	//предупреждение
	PRM WORDS_ = s;

	//слова - генерация построений
	for (auto &w : words_) {
		if (w.is_live()) {
			w.update();
		}
	}

	//техно
	MACHINE.update(dt);
}

//--------------------------------------------------------------
void Sea::draw() {


}

//--------------------------------------------------------------
//добавить слово
//buffer с запасом, надо использовать n
//pedal_index 0 - техно, 1 - повторы
void Sea::push_word(const vector<float> &sound0, int n0, int pedal_index) {
	vector<float> sound;
	crop(sound0, n0, sound);	//подрезаем звук выбранным алгоритмом
	if (sound.empty()) return;

	//Повторы
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
		for (int i = 0; i < maxTones; i++) {
			if (*gui.findVarStringList("REC" + ofToString(i + 1))) {
				int BPM = PRM BPM * 2;	//умножаем на 2, чтобы были быстрее самые короткие длительности				
				MACHINE.push_tone(i, sound, BPM);
			}
		}
	}
}

//--------------------------------------------------------------
//подрезка звука - выкл, ручная подрезка начала, авто подрезка начала и конца
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
	if (mode == 2) { // auto, вычисляем начало и конец по адаптивному порогу от максимальной амплитуды 
		float max_v = 0.0001;
		for (auto &v : sound0) {
			max_v = max(max_v, fabs(v));
		}
		float thresh = max_v * PRM Crop_thresh / 100.0f;
		//начало
		while (start < n0 && fabs(sound0[start] <= thresh)) {
			start++;
		}
		//конец
		while (end > start && fabs(sound0[end] <= thresh)) {
			end--;
		}

	}
	//подрезаем
	int n = end+1-start;
	if (start >= n || n <= 1) {
		sound.clear();
		return;
	}
	sound.resize(n);
	for (int i = 0; i < n; i++) {
		sound[i] = sound0[start + i];
	}
}

//--------------------------------------------------------------
void Sea::audioOut(vector<float> &stereo_buffer, int n) {

	StereoSample mach_sample;
	for (int i = 0; i < n; i++) {
		MACHINE.audioOut(mach_sample);
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
