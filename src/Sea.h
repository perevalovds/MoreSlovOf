#pragma once

//Sea of words
#include "ofMain.h"
#include "Common.h"
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

	//����� ������� ��� ������
	void recbuttons_setup();
	void recbuttons_update();	//�������� GUI ������ ������ � ����� ������� ��� ������
	void recbuttons_set_next();	//����� �� ��������� �������, ���� �� ������ ������� ������ ������ Record Arm

	vector<int*> rec_gui_;	//�������� REC1..7
	vector<int> rec_state_;	//��������� ��������� ������

	void load_sample(int i);	//��������� ����� �� �������������� � �������� �������
};


extern Sea SEA;