#pragma once

//Общие данные и работа с GUI

#include "ofMain.h"
#include "ofxKuMessageLog.h"

extern int SR;		//Sample rate

const int maxTones_part1 = 6;	//первая часть, управляемая с пультов
const int maxTones_part2 = 6;	//первая часть, управляемая только из программы
const int maxTones = maxTones_part1 + maxTones_part2;	//все дорожки


struct StereoSample {
	float L = 0;
	float R = 0;
	void clear() { L = R = 0; }
	void add(const StereoSample &in, float vol = 1) {
		L += in.L * vol;
		R += in.R * vol;
	}
};

//assert, exit
void x_exit(const string &message);
#define x_assert(cond, message) { if (!(cond)) x_exit(message); }

//Замеры времени
//#define TIMER_ON(i) float time__##i = ofGetElapsedTimeMillis();
//#define TIMER_PRINT(i, message) cout << "TIME " << message << ": " << ofGetElapsedTimeMillis() - time__##i << " ms" << endl;

//Для отключения замеров времени:
#define TIMER_ON(i) {}
#define TIMER_PRINT(i, message) {}



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

extern int SR;	//sample rate, call setup() to set up it