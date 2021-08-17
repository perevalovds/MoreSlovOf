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
	int k = ofRandom(words_.size());
	if (k >= 0 && k < words_.size()) {
		words_[k].run(sound, n);
	}
}

//--------------------------------------------------------------
