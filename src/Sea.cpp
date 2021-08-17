#include "Sea.h"
#include "gui_generated.h"
#include "ofxKuMessageLog.h"

Sea SEA;

//--------------------------------------------------------------
void Sea::setup() {
	words_.resize(PRM max_words);
	for (auto &w : words_) {
		w.setup();
	}
}

//--------------------------------------------------------------
void Sea::update() {
	//�������, ������� ���� ������������
	int count = 0;
	for (auto &w : words_) {
		if (w.is_live()) {
			count++;
		}
	}
	string s = ofToString(count) + " / " + ofToString(PRM max_words);
	if (count >= PRM max_words - 2) s += "  !!!!!";	//��������������
	PRM WORDS_ = s;
}

//--------------------------------------------------------------
void Sea::draw() {


}

//--------------------------------------------------------------
//�������� �����
//buffer � �������, ���� ����� n
void Sea::push_word(const vector<float> &sound, int n) {
	if (n <= 0) return;
	//���� "�������"
	bool found = false;
	for (auto &w : words_) {
		if (!w.is_live()) {
			w.run(sound, n);
			found = true;
			break;
		}
	}
	//�� ����� - ����� ����� ������������
	if (!found) {
		int k = ofRandom(words_.size());
		if (k >= 0 && k < words_.size()) {
			words_[k].run(sound, n);
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
