#pragma once

//Sea of words
#include "ofMain.h"
#include "SeaWord.h"

struct Sea {
	void setup();
	void update();
	void draw();

	//добавить слово
	//buffer с запасом, надо использовать n
	void push_word(const vector<float> &sound, int n);

	//звук
	void audioOut(vector<float> stereo_buffer, int n);
protected:
	vector<SeaWord> words_;	//создаем один раз, чтобы звуковой потом мог всегда считывать
};


extern Sea SEA;