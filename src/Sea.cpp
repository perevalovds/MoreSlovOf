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
//sound с запасом, надо взять n, а также отрезаем начало
void Sea::push_word(const vector<float> &sound0, int n0) {

	if (n0 <= 0) return;

	//Повторы - без подрезания
	if (PRM REP_REC) {
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
	//Techno - подрезаем
	int cut_samples = PRM Rec_Cut_ms * SR / 1000;	//сколько отрезать в начале
	int n = n0 - cut_samples;
	if (n <= 0) return;
	vector<float> sound(n);
	for (int i = 0; i < n; i++) {
		sound[i] = sound0[i + cut_samples];
	}

	//Вставляем
	for (int i=0; i<maxTones; i++) {
		if (*gui.findVarStringList("REC" + ofToString(i+1))) {
			int BPM = PRM BPM * 2;	//умножаем на 2, чтобы были быстрее самые короткие длительности
			auto sound1 = sound;
			sound1.resize(n);
			MACHINE.push_tone(i, sound1, BPM);
		}
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
