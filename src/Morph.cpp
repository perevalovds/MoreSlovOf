#include "Morph.h"
#include "gui_generated.h"
#include "ofxKuMessageLog.h"
#include "ofxSoundUtils.h"

Morph MORPH;

//--------------------------------------------------------------
void Morph::setup() {
	ofDirectory dir;
	int N = dir.listDir("morph");
	sounds_.resize(N);
	for (int i = 0; i < N; i++) {
		auto &Sound = sounds_[i];
		auto &sound = Sound.sound;
		auto &n = Sound.n;
		sound = ofxSoundUtils::load_sound_raw_mono16(dir.getPath(i));
		Sound.n = sound.size();

		//трансформация
		for (int i = 0; i < n; i++) {
			float &v = sound[i];
			v = fabs(v);
			if (v > 0) v = sqrt(v);
			//v *= v;
			//sound[i] = fabs(sound[i]);
		}
	}
	N_ = N;
	MLOG("Loaded " + ofToString(N) + " morph sounds");
}

//--------------------------------------------------------------
void Morph::apply_to_audio(int file_id, int &audio_counter, float intensity, StereoSample &audio) {
	if (file_id >= 0 && file_id < N_) {
		auto &sound = sounds_[file_id];
		float v = sound.sound[audio_counter % sound.n];

		//audio.L = audio.L * (1-intensity) + v*intensity;
		//audio.R = audio.L * (1 - intensity) + v * intensity;
		audio.L = audio.L * ((1 - intensity) + v * intensity);
		audio.R = audio.R * ((1 - intensity) + v * intensity);

		audio_counter++;
	}
}

//--------------------------------------------------------------
