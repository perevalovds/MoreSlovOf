#include "SeaWord.h"
#include "gui_generated.h"
#include "ofxKuMessageLog.h"
#include "Common.h"

//--------------------------------------------------------------
void SeaWordParam::read_from_GUI() {
	//Duration
	w_duration_msec = PRM w_duration_msec;
	w_evolution_perc = PRM w_evolution_perc;
	w_fadeout_perc = PRM w_fadeout_perc;

	//Repeats
	w_repeat0_msec = PRM w_repeat0_msec;
	w_repeat1_msec = PRM w_repeat1_msec;

	//Vol, stereo
	w_vol_perc = PRM w_vol_perc;
	w_envelope = PRM w_envelope;	// const[const, fadeout, fadein]
	w_stereo_range = PRM w_stereo_range;	// 0:100 1, 10

	//Fragment
	w_speed_perc = PRM w_speed_perc;
	w_len_perc = PRM w_len_perc;
	w_pos_perc = PRM w_pos_perc;
	w_pos_random_perc = PRM w_pos_random_perc;

	//Granular
	w_grain_msec = PRM w_grain_msec;
	w_grain_move_perc = PRM w_grain_move_perc;
	w_grain_pause_msec = PRM w_grain_pause_msec;

	//Filter
	w_flt = PRM w_flt; // No[No, Lopass, Hipass, Bandpass]
	w_flt_cutoff0 = PRM w_flt_cutoff0;	//0..1000
	w_flt_cutoff1 = PRM w_flt_cutoff1;	//0..1000
}


//--------------------------------------------------------------
void SeaWord::setup(int id) {
	id_ = id;
	sound_.resize(Common::max_mic_rec_n());

}
//--------------------------------------------------------------
void SeaWord::run(const vector<float> &sound, int n, const SeaWordParam &param) {
	n_ = 0;	//stop sounding if any, will set to n below
	memcpy(sound_.data(), sound.data(), n*sizeof(float));

	param_ = param;

	//start sound
	n_ = n;
	is_live_ = true;

	MLOG("Sound " + ofToString(id_) + ": " + ofToString(1000 * n / Common::sample_rate()) + " msec");
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
	if (is_live()) {
		for (int i = 0; i < n; i++) {
			float v = sound_[i_++];
			i_ %= n_;

			stereo_buffer[2 * i] += v;
			stereo_buffer[2 * i + 1] += v;
		}

	}
	//for (int i = 0; i < n; i++) {
	//	stereo_buffer[2 * i] = stereo_buffer[2 * i + 1] = ofRandom(-0.05, 0.05);
	//}

}

//--------------------------------------------------------------
