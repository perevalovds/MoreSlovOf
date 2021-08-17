#include "SeaSample.h"
#include "gui_generated.h"
#include "ofxKuMessageLog.h"
#include "Common.h"

//--------------------------------------------------------------
void SeaSample::setup(const SeaSampleParam &param) {
	param_ = param;

}

//--------------------------------------------------------------
bool SeaSample::is_live() {
	return is_live_;
}

//--------------------------------------------------------------
void SeaSample::audioOut(vector<float> &stereo_buffer, int n) {
	//for (int i = 0; i < n; i++) {
	//	stereo_buffer[2 * i] = stereo_buffer[2 * i + 1] = ofRandom(-0.05, 0.05);
	//}

}

//--------------------------------------------------------------
