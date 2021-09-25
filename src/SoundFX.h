#pragma once

//Звуковые эффекты

#include "ofMain.h"
#include "Common.h"
#include "ofxSoundUtils.h"

struct SoundFX {
	void setup();
	void update();

	//Отправка звуков
	void send_clear();
	void send_sound(const StereoSample &sample, float send_value1, float send_value2);

	//сгенерировать выходной сигнал
	void process_add(StereoSample &out_sample_added);

protected:
	ofxSoundUtilsDelayStereo delay1_, delay2_;
	StereoSample input1_, input2_;
	StereoSample proc_;
};

extern SoundFX SOUNDFX;