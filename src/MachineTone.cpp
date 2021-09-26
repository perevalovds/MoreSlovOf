#include "MachineTone.h"

#include "gui_generated.h"
#include "Morph.h"
#include "MachineDrums.h"
#include "SoundFX.h"

extern ofxKuTextGui gui;

//--------------------------------------------------
MachineTone::~MachineTone() {
    delete fft;
}

//--------------------------------------------------
 //также вызывается при восстановлении backup
void MachineTone::setup(int id, vector<float> &sound0, float BPM, ToneParams *params, bool backup_restore) {
	id_ = id;

	if (!backup_restore) {
		prm_ = params;
	}

    sound = sound0;
    
    N = sound.size();

	//thumb
	make_thumb();
    
    //live = true;
    
	if (!backup_restore) {
		add_backup(sound, thumb_);	//записываем в backup

		samples_per_bit = SR * 60 / (BPM * 4);    //сколько сэмплов в доле
	}

    vol = 0.5;
    pan = 0.5;
    flt = 0.5;

    lfo_vol.setup(TP voltype, TP volstp, 1/*TP vol*/, 0, TP volmov);
    lfo_pan.setup(TP pantype, TP panstp, 0.5/*TP pan*/, 0, TP panmov);
    //lfo_flt.setup(TON flttype, TON fltstp, TON flt, TON fltrnd, TON fltmov);
    
    //Play_Len = (repeats-1) * Loop_Len + N;
    update(0);
    
    play_pos = -1;
    grain_pos = 0;
    played_count = 0;
    sample = -Loop_Len + N;//+preSound/speed;    //запускаем чтобы был правильный повтор
    index_ = 0;
    //--------------
    //Спектр
	if (fft) delete fft;	 //если повторный вызов - то надо очистить (при восстановлени backup)
    fft = ofxFft::create(fft_n, OF_FFT_WINDOW_HAMMING); //OF_FFT_WINDOW_HANN);
    fft_pos = 0;
    fft_buffer.resize(fft_n);
    
    Phase_[0].resize(fft_n);
    Phase_[1].resize(fft_n);
    phase_prv_[0].resize(fft_n);
    phase_prv_[1].resize(fft_n);
    tempBuffer_[0].resize(fft_n);
    tempBuffer_[1].resize(fft_n);
    lastBuffer_.resize(fft_n);
    temp_.resize(fft_n);
    phase_.resize(fft_n);
    
    play_fft = 0;
    
    //--------------
    update(0);
}

//--------------------------------------------------
void MachineTone::update( float dt ) {
	//The reading from GUI and smoothing goes at ToneMachine::update

	//string name = ofToString(id_ + 1);
	
	//Read values from GUI
	//Also some value is smoothed
	Loop_Len = int(samples_per_bit * TP delay);
	
	pos_f = TP pos;
    len_f = TP len;
	speed_f = TP spd;
    grain_f = TP grain_len;
    mode = TP mode;
    
    
    pos_s = pos_f * N;
    len_s = len_f * SR;
    grain_s = grain_f * SR;
    speed_s = grain_s * speed_f;

    len_s = max(len_s,1);
    //speed_s = ofClamp(speed_s,0,1);
}

//--------------------------------------------------
void MachineTone::audioOut( StereoSample &out ) {
	switch (mode) {
	case 0: audioOut_grain(out);
		break;
	case 1: audioOut_spectr(out);
		break;
	case 2: audioOut_delay(out);
		break;
	case 3: audioOut_drum(out, 0);
		break;
	case 4: audioOut_drum(out, 1);
		break;
	default: out.clear();
	}

	//применяем морфинг
	MORPH.apply_to_audio(TP morph_id, morph_audio_counter_, TP morph_insensity, out);

	//применяем фильтр
	out.L = mic_filter_L.process(out.L, TP flt_cutoff, TP flt_mode);
	out.R = mic_filter_R.process(out.R, TP flt_cutoff, TP flt_mode);


	//применяем Vol и Pan
	out.L *= TP vol * (1 - TP pan); //громкость гасится из-за pan в 2 раза в центре
	out.R *= TP vol * (TP pan);

	//добавляем в эффекты
	SOUNDFX.send_sound(out, TP send_fx1, TP send_fx2);

	//обновляем громкость
	measure_vol_ = max(fabs(out.L) + fabs(out.R), measure_vol_*0.999f);


}

