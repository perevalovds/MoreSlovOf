#pragma once

//Sea of words
#include "ofMain.h"

struct Sea {
	void setup();
	void update();
	void draw();

	//добавить слово
	//buffer с запасом, надо взять n
	void push_word(const vector<float> &buffer, int n);
};


extern Sea SEA;