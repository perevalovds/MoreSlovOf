#include "Machines.h"
#include "ofxKuMessageLog.h"
#include "Common.h"
#include "ofxSoundUtils.h"
#include "gui_generated.h"

extern ofxKuTextGui gui;

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
void ToneMachine::draw_thumbs() {		//рисовать звуки
	for (int i = 0; i < maxTones; i++) {
		if (tone[i]) {
			tone[i]->draw_thumb();
		}
	}
}

//--------------------------------------------------
void ToneMachine::push_tone(int ton_number, vector<float> &sound, float BPM) {
	int i = ton_number;
	MLOG("Techno " + ofToString(i + 1));

	//Создание тона
	//если это последняя машина - то не пересоздаем
	bool is_backups = (i == maxTones - 1);
	MachineTone *ton = (is_backups) ? tone[i] : 0;
	if (!ton) {
		ton = new MachineTone();
	}
	if (is_backups) {
		ton->setup_backups(PRM Backups7);
	}

	//Запуск тона
	ton->setup(i, sound, BPM, &params_[i]);

	//удаляем старую
	MachineTone *temp = tone[i];
	tone[i] = ton;	//сначала переключаем, а потом удаляем, чтобы звук не выдал ошибку!
	if (!is_backups && temp) {
		delete temp;
	}
	
	index = i;

	shared_pushed = true;
}

//--------------------------------------------------
void ToneMachine::update(float dt) {
	//считывание параметров
	for (int i = 0; i < maxTones; i++) {
		auto &p = params_[i];
		string name = ofToString(i + 1);

		//Громкость 
		float vol = *gui.findVarFloat("w_vol" + name);
		vol = ofxSoundUtils::volume_linear_to_exp(vol);	//экспонента
		vol *= (1 + *gui.findVarStringList("w_louder" + name));//опционально увеличиваем с помощью дополнительного флажка "w_louder" - Solo / Que на APC40
		p.vol = vol;
		
		p.pan = *gui.findVarFloat("w_pan" + name);

		p.mode = *gui.findVarStringList("w_mode" + name);

		p.delay = Common::w_delay(*gui.findVarStringList("w_delay" + name));
		p.pos = *gui.findVarFloat("w_pos" + name);
		
		float len = *gui.findVarFloat("w_len" + name);
		//нелинейность и диапазон
		p.len = ofMap(len*len, 0, 1, 0.01, 5);	


		float spd = *gui.findVarFloat("w_spd" + name);
		//нелинейность
		p.spd = spd*spd;

		float grain_len = *gui.findVarFloat("w_grain_len" + name);
		//нелинейность
		p.grain_len = (grain_len/0.1)*(grain_len / 0.1)*0.1;

		p.voltype = *gui.findVarStringList("w_voltype" + name);
		p.volstp = *gui.findVarInt("w_volstp" + name);
		p.volmov = *gui.findVarFloat("w_volmov" + name);
		p.pantype = *gui.findVarStringList("w_pantype" + name);
		p.panstp = *gui.findVarInt("w_panstp" + name);
		p.panmov = *gui.findVarFloat("w_panmov" + name);

		p.flt_mode = *gui.findVarStringList("w_flt" + name);

		float cutoff = *gui.findVarFloat("w_cutoff" + name);
		//нелинейность и диапазон
		cutoff = ofMap(cutoff, 0, 1, 0.11, 1);
		p.flt_cutoff = ofMap(cutoff*cutoff, 0, 1, 0.003, 1);
		//cout << "cutoff " << cutoff << " " << p.flt_cutoff << endl;
	}


    for (int i=0; i<n; i++) {
        if (tone[i]) tone[i]->update(dt);
    }
}

//--------------------------------------------------
void ToneMachine::audioOut(StereoSample &out_sample) {
	out_sample.clear();

    for (int i=0; i<n; i++) {
        MachineTone *ton = tone[i];
        if (ton) {           
			StereoSample out1;
			ton->audioOut(out1);
			out_sample.L += out1.L;
            out_sample.R += out1.R;            
        }
    }
}

//--------------------------------------------------
