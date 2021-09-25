#pragma once

#include "ofMain.h"

//Второй экран с изображением семплов 1-6
class AppSecond: public ofBaseApp {
public:
	void setup();
	void set_screen_size(int x, int y, int w, int h);

	void update();
	void draw();

protected:
	ofTrueTypeFont font_;

	int n = 6;		//число дорожек для рисования, и 7-я - частично
	float W_ = 100;
	float H_ = 100;
	float pos_x(int k);
	float get_w(int k);


};

extern AppSecond *APP_SECOND;

