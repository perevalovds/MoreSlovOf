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

	//добавить слово
	//buffer с запасом, надо использовать n
	//pedal_index 0 - техно, 1 - повторы
	void push_word(const vector<float> &sound, int n, int pedal_index);

	//звук
	void audioOut(vector<float> &stereo_buffer, int n);
protected:
	vector<SeaWord> words_;	//создаем один раз, чтобы звуковой потом мог всегда считывать

	//подрезка звука - выкл, ручна€ подрезка начала, авто подрезка начала и конца
	void crop(const vector<float> &sound0, int n, vector<float> &sound);

	//¬ыбор дорожки дл€ записи
	void recbuttons_setup();
	void recbuttons_update();	//обновить GUI кнопки записи и номер дорожки дл€ записи
	void recbuttons_set_next();	//сдвиг на следующую дорожку, если не нажата красна€ кнопка пульта Record Arm

	vector<int*> rec_gui_;	//значени€ REC1..7
	vector<int> rec_state_;	//последнее состо€ние кнопок

	void restore_backup(int i);
};


extern Sea SEA;