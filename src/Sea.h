#pragma once

//Sea of words
#include "ofMain.h"
#include "SeaWord.h"
#include "Machines.h"

struct Sea {
	void setup();
	void update(float dt);
	void draw();

	//�������� �����
	//buffer � �������, ���� ������������ n
	void push_word(const vector<float> &sound, int n);

	//����
	void audioOut(vector<float> &stereo_buffer, int n);
protected:
	vector<SeaWord> words_;	//������� ���� ���, ����� �������� ����� ��� ������ ���������
};


extern Sea SEA;