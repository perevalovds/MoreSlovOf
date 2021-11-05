#pragma once

//Морфинг в другой звук
#include "ofMain.h"
#include "Common.h"
#include "MachineTone.h"

struct Morph {
	void setup();
	void apply_to_audio(int file_id, int &audio_counter, float intensity, StereoSample &audio);

protected:
	struct Sound {
		vector<float> sound;
		int n = 0;
		void load(string wav_file) {

		}
	};
	vector<Sound> sounds_;
	int N_ = 0;
};

extern Morph MORPH;