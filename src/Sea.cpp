#include "Sea.h"
#include "gui_generated.h"
#include "ofxKuMessageLog.h"

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
//buffer с запасом, надо взять n
void Sea::push_word(const vector<float> &sound, int n) {
	if (n <= 0) return;

	//выбор, куда
	int destination = PRM REC;	//0 - sea, 1,2,3,4,5,6 - techno1..6

	if (destination == 0) {
		//Sea
		SeaWordParam param;
		param.read_from_GUI();

		//ищем "умерший"
		bool found = false;
		for (auto &w : words_) {
			if (!w.is_live()) {
				w.run(sound, n, param);
				found = true;
				break;
			}
		}
		//не нашли - тогда берем произвольное
		if (!found) {
			int k = ofRandom(words_.size());
			if (k >= 0 && k < words_.size()) {
				words_[k].run(sound, n, param);
			}
		}
	}
	else {
		//Techno
		int BPM = 120;

		int i = destination - 1;
		if (i < maxTones) {
			auto sound1 = sound;
			sound1.resize(n);
			MACHINE.push_tone(i, 0, sound1, BPM);
		}
	}
}

//--------------------------------------------------------------
void Sea::audioOut(vector<float> &stereo_buffer, int n) {
	vector<float> mach(maxTones * 2);
	float vol = 1;
	for (int i = 0; i < n; i++) {
		MACHINE.audioOut(&mach[0], vol);
		stereo_buffer[2 * i] += mach[0];
		stereo_buffer[2 * i + 1] += mach[1];
	}
	for (auto &w : words_) {
		if (w.is_live()) {
			w.audioOut(stereo_buffer, n);
		}
	}
	
}

//--------------------------------------------------------------
