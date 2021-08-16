#pragma once
//Auto-generated GUI file for ofxKuTextGui, 2021-07-07-10-43-24-862

#include "ofMain.h"
#include "ofxKuTextGui.h"

struct Parameters {
	int ClearLog;
	int Save;
	int Exit;
	int fps_;
	float vol_in_;
	float vol_out_;
	int FPS;
	int _FPS_;
	int FULL_SCR;
	int _FULL_SCR_;
	int update_scr;
	int scr_x;
	int _scr_x_;
	int scr_y;
	int _scr_y_;
	int scr_w;
	int _scr_w_;
	int scr_h;
	int _scr_h_;
	int messages_n;
	int _messages_n_;
	int messages_font;
	int _messages_font_;
	int messages_x;
	int _messages_x_;
	int messages_y;
	int _messages_y_;
	int OSC_in_port;
	int _OSC_in_port_;
	int Watchdog;
	int wd_port;
	int wd_time;
	int in_channels;
	int _in_channels_;
	int out_channels;
	int _out_channels_;
	int sample_rate;
	int _sample_rate_;
	int sound_buffers;
	int _sound_buffers_;
	int sound_buffer;
	int _sound_buffer_;
	int engine;
	int _engine_;
	int selectby;
	int _selectby_;
	int device_in;
	int _device_in_;
	int device_out;
	int _device_out_;
	string devin_nameports;
	string _devin_nameports_;
	string devout_nameports;
	string _devout_nameports_;
	int EMULATE_IN;
	int _EMULATE_IN_;
	float emulate_vol;
	string device_in_name_;
	string device_out_name_;
	int SOUND_STATUS_;
	string SND_CALLB_;
	int ShowDevices;
	int buffer_sec;
	int _buffer_sec_;
	int safe_samples;
	int _safe_samples_;
	int heads_dist_;
	int PASS_THRU;
	float pass_vol;
	float MIC_VOL;
	float GEN_VOL;
	int SaveNetwork;
	int LoadNetwork;
	int time_in;
	int _time_in_;
	float sparse_incr;
	float _sparse_incr_;
	int input_neurons_;
	int hidden_neurons;
	int _hidden_neurons_;
	int examples;
	int train_steps;
	int epochs;
	float momentum;
	int wghpred_1;
	int wghpred_2;
	int wghpred_3;
	int predict_sec1;
	int predict_sec2;
	int predict_sec3;
	int predict_sec_;
	int Test_Constr_gen;
	int wghstep_1;
	int wghstep_2;
	int wghstep_3;
	int examplstep1;
	int examplstep2;
	int examplstep3;
	int examplstep_;
	string examplsec_;
	int MICROPHONES;
	int mic_;
	float des_amount_;
	float des_range_;
	int TrainNow;
	int GenParams;
	int GenSound;
	int GenSequence;
	float RMS_;
	float RMS_MAX;
	int FILTER;
	float filter_cutoff;
	int INFILTER;
	float infilter_cutoff;
	int AUTOPLAY;
	int starting_pause;
	int mode_;
	string pause_;
	int train_train;
	int train_play;
	int train_pause;
	int play_train;
	int play_play;
	int play_pause;
	int pause_train;
	int pause_play;
	int pause_pause;
	int pause_sec1;
	int pause_sec2;
	int pause_sec3;
	int pause_sec4;
	int pause_sec5;
	int Test_NextStep;
	int SEQ_NOTES;
	float SEQ_OVERLAP;
	float fade_sec;
	int des_amount_0;
	int des_amount_10;
	int des_amount_20;
	int des_amount_30;
	int des_amount_40;
	int des_amount_50;
	int des_amount_60;
	int des_amount_70;
	int des_amount_80;
	int des_amount_90;
	string des_amt_divide;
	int Test_Destr_gen;
	int des_range_0;
	int des_range_10;
	int des_range_20;
	int des_range_30;
	int des_range_40;
	int des_range_50;
	int des_range_60;
	int des_range_70;
	int des_range_80;
	int des_range_90;
	int des_range_100;
	string des_rng_divide;
	int SaveDebugSounds;
    Parameters();
    void setup(ofxKuTextGui &gui, string fileName);
    void save();
    string fileName_;
    ofxKuTextGui *gui_;
};

extern Parameters params;
#define PRM params.
