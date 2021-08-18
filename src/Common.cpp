#include "Common.h"
#include "gui_generated.h"
#include "ofxKuProbability.h"

int SR = 0;	//sample rate

//--------------------------------------------------------------------------------
void Common::setup() {
	SR = get_sample_rate(PRM sample_rate);
}

//--------------------------------------------------------------------------------
int Common::max_mic_rec_n() {
	return PRM max_rec_msec * SR / 1000;
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
int Common::get_sound_buffer_size(int v) {
	//int *sound_buffer=512 8:4096 1,50          //stringlist *sound_buffer = 512 [16, 32, 64, 128, 256, 512, 1024, 2048, 4096]
	return v;
}

//--------------------------------------------------------------------------------
int Common::w_delay(int index) {	//stringlist w_delay1=0 [1,2,4,8,16,32]
	switch (index) {
	case 0: return 1;
	case 1: return 2;
	case 2: return 4;
	case 3: return 8;
	case 4: return 16;
	case 5: return 32;

	default: return 4;
	}
	return 4;

}

//--------------------------------------------------------------------------------
