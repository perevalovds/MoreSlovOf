#include "SoundFX.h"
#include "ofxKuMessageLog.h"
#include "gui_generated.h"
#include "ofxAudioFile.h"
#include "Common.h"
#include "Sea.h"


SoundFX SOUNDFX;

//--------------------------------------------------------------------------------
void SoundFX::setup() {
	float max_len_sec = 20;
	delay1_.setup(SR, max_len_sec);
	delay2_.setup(SR, max_len_sec);

	send_clear();
}

//--------------------------------------------------------------------------------
void SoundFX::update() {
	delay1_.set_volume(PRM delay1_vol);
	delay1_.set_delay_time(PRM delay1_sec);
	delay1_.set_feedback(PRM delay1_fdbck);
	delay1_.set_cross_stereo(PRM delay1_cross);

	delay2_.set_volume(PRM delay2_vol);
	delay2_.set_delay_time(PRM delay2_sec);
	delay2_.set_feedback(PRM delay2_fdbck);
	delay2_.set_cross_stereo(PRM delay2_cross);
}

//--------------------------------------------------------------------------------
//Отправка звуков
void SoundFX::send_clear() {
	input1_.clear();
	input2_.clear();
}

//--------------------------------------------------------------------------------
void SoundFX::send_sound(const StereoSample &sample, float send_value1, float send_value2) {
	input1_.add(sample, send_value1);
	input2_.add(sample, send_value2);
}

//--------------------------------------------------------------------------------
//сгенерировать выходной сигнал
void SoundFX::process_add(StereoSample &out_sample_added) {
	delay1_.process_add(input1_.L, input1_.R, out_sample_added.L, out_sample_added.R);
	delay2_.process_add(input2_.L, input2_.R, out_sample_added.L, out_sample_added.R);
}

//--------------------------------------------------------------------------------
