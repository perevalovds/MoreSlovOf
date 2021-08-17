#include "MachineTone.h"

//--------------------------------------------------
MachineTone::~MachineTone() {
    delete fft;
}

//--------------------------------------------------
void MachineTone::setup(vector<float> &sound0, float BPM, ToneParams *params) {
    prm_ = params;
    
    sound = sound0;
    
    N = sound0.size();
    
    //live = true;
    
    samples_per_bit = SR * 60 / (BPM*4);    //сколько сэмплов в доле
    
    vol = 0.5;
    pan = 0.5;
    flt = 0.5;

    lfo_vol.setup(TP voltype, TP volstp, TP vol, 0, TP volmov);
    lfo_pan.setup(TP pantype, TP panstp, TP pan, 0, TP panmov);
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
    
    pos_f = TP pos;
    len_f = TP len;
    speed_f = TP spd;
    grain_f = TP grain_len;
    mode = TP mode;
    
    Loop_Len = samples_per_bit * TP delay;

    
    pos_s = pos_f * N;
    len_s = len_f * SR;
    grain_s = grain_f * SR;
    speed_s = grain_s * speed_f;

    len_s = max(len_s,1);
    //speed_s = ofClamp(speed_s,0,1);
}

//--------------------------------------------------
void MachineTone::audioOut( StereoSample &out ) {
    if (mode == 0) { audioOut_delay(out); return; }
    if (mode == 1) { audioOut_grain(out); return; }
    if (mode == 2) { audioOut_spectr(out); return; }
    
    return;
}

//--------------------------------------------------
void MachineTone::audioOut_delay( StereoSample &out ) {
    int index = (sample+Loop_Len) / Loop_Len;
    //новый повтор
    if (index_ != index) {
        index_ = index;
        vol = lfo_vol.nextValue();
        pan = lfo_pan.nextValue();
        //flt = lfo_flt.nextValue();
        //cout << "index " << index << " pan " << pan << endl;
    }
    
    int i = (sample+Loop_Len) % Loop_Len;
    sample++;
    
    int u0 = i;
    if (u0 >= 0 && u0 < N) {
        float v = sound[u0];
        
        out.L = v*vol*(1-pan); //громкость гасится из-за pan в 2 раза в центре
        out.R = v*vol*(pan);
    }
    //live = (sample < Play_Len);
}

//--------------------------------------------------
void MachineTone::audioOut_grain( StereoSample &out ) {
    int index = (sample+Loop_Len) / Loop_Len;
    sample++;
    //новый повтор
    if (index_ != index) {
        index_ = index;
        vol = lfo_vol.nextValue();
        pan = lfo_pan.nextValue();
        //flt = lfo_flt.nextValue();
        //cout << "index " << index << " pan " << pan << endl;
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
    //live = (sample < Play_Len);
}

//--------------------------------------------------
void MachineTone::audioOut_spectr( StereoSample &out ) {
    if (fft_pos==0) audioOut_make_buffer(); //обновление буфера
    
    int index = (sample+Loop_Len) / Loop_Len;
    sample++;
    //новый повтор
    if (index_ != index) {
        index_ = index;
        vol = lfo_vol.nextValue();
        pan = lfo_pan.nextValue();
        //play_pos = pos_s;
    }
    
    float v = fft_buffer[fft_pos];
    out.L = v*vol*(1-pan); //громкость гасится из-за pan в 2 раза в центре
    out.R = v*vol*(pan);
    fft_pos = (fft_pos+1) % fft_n;
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
