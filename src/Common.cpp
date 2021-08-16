#include "Common.h"
#include "gui_generated.h"
#include "ofxKuProbability.h"

//--------------------------------------------------------------------------------
int Common::sample_rate() {
	return get_sample_rate(PRM sample_rate);
}


//--------------------------------------------------------------------------------
int Common::window_in() {
	return PRM time_in * sample_rate();
}

//--------------------------------------------------------------------------------
float Common::gen_destructor_amount() {
	ofxKuProbability prob;
	prob.add_value(0, PRM des_amount_0);
	prob.add_value(0.1, PRM des_amount_10);
	prob.add_value(0.2, PRM des_amount_20);
	prob.add_value(0.3, PRM des_amount_30);
	prob.add_value(0.4, PRM des_amount_40);
	prob.add_value(0.5, PRM des_amount_50);
	prob.add_value(0.6, PRM des_amount_60);
	prob.add_value(0.7, PRM des_amount_70);
	prob.add_value(0.8, PRM des_amount_80);
	prob.add_value(0.9, PRM des_amount_90);
	return prob.generate_value() / ofToFloat(PRM des_amt_divide);
}

//--------------------------------------------------------------------------------
float Common::gen_destructor_range() {
	ofxKuProbability prob;
	prob.add_value(0, PRM des_range_0);
	prob.add_value(0.1, PRM des_range_10);
	prob.add_value(0.2, PRM des_range_20);
	prob.add_value(0.3, PRM des_range_30);
	prob.add_value(0.4, PRM des_range_40);
	prob.add_value(0.5, PRM des_range_50);
	prob.add_value(0.6, PRM des_range_60);
	prob.add_value(0.7, PRM des_range_70);
	prob.add_value(0.8, PRM des_range_80);
	prob.add_value(0.9, PRM des_range_90);
	prob.add_value(1, PRM des_range_100);
	return prob.generate_value() / ofToFloat(PRM des_rng_divide);
}

//--------------------------------------------------------------------------------
//время предсказания
float Common::gen_predict_sec() {
	ofxKuProbability prob;
	prob.add_value(PRM predict_sec1, PRM wghpred_1);
	prob.add_value(PRM predict_sec2, PRM wghpred_2);
	prob.add_value(PRM predict_sec3, PRM wghpred_3);
	return prob.generate_value();
}

//--------------------------------------------------------------------------------
//диапазон при обучении
float Common::gen_examplstep() {
	ofxKuProbability prob;
	prob.add_value(PRM examplstep1, PRM wghstep_1);
	prob.add_value(PRM examplstep2, PRM wghstep_2);
	prob.add_value(PRM examplstep3, PRM wghstep_3);
	return prob.generate_value();
}

//--------------------------------------------------------------------------------
int Common::get_api_id(int stringlist_index) {
	//stringlist *engine=DS [WASAPI,ASIO,DS]
	if (stringlist_index == 0) return ofSoundDevice::Api::MS_WASAPI;
	if (stringlist_index == 1) return ofSoundDevice::Api::MS_ASIO;
	if (stringlist_index == 2) return ofSoundDevice::Api::MS_DS;
	return 0;
}

//--------------------------------------------------------------------------------
string Common::get_api_name(int stringlist_index) {
	//stringlist *engine=DS [WASAPI,ASIO,DS]
	if (stringlist_index == 0) return "WASAPI";
	if (stringlist_index == 1) return "ASIO";
	if (stringlist_index == 2) return "DirectShow";
	return "?";
}

//--------------------------------------------------------------------------------
int Common::get_sample_rate(int stringlist_index) {
	//stringlist *sample_rate = 44100 [8000, 11025, 22050, 32000, 44100, 48000]
	if (stringlist_index == 0) return 8000;
	if (stringlist_index == 1) return 11025;
	if (stringlist_index == 2) return 22050;
	if (stringlist_index == 3) return 32000;
	if (stringlist_index == 4) return 44100;
	if (stringlist_index == 5) return 48000;
	return 44100;
}

//--------------------------------------------------------------------------------
int Common::get_sound_buffer_size(int stringlist_index) {
	//stringlist *sound_buffer = 512 [16, 32, 64, 128, 256, 512, 1024, 2048, 4096]
	if (stringlist_index == 0) return 16;
	if (stringlist_index == 1) return 32;
	if (stringlist_index == 2) return 64;
	if (stringlist_index == 3) return 128;
	if (stringlist_index == 4) return 256;
	if (stringlist_index == 5) return 512;
	if (stringlist_index == 6) return 1024;
	if (stringlist_index == 7) return 2048;
	if (stringlist_index == 8) return 4096;
	return 512;
}



//--------------------------------------------------------------------------------