//--------------------------------------------------
inline void MachineTone::audio_lfo_next_value() {
	vol = lfo_vol.nextValue();
	pan = lfo_pan.nextValue();
	//flt = lfo_flt.nextValue();
	//cout << "index " << index << " pan " << pan << endl;
	
}

//--------------------------------------------------
void MachineTone::audioOut_delay( StereoSample &out ) {
	//next repeat
	if (sample >= Loop_Len) {
		audio_lfo_next_value();
		sample = 0; 
	}
        
    if (sample >= 0 && sample < N) {
        float v = sound[sample];
        
        out.L = v*vol*(1-pan); //громкость гасится из-за pan в 2 раза в центре
        out.R = v*vol*(pan);
    }
    //live = (sample < Play_Len);
	sample++;

}

//--------------------------------------------------
void MachineTone::audioOut_grain( StereoSample &out ) {
	//next repeat
	if (sample >= Loop_Len) {
		audio_lfo_next_value();
		sample = 0; 
        play_pos = pos_s;
        grain_pos = 0;
        //played_count = 0;
    }
    
    if (play_pos >= 0 && play_pos < pos_s + len_s) {
        if (play_pos < N) {
            float v = sound[play_pos];
            
            out.L = v*vol*(1-pan); //громкость гасится из-за pan в 2 раза в центре
            out.R = v*vol*(pan);
        }
        play_pos++;
        grain_pos++;
        //played_count++;
        if (grain_pos >= grain_s) { //кончилась гранула
            play_pos += (speed_s - grain_s);
            grain_pos = 0;
        }
        
    }
	sample++;
}

//--------------------------------------------------
void MachineTone::audioOut_drum(StereoSample &out, int kit) {
	//барабан - один звук звучит Loop_Len
	
	//первый звук будет неверный, но потом правильный

	//next repeat
	if (sample >= Loop_Len) {
		audio_lfo_next_value();
		sample = 0;

		index_ = (index_ + 1) % DrumBeats;
		play_pos = int(*DRUM_POS[kit][index_] * N);		//медленная операция
	}

	if (play_pos >= 0 && play_pos < N) {
		float v = sound[play_pos];

		out.L = v * vol*(1 - pan); //громкость гасится из-за pan в 2 раза в центре
		out.R = v * vol*(pan);

		play_pos++;
	}
	sample++;
}

//--------------------------------------------------
void MachineTone::audioOut_spectr( StereoSample &out ) {
    if (fft_pos==0) audioOut_make_buffer(); //обновление буфера
    
	//next repeat
	if (sample >= Loop_Len) {
		audio_lfo_next_value();
		sample = 0;
	}

    float v = fft_buffer[fft_pos];
    out.L = v*vol*(1-pan); //громкость гасится из-за pan в 2 раза в центре
    out.R = v*vol*(pan);
    fft_pos = (fft_pos+1) % fft_n;

	sample++;
}

//--------------------------------------------------
//Phase Vocoder C++
//https://github.com/stekyne/PhaseVocoder/blob/master/Source/PV.cpp
//m:  http://www.musicdsp.org/files/vocoder.m
//https://cycling74.com/2006/11/02/the-phase-vocoder-%E2%80%93-part-i/#.WLow4hBnT7s


