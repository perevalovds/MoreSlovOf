#include "Sea.h"
#include "gui_generated.h"
#include "ofxKuMessageLog.h"
#include "Common.h"

extern ofxKuTextGui gui;
Sea SEA;

//--------------------------------------------------------------
void Sea::setup() {
	words_.resize(PRM max_words);
	for (int i=0; i<words_.size(); i++) {
		words_[i].setup(i);
	}

	MACHINE.setup();

	PRM REC = 0;	//Techno1

	rec_state_.resize(maxTones);		//+1 - 7-� ������� ��� ����
}

//--------------------------------------------------------------
void Sea::update(float dt) {
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

	//����� - ��������� ����������
	for (auto &w : words_) {
		if (w.is_live()) {
			w.update();
		}
	}

	//�����
	MACHINE.update(dt);
}

//--------------------------------------------------------------
void Sea::draw() {
	//����� ����� �����-�����
	ofSetColor(128);
	float sepx = 1410.5 - 10;
	ofLine(sepx, 0, sepx, ofGetHeight()); //����� ����� �����-�����

}

//--------------------------------------------------------------
//�������� �����
//buffer � �������, ���� ������������ n
//pedal_index 0 - �����, 1 - �������
void Sea::push_word(const vector<float> &sound0, int n0, int pedal_index) {
	vector<float> sound;
	crop(sound0, n0, sound);	//��������� ���� ��������� ����������
	if (sound.empty()) return;

	//�������
	if (pedal_index == 1) {
		//if (PRM REP_REC) {
		SeaWordParam param;
		param.read_from_GUI();

		//���� "�������"
		bool found = false;
		for (auto &w : words_) {
			if (!w.is_live()) {
				w.run(sound0, n0, param);
				found = true;
				break;
			}
		}
		//�� ����� - ����� ����� ������������
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
		int BPM = PRM BPM * 2;	//�������� �� 2, ����� ���� ������� ����� �������� ������������				
		MACHINE.push_tone(i, sound, BPM);

		set_next_rec();	//������������� �� ��������� �������, ���� �� ������ �������

		/*for (int i = 0; i < maxTones; i++) {
			if (*gui.findVarStringList("REC" + ofToString(i + 1))) {
				int BPM = PRM BPM * 2;	//�������� �� 2, ����� ���� ������� ����� �������� ������������				
				MACHINE.push_tone(i, sound, BPM);
			}
		}*/
	}
}

//--------------------------------------------------------------
//�������� ����� - ����, ������ �������� ������, ���� �������� ������ � �����
void Sea::crop(const vector<float> &sound0, int n0, vector<float> &sound) {
	int mode = PRM Crop_Mode;

	int start = 0;
	int end = n0 - 1;
	if (mode == 0) { // off, ������ �� ���������
	}
	if (mode == 1) { // manual, �������� ������
		int cut_samples = PRM Crop_ms * SR / 1000;	
		start = cut_samples;
	}
	if (mode == 2) { // auto, ��������� ������ � ����� �� ����������� ������ �� ������������ ��������� 
		float max_v = 0.0001;
		for (auto &v : sound0) {
			max_v = max(max_v, fabs(v));
		}
		float thresh = max_v * PRM Crop_thresh / 100.0f;
		//������
		while (start < n0 && fabs(sound0[start] <= thresh)) {
			start++;
		}
		//�����
		while (end > start && fabs(sound0[end] <= thresh)) {
			end--;
		}

	}
	//���������
	int n = end+1-start;
	if (start >= n || n <= 1) {
		sound.clear();
		return;
	}
	sound.resize(n);
	for (int i = 0; i < n; i++) {
		sound[i] = sound0[start + i];
	}

	//����
	int fade = min(int(PRM Crop_fade_ms * SR / 1000), n/2);
	if (fade > 0) {
		for (int i = 0; i < fade; i++) {
			float f = float(i + 1) / fade;
			sound[i] *= f;
			sound[n-1-i] *= f;
		}
	}

	//��������� ����������� ���������
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
void Sea::set_next_rec() {	//����� �� ��������� �������, ���� �� ������ ������� ������ ������ Record Arm
	MLOG("next rec");
}

//--------------------------------------------------------------------------------
void Sea::update_rec_buttons() {	//������������ ����� ��� �������� ������� ������ �� ������


}

//--------------------------------------------------------------
