#pragma once

//Один сэмпл слова

#include "ofMain.h"

struct SeaSampleParam {
	//Vol, stereo
	int w_vol_perc = 50;
	int w_envelope = 0;	// const[const, fadeout, fadein]
	float w_stereo_pos = 0;	//-1,1

	//Fragment
	int w_speed_perc = 100;
	int w_len_perc = 100;
	int w_pos_perc = 0;

	//Granular
	int w_grain_msec = 50;
	int w_grain_move_perc = 100;
	int w_grain_pause_msec = 0;

	//Filter
	int w_flt = 0; // No[No, Lopass, Hipass, Bandpass]
	int w_flt_cutoff = 500;	//0..1000

};


struct SeaSample {
	void setup(const SeaSampleParam &param);
	bool is_live();

	//звук
	void audioOut(vector<float> &stereo_buffer, int n);
protected:
	bool is_live_ = false;
	SeaSampleParam param_;
};

