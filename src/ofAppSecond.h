#pragma once

#include "ofMain.h"

//������ ����� � ������������ ������� 1-6
class AppSecond: public ofBaseApp {
public:
	void setup();
	void set_screen_size(int x, int y, int w, int h);

	void update();
	void draw();

protected:
	ofTrueTypeFont font_;

	int n = 6;		//����� ������� ��� ���������, � 7-� - ��������
	float W_ = 100;
	float H_ = 100;
	float pos_x(int k);
	float get_w(int k);


};

extern AppSecond *APP_SECOND;

