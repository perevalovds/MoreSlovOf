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
	//pedal_index 0 - �����, 1 - �������
	void push_word(const vector<float> &sound, int n, int pedal_index);

	//����
	void audioOut(vector<float> &stereo_buffer, int n);
protected:
	vector<SeaWord> words_;	//������� ���� ���, ����� �������� ����� ��� ������ ���������

	//�������� ����� - ����, ������ �������� ������, ���� �������� ������ � �����
	void crop(const vector<float> &sound0, int n, vector<float> &sound);
};


extern Sea SEA;