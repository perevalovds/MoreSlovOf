#pragma once

//Одно слово - оно генерирует много сэмплов
//память должна быть выделена заранее, чтобы не было сбоев со звуковом

#include "ofMain.h"
#include "SeaSample.h"

struct SeaWordParam {
	//Duration
	int w_duration_msec = 10000;
	int w_evolution_perc = 40;
	int w_fadeout_perc = 10;

	//Repeats
	int w_repeat0_msec = 250;
	int w_repeat1_msec = 250;

	//Vol, stereo
	int w_vol_perc = 50;
	int w_envelope = 0;	// const[const, fadeout, fadein]
	int w_stereo_range = 0;	// 0:100 1, 10

	//Fragment
	int w_speed_perc = 100;
	int w_len_perc = 100;
	int w_pos_perc = 0;
	int w_pos_random_perc = 0;

	//Granular
	int w_grain_msec = 50;
	int w_grain_move_perc = 100;
	int w_grain_pause_msec = 0;

	//Filter
	int w_flt = 0; // No[No, Lopass, Hipass, Bandpass]
	int w_flt_cutoff0 = 500;	//0..1000
	int w_flt_cutoff1 = 500;	//0..1000

	void read_from_GUI();
};



struct SeaWord {
	void setup(int id);
	void run(const vector<float> &sound, int n, const SeaWordParam &param);	//sound может быть длиннее
	void update();	//генерация повтроений
	void draw();
	bool is_live();

	//звук
	void audioOut(vector<float> &stereo_buffer, int n);
protected:
	int id_ = 0;
	vector<float> sound_;	//исходный звук
	int n_ = 0;
	bool is_live_ = false;

	SeaWordParam param_;

	vector<SeaSample> samples_;	//повторы

	int i_ = 0;	//test
	int rep_ = 0;	//test
	int max_reps_ = 16;
	float stereo_pos_L_ = 0.5;
	float stereo_pos_R_ = 0.5;

};

