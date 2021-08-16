#pragma once

//Sound utils

#include "ofMain.h"



//случайный sample&hold на два канала
vector<float> sample_and_hold_random_stereo(vector<float> &sound_mono);

//вычисление статистики фазового пространства
//рекомендуется использовать mu-преобразованный звук
struct SpaceStat {
	void setup(int w, int h, float *sound_mono, int n);
	void setup(int w, int h, vector<float> &sound_mono, int i0, int n);
	void draw(float x, float y, float w, float h);

	int w, h;
	vector<float> v;
};