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

	rep_ = 0;

	//start sound
	n_ = n;
	is_live_ = true;

	MLOG("Sound " + ofToString(id_) + ": " + ofToString(1000 * n / SR) + " msec");
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
	int use_len = n_;//n_ - n_ * rep_/max_reps_;		//сокращаем длину
	float use_vol = ofMap(rep_, 0, max_reps_, 1, 0) * PRM REP_VOL;

	if (is_live()) {
		for (int i = 0; i < n; i++) {
			float v = (i_ < use_len) ? sound_[i_] : 0;
			i_++;
			if (i_ >= n_) {
				i_ %= n_;

				//repeat -----------------------------------
				stereo_pos_L_ = 0.5 + ofRandom(-param_.w_stereo_range, param_.w_stereo_range)/200.0f;	//0..1
				stereo_pos_R_ = 1 - stereo_pos_L_;

				rep_++;
				//MLOG("Repeat " + ofToString(id_) + ": " + ofToString(rep_));
				if (rep_ >= max_reps_) {
					is_live_ = false;
					//MLOG("Delete " + ofToString(id_));
					break;
				}
				//------------------------------------------
			}

			stereo_buffer[2 * i] += v * stereo_pos_L_ * use_vol;
			stereo_buffer[2 * i + 1] += v * stereo_pos_R_ * use_vol;
		}

	}
	//for (int i = 0; i < n; i++) {
	//	stereo_buffer[2 * i] = stereo_buffer[2 * i + 1] = ofRandom(-0.05, 0.05);
	//}

}

//--------------------------------------------------------------
