#include "Machines.h"
#include "ofxKuMessageLog.h"

ToneMachine MACHINE;

//--------------------------------------------------
ToneMachine::ToneMachine() {
    n = maxTones;
    for (int i=0; i<n; i++) {
        tone[i] = 0;
    }
    index = 0;

	params_.resize(maxTones);
}

//--------------------------------------------------
void ToneMachine::setup() {
    shared_pushed = false;
}
    
//--------------------------------------------------
void ToneMachine::push_tone(int ton_number, int type, vector<float> &sound, float BPM) {
	MLOG("Techno " + ofToString(ton_number + 1));

	//Создание тона
    MachineTone *ton = new MachineTone();

    //Запуск тона
    if (ton) {
        int i = ton_number;
        ton->setup(sound, BPM, &params_[i]);
        //tone.push_back(ton);
        bool ok = false;
        
        MachineTone *temp = tone[i];
        tone[i] = ton;
        if (temp) {
            delete temp;
        }
        index = i;
        
    }
    shared_pushed = true;
}

//--------------------------------------------------
void ToneMachine::update(float dt) {
    for (int i=0; i<n; i++) {
        if (tone[i]) tone[i]->update(dt);
    }
}

//--------------------------------------------------
void ToneMachine::audioOut(float *out_sample, float vol) {
    StereoSample out;
    int k = 0;
    for (int i=0; i<n; i++) {
        MachineTone *ton = tone[i];
        if (ton) {
            out.L = out.R = 0;
            ton->audioOut(out);
            out_sample[k++] = out.L * vol;
            out_sample[k++] = out.R * vol;
            
            //удаляем отработавшие
            //if (!ton->live) {
            //    tone[i] = 0;
            //    delete ton;
            //}
        }
        else {
            out_sample[k++] = 0;
            out_sample[k++] = 0;
        }
    }

}

//--------------------------------------------------
