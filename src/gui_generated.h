#pragma once
//Auto-generated GUI file for ofxKuTextGui, 2021-08-17-10-19-47-778

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
	int in_channels;
	int _in_channels_;
	int out_channel_start;
	int _out_channel_start_;
	int out_channels;
	int _out_channels_;
	int sample_rate;
	int _sample_rate_;
	int sound_buffers;
	int _sound_buffers_;
	int sound_buffer;
	int _sound_buffer_;
	int sound_buffer_;
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
	string device_in_name_;
	string device_out_name_;
	int SOUND_STATUS_;
	string SND_CALLB_;
	int ShowDevices;
	float MIC_VOL;
	int MIC_FILTER;
	float mic_cutoff;
	int PASS_THRU;
	float PASS_VOL;
	string pass_thru_delta_;
	float OUT_VOL;
	string Pedal_baud;
	string _Pedal_baud_;
	int Pedal_invert;
	string Pedal_status_;
	int Print_Arduinos;
	int PEDAL_;
	int max_rec_msec;
	int _max_rec_msec_;
	int max_words;
	int _max_words_;
	string WORDS_;
	int w_duration_msec;
	int w_evolution_perc;
	int w_fadeout_perc;
	int w_repeat0_msec;
	int w_repeat1_msec;
	int w_envelope;
	int w_stereo_range;
	int w_speed_perc;
	int w_len_perc;
	int w_pos_perc;
	int w_pos_random_perc;
	int w_grain_msec;
	int w_grain_move_perc;
	int w_grain_pause_msec;
	int w_flt;
	int w_flt_cutoff0;
	int w_flt_cutoff1;
	int sea_x;
	int sea_y;
	int sea_w;
	int sea_h;
	int SaveDebugSounds;
    Parameters();
    void setup(ofxKuTextGui &gui, string fileName);
    void save();
    string fileName_;
    ofxKuTextGui *gui_;
};

extern Parameters params;
#define PRM params.
