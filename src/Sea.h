#pragma once

//Sea of words
#include "ofMain.h"

struct Sea {
	void setup();
	void update();
	void draw();

	//�������� �����
	//buffer � �������, ���� ����� n
	void push_word(const vector<float> &buffer, int n);
};


extern Sea SEA;