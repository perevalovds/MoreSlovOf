#pragma once

//Sea of words
#include "ofMain.h"
#include "SeaWord.h"
#include "Machines.h"

struct Sea {
	void setup();
	void update(float dt);
	void draw();

	//добавить слово
	//buffer с запасом, надо использовать n
	//pedal_index 0 - техно, 1 - повторы
	void push_word(const vector<float> &sound, int n, int pedal_index);

	//звук
	void audioOut(vector<float> &stereo_buffer, int n);
protected:
	vector<SeaWord> words_;	//создаем один раз, чтобы звуковой потом мог всегда считывать

	//подрезка звука - выкл, ручная подрезка начала, авто подрезка начала и конца
	void crop(const vector<float> &sound0, int n, vector<float> &sound);
};


extern Sea SEA;