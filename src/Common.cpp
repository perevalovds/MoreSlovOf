#include "Common.h"
#include "gui_generated.h"
#include "ofxKuProbability.h"

//--------------------------------------------------------------------------------
int Common::sample_rate() {
	return get_sample_rate(PRM sample_rate);
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
