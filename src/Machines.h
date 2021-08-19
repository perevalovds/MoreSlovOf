#pragma once

#include "ofMain.h"
#include "MachineTone.h"
#include "ofxKuTextGui.h"



extern int SR;  //sample rate


const int Tone_Delay = 0;
const int Tone_Grain = 1;
const int Tone_Spectral = 2;

const int maxTones = 7;	//последняя - спецдорожка

//Звуковая машина для воспроизведения сэмплов
struct ToneMachine {
    ToneMachine();
    void setup();

	void draw_thumbs();		//рисовать звуки

    bool shared_pushed;
    
    void push_tone(int ton_number, vector<float> &sound, float BPM);
    void audioOut(StereoSample &out_sample);
    void update(float dt);
  
    int n;
    MachineTone *tone[maxTones];
	vector<ToneParams> params_;
    
    int index = 0;  //тон, готовый к записи
    
};

extern ToneMachine MACHINE;