#pragma once

//Общие данные и работа с GUI

#include "ofMain.h"

struct Common {
	static int sample_rate();
	static int window_in();

	//Конструктор
	//время предсказания
	static float gen_predict_sec();
	//диапазон при обучении
	static float gen_examplstep();

	//Деструктор
	static float gen_destructor_amount();
	static float gen_destructor_range();

	//GUI parser
	static int get_api_id(int stringlist_index);
	static string get_api_name(int stringlist_index);
	static int get_sample_rate(int stringlist_index);
	static int get_sound_buffer_size(int v);
};