#pragma once

//Sea of words
#include "ofMain.h"

/*
dummy Duration
int w_duration_msec=10000 100:60000 10,500
int w_evolution_perc=40 1:100 1,10
int w_fadeout_perc=10 1:100 1,10

dummy Repeats
int w_repeat0_msec=250 0:1000 10,100
int w_repeat1_msec=250 0:1000 10,100

dummy Vol_Stereo
stringlist w_envelope=const [const,fadeout,fadein]
int w_stereo_range=0 0:100 1,10

dummy Fragment
int w_speed_perc=100 1:100 1,10
int w_len_perc=100 1:100 1,10
int w_pos_perc=0 0:100 1,10
int w_pos_random_perc=0 0:100 1,10

dummy Granular
int w_grain_msec=50 1:1000 1,10
int w_grain_move_perc=100 0:200 1,10
int w_grain_pause_msec=0 0:1000 1,10

dummy Filter
stringlist w_flt=No [No,Lopass,Hipass,Bandpass]
int w_flt_cutoff0=500 0:1000 5,50
int w_flt_cutoff1=0.5 0:1000 5
*/

//память должна быть выделена заранее, чтобы не было сбоев со звуковом

struct SeaWord {
	void setup();
	void run(const vector<float> &sound, int n);	//sound может быть длиннее
	void update();
	void draw();
	bool is_live();
protected:
	vector<float> sound_;
	float n_ = 0;
	bool is_live_ = false;
};

