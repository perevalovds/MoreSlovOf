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

	MLOG("Sound " + ofToString(n));
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
