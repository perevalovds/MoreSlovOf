#pragma once

#include "ofMain.h"

//Второй экран с изображением семплов 1-6
class AppSecond: public ofBaseApp {
public:
	void setup();
	void set_screen_size(int x, int y, int w, int h);

	void update();
	void draw();


};

extern AppSecond *APP_SECOND;