void MachineTone::audioOut_make_buffer() {
    int n = fft_n;
    int n2 = n/2;
    
    int len_fft = min(pos_s+len_s + n, N);
    
    for (int Q=0; Q<2; Q++) {
        int pos = play_fft + n2*speed_f*Q + pos_s;
        for (int i=0; i<n; i++) {
            temp_[i] = sound[ (pos+i)%len_fft ]; //зацикливаем звук
        }
        fft->setSignal(&temp_[0]);
        memcpy(&phase_[0], fft->getPhase(), sizeof(float) * n);
        //вычисление приращения фазы
        for (int i=0; i<n; i++) {
            Phase_[Q][i] += phase_[i] - phase_prv_[Q][i];
        }
        phase_prv_[Q] = phase_;
        fft->setPolar(fft->getAmplitude(), &Phase_[Q][0]);
        //fft->clampSignal();
        memcpy(&tempBuffer_[Q][0], fft->getSignal(), sizeof(float) * n);
    }
    
    //наложение окон
    for (int i=0; i<n2; i++) {
        fft_buffer[i] = lastBuffer_[i+n2] + tempBuffer_[0][i];
        fft_buffer[i+n2] = tempBuffer_[0][i+n2] + tempBuffer_[1][i];
    }
    lastBuffer_ = tempBuffer_[1];
    
    //сдвиг положения воспроизведения
    play_fft += n*speed_f;
    
}

//--------------------------------------------------
void MachineTone::make_thumb() {
	int n = 100;		//TODO PARAM размер thumb
	thumb_.resize(n);
	fill(thumb_.begin(), thumb_.end(), 0);
	if (N == 0) return;
	for (int i = 0; i < N; i++) {
		auto &v = thumb_[i * n / N];
		v = max(v, sound[i]);
	}
}

//--------------------------------------------------
//рисовать звук и pos
void MachineTone::draw_thumb(int x, int y, int w, int h) {
	//рисуем в две строки
	if (x < 0) {
		x = *gui.findVarInt("thumb_x" + ofToString((id_%maxTones_part1) + 1));
		y = PRM thumb_y + (PRM thumb_h+20) * (id_/ maxTones_part1);
	}

	draw_thumb_(thumb_, x, y, TP pos, measure_vol_, w, h);
}

//--------------------------------------------------
void MachineTone::draw_thumb_(const vector<float> &thumb, int x, int y, float pos, float vol, int w, int h) {
	if (w < 0) w = PRM thumb_w;
	if (h < 0) h = PRM thumb_h;
	int h2 = h / 2;
	y += h2;

	float scly = PRM thumb_scl * h2;

	// border
	ofSetColor(200);
	ofNoFill();
	ofDrawRectangle(x, y-h2, w, 2*h2);
	
	// sound
	int n = thumb.size();
	if (n > 0) {
		for (int i = 0; i < w; i++) {
			int v = int(thumb[i*n/w] * scly);
			ofDrawLine(x + i, y - v, x + i, y + v);
		}
	}

	// pos
	if (pos >= 0) {
		ofSetColor(255, 0, 0);
		ofSetLineWidth(3);
		int p = pos * w;
		ofDrawLine(x + p, y - h2, x + p, y + h2);
		ofSetLineWidth(1);
	}

	// volume
	if (vol >= 0) {
		ofSetColor(255);
		ofFill();
		int p = vol * w * PRM thumb_vol;
		ofDrawRectangle(x, y + h2+2, p, 5);
	}
}

//--------------------------------------------------
void MachineTone::setup_backups(int n_backups) {	//хранить n_backups записанных звуков
	backup_n_ = n_backups;
}

//--------------------------------------------------
void MachineTone::load_sample(int k) {			//загрузить сэмпл в текущий воспроизводимый звук
	if (backups_.empty()) return;
	k = min(k, int(backups_.size()) - 1);
	bool backup_restore = true;
	setup(id_, backups_[k].sound, 0, 0, backup_restore);
}

//--------------------------------------------------
void MachineTone::draw_backups(int x, int y) {
	int h1 = PRM thumb_h;
	for (int i = 0; i < backups_.size(); i++) {
		draw_thumb_(backups_[i].thumb, x, y + h1 * i);
	}
}

//--------------------------------------------------
void MachineTone::add_backup(const vector<float> &sound, const vector<float> &thumb) {
	if (backup_n_ > 0) {
		Backup backup;
		backup.sound = sound;
		backup.thumb = thumb;
		backups_.push_back(backup);
		while (backups_.size() > backup_n_) {
			backups_.erase(backups_.begin());
		}
	}
}

//--------------------------------------------------

