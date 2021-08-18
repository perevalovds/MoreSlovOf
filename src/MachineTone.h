#pragma once

#include "ofMain.h"
#include "LfoBeat.h"
#include "ofxFft.h"
#include "ofxSoundUtils.h"

extern int SR;  //sample rate

struct StereoSample {
	float L = 0;
	float R = 0;
	void clear() { L = R = 0; }
};

//Обращение к параметрами машины внутри машины
#define TP prm_->

struct ToneParams {
	float vol = 0.5;
	float pan = 0.5;

	int mode = 0;
	int delay = 100;
	float pos = 0;
	float len = 0.5;
	float spd = 0.5;
	float grain_len = 0.1;
	int voltype = 0;
	int volstp = 1;
	float volmov = 0;
	int pantype = 0;
	int panstp = 1;
	float panmov = 0;
	//float VOL = 0.5;

	float flt_cutoff = 0.5;
	int flt_mode = 0;	//bypass, Lopass, Hipass, Bandpass
};


//Один тон
struct MachineTone {
    vector<float> sound;
    
    void setup(int id, vector<float> &sound0, float BPM, ToneParams *params);
    void audioOut( StereoSample &out );
    void update( float dt );
	
	void draw_thumb(); //рисовать звук и pos

    ~MachineTone();
    
	int id_ = 0;

	ToneParams *prm_;

    int sample;
    int N;
    LfoBeat lfo_vol;
    LfoBeat lfo_pan;
    LfoBeat lfo_flt;
    
    
	float vol = 1;
	float pan = 0.5;
	float flt = 0.5;
    
    //bool live;
    int samples_per_bit;
    
    
    int Loop_Len; //длина повтора
    //int Play_Len; //общая длина

    int index_; //номер повтора
    
    
    void audioOut_delay( StereoSample &out );
    void audioOut_grain( StereoSample &out );
    void audioOut_spectr( StereoSample &out );
    
    //гранулы
    int play_pos;
    int grain_pos;
    int played_count;
    

    //управляющие параметры
    int mode;   //delay, grain, spectral
    
    float pos_f, len_f, speed_f, grain_f;
    
    //внутренние параметры
    int pos_s, len_s, speed_s, grain_s;

	ofxSoundUtilsFilter mic_filter_L, mic_filter_R;
    
    //спектр
    static const int fft_n = 2048; //1024;
    static const int fft_n_2 = fft_n/2;
    vector<float> Phase_[2];   //для обратного преобразования
    vector<float> phase_prv_[2];   //для обратного преобразования
    vector<float> lastBuffer_;
    vector<float> tempBuffer_[2];
    vector<float> temp_;
    vector<float> phase_;

    float play_fft;
    ofxFft* fft;
    vector<float>fft_buffer;
    int fft_pos;        //подготовленный сэмпл для fft
    void audioOut_make_buffer();
    

	//thumbnail
	vector<float> thumb_;	//данные для картинки звука
	void make_thumb();

};




