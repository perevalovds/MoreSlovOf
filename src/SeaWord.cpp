#include "SeaWord.h"
#include "gui_generated.h"
#include "ofxKuMessageLog.h"


//--------------------------------------------------------------
void SeaWord::setup(const vector<float> &sound) {
	sound_ = sound;
	n_ = sound_.size();
}

//--------------------------------------------------------------
void SeaWord::update() {

}

//--------------------------------------------------------------
void SeaWord::draw() {

}

//--------------------------------------------------------------
bool SeaWord::is_live() {
	return true;
}

//--------------------------------------------------------------
