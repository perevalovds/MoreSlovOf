#include "SeaWord.h"
#include "gui_generated.h"
#include "ofxKuMessageLog.h"
#include "Common.h"

//--------------------------------------------------------------
void SeaWord::setup() {
	sound_.resize(Common::max_mic_rec_n());

}
//--------------------------------------------------------------
void SeaWord::run(const vector<float> &sound, int n) {
	n_ = 0;	//stop sounding if any
	memcpy(sound_.data(), sound.data(), n);
	n_ = n;
	is_live_ = true;

	MLOG("Sound " + ofToString(1000 * n / Common::sample_rate()) + " msec");
}

//--------------------------------------------------------------
void SeaWord::update() {

}

//--------------------------------------------------------------
void SeaWord::draw() {

}

//--------------------------------------------------------------
bool SeaWord::is_live() {
	return is_live_;
}

//--------------------------------------------------------------
void SeaWord::audioOut(vector<float> &stereo_buffer, int n) {
	for (int i = 0; i < n; i++) {
		stereo_buffer[2 * i] = stereo_buffer[2 * i + 1] = ofRandom(-0.05, 0.05);
	}

}

//--------------------------------------------------------------
