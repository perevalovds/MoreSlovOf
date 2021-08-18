#pragma once

//Общие данные и работа с GUI

#include "ofMain.h"

struct Common {
	static void setup();

	static int max_mic_rec_n();

	//GUI parser
	static int get_api_id(int stringlist_index);
	static string get_api_name(int stringlist_index);
	static int get_sample_rate(int stringlist_index);
	static int get_sound_buffer_size(int v);

	static int w_delay(int index);	//stringlist w_delay1=0 [64,32,16,8,4,2,1]

};

extern int SR;	//sample rate, call set_sample_rate() to set up it