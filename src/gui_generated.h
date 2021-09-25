#pragma once
//Auto-generated GUI file for ofxKuTextGui, 2021-09-25-15-51-26-806

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
	int scr2_x;
	int _scr2_x_;
	int scr2_y;
	int _scr2_y_;
	int scr2_w;
	int _scr2_w_;
	int scr2_h;
	int _scr2_h_;
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
	float SEA_VOL;
	string pass_thru_delta_;
	float OUT_VOL;
	int Arduino_Pedal;
	int _Arduino_Pedal_;
	string Pedal_baud;
	string _Pedal_baud_;
	int Pedal_invert;
	string Pedal_status_;
	int Print_Arduinos;
	int PEDAL_;
	int PEDAL2_;
	string APC_midi_in;
	string _APC_midi_in_;
	string APC_midi_out;
	string _APC_midi_out_;
	string APC_status_;
	int Print_MIDI;
	int log_midi;
	int max_rec_msec;
	int _max_rec_msec_;
	int max_words;
	int _max_words_;
	int max_polyphony;
	int _max_polyphony_;
	int BPM;
	int Auto_Rec_Next;
	int Crop_Mode;
	int Crop_thresh;
	int Crop_ms;
	int Crop_fade_ms;
	float Min_Vol;
	string WORDS_;
	int REC;
	int backup1;
	int backup2;
	int backup3;
	int backup4;
	int backup5;
	int backup6;
	int REC1;
	int w_mode1;
	int w_delay1;
	float w_len1;
	float w_spd1;
	float w_grain_len1;
	int w_flt1;
	float w_cutoff1;
	int w_voltype1;
	int w_volstp1;
	float w_volmov1;
	int w_pantype1;
	int w_panstp1;
	float w_panmov1;
	int w_morph1;
	int w_percent1;
	int w_louder1;
	float w_pan1;
	float w_vol1;
	float w_pos1;
	int REC2;
	int w_mode2;
	int w_delay2;
	float w_len2;
	float w_spd2;
	float w_grain_len2;
	int w_flt2;
	float w_cutoff2;
	int w_voltype2;
	int w_volstp2;
	float w_volmov2;
	int w_pantype2;
	int w_panstp2;
	float w_panmov2;
	int w_morph2;
	int w_percent2;
	int w_louder2;
	float w_pan2;
	float w_vol2;
	float w_pos2;
	int REC3;
	int w_mode3;
	int w_delay3;
	float w_len3;
	float w_spd3;
	float w_grain_len3;
	int w_flt3;
	float w_cutoff3;
	int w_voltype3;
	int w_volstp3;
	float w_volmov3;
	int w_pantype3;
	int w_panstp3;
	float w_panmov3;
	int w_morph3;
	int w_percent3;
	int w_louder3;
	float w_pan3;
	float w_vol3;
	float w_pos3;
	int REC4;
	int w_mode4;
	int w_delay4;
	float w_len4;
	float w_spd4;
	float w_grain_len4;
	int w_flt4;
	float w_cutoff4;
	int w_voltype4;
	int w_volstp4;
	float w_volmov4;
	int w_pantype4;
	int w_panstp4;
	float w_panmov4;
	int w_morph4;
	int w_percent4;
	int w_louder4;
	float w_pan4;
	float w_vol4;
	float w_pos4;
	int REC5;
	int w_mode5;
	int w_delay5;
	float w_len5;
	float w_spd5;
	float w_grain_len5;
	int w_flt5;
	float w_cutoff5;
	int w_voltype5;
	int w_volstp5;
	float w_volmov5;
	int w_pantype5;
	int w_panstp5;
	float w_panmov5;
	int w_morph5;
	int w_percent5;
	int w_louder5;
	float w_pan5;
	float w_vol5;
	float w_pos5;
	int REC6;
	int w_mode6;
	int w_delay6;
	float w_len6;
	float w_spd6;
	float w_grain_len6;
	int w_flt6;
	float w_cutoff6;
	int w_voltype6;
	int w_volstp6;
	float w_volmov6;
	int w_pantype6;
	int w_panstp6;
	float w_panmov6;
	int w_morph6;
	int w_percent6;
	int w_louder6;
	float w_pan6;
	float w_vol6;
	float w_pos6;
	int REC7;
	int w_mode7;
	int w_delay7;
	float w_len7;
	float w_spd7;
	float w_grain_len7;
	int w_flt7;
	float w_cutoff7;
	int w_voltype7;
	int w_volstp7;
	float w_volmov7;
	int w_pantype7;
	int w_panstp7;
	float w_panmov7;
	int w_morph7;
	int w_percent7;
	int w_louder7;
	float w_pan7;
	float w_vol7;
	float w_pos7;
	float REP_VOL;
	int w_duration_msec;
	int w_evolution_perc;
	int w_fadeout_perc;
	int w_repeat0_msec;
	int w_repeat1_msec;
	int w_vol_perc;
	int w_envelope;
	int w_stereo_range;
	int w_grain_msec;
	int w_grain_move_perc;
	int w_grain_pause_msec;
	int w_flt;
	int w_flt_cutoff0;
	int w_flt_cutoff1;
	float d1pos1;
	float d1pos2;
	float d1pos3;
	float d1pos4;
	float d1pos5;
	float d1pos6;
	float d1pos7;
	float d1pos8;
	float d1pos9;
	float d1pos10;
	float d1pos11;
	float d1pos12;
	float d1pos13;
	float d1pos14;
	float d1pos15;
	float d1pos16;
	int d1_Equal;
	int d1_Random;
	float d1_len;
	float d1_spd;
	float d2pos1;
	float d2pos2;
	float d2pos3;
	float d2pos4;
	float d2pos5;
	float d2pos6;
	float d2pos7;
	float d2pos8;
	float d2pos9;
	float d2pos10;
	float d2pos11;
	float d2pos12;
	float d2pos13;
	float d2pos14;
	float d2pos15;
	float d2pos16;
	int d2_Equal;
	int d2_Random;
	float d2_len;
	float d2_spd;
	float smth_delay_sec;
	float smth_spd_sec;
	float sm_gr_len_sec;
	float v_spd1;
	float v_grain_len1;
	float v_cutoff1;
	float v_pan1;
	float v_vol1;
	float v_pos1;
	int Variate1;
	float v_spd2;
	float v_grain_len2;
	float v_cutoff2;
	float v_pan2;
	float v_vol2;
	float v_pos2;
	int Variate2;
	float v_spd3;
	float v_grain_len3;
	float v_cutoff3;
	float v_pan3;
	float v_vol3;
	float v_pos3;
	int Variate3;
	float v_spd4;
	float v_grain_len4;
	float v_cutoff4;
	float v_pan4;
	float v_vol4;
	float v_pos4;
	int Variate4;
	float v_spd5;
	float v_grain_len5;
	float v_cutoff5;
	float v_pan5;
	float v_vol5;
	float v_pos5;
	int Variate5;
	float v_spd6;
	float v_grain_len6;
	float v_cutoff6;
	float v_pan6;
	float v_vol6;
	float v_pos6;
	int Variate6;
	int sea_x;
	int sea_y;
	int sea_w;
	int sea_h;
	int thumb_x1;
	int thumb_y;
	int thumb_w;
	int thumb_h;
	float thumb_scl;
	float thumb_vol;
	int thumb_x2;
	int thumb_x3;
	int Backups7;
	int _Backups7_;
	int backup_x;
	int backup_y;
	int thumb_x4;
	int thumb_x5;
	int thumb_x6;
	int thumb_x7;
	int SaveDebugSounds;
    Parameters();
    void setup(ofxKuTextGui &gui, string fileName);
    void save();
    string fileName_;
    ofxKuTextGui *gui_;
};

extern Parameters params;
#define PRM params.
