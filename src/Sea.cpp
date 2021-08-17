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
}

//--------------------------------------------------------------
void Sea::update() {
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
}

//--------------------------------------------------------------
void Sea::draw() {


}

//--------------------------------------------------------------
//добавить слово
//buffer с запасом, надо взять n
void Sea::push_word(const vector<float> &sound, int n) {
	if (n <= 0) return;

	//параметры
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

//--------------------------------------------------------------
void Sea::audioOut(vector<float> &stereo_buffer, int n) {
	for (auto &w : words_) {
		if (w.is_live()) {
			w.audioOut(stereo_buffer, n);
		}
	}

}

//--------------------------------------------------------------
