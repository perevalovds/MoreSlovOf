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

	//подрезка звука - выкл, ручная подрезка начала, авто подрезка начала и конца
	void crop(const vector<float> &sound0, int n, vector<float> &sound);

	//Выбор дорожки для записи
	void recbuttons_setup();
	void recbuttons_update();	//обновить GUI кнопки записи и номер дорожки для записи
	void recbuttons_set_next();	//сдвиг на следующую дорожку, если не нажата красная кнопка пульта Record Arm

	vector<int*> rec_gui_;	//значения REC1..7
	vector<int> rec_state_;	//последнее состояние кнопок

	void load_sample(int i);	//загрузить сэмпл из предзаписанных в заданную дорожку
};


extern Sea SEA;