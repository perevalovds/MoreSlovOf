#include "Machines.h"
#include "ofxKuMessageLog.h"
#include "Common.h"
#include "ofxSoundUtils.h"
#include "gui_generated.h"
#include "MachineDrums.h"

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

	//барабаны
	drums_setup();

	//создаем все дорожки - в первую очередь, чтобы вторая часть принимала сэмплы из backup
	vector<float> empty_sound(1000);
	for (int i = 0; i < maxTones; i++) {
		push_tone(i, empty_sound); // , PRM BPM * 2);	//*2 - так как в других местах так делаем
	}


	
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
void ToneMachine::push_tone(int ton_number, vector<float> &sound) {
	int i = ton_number;
	//MLOG("Techno " + ofToString(i + 1));

	//Создание тона
	//если это 7-я машина - то не пересоздаем
	bool is_backups = (i == maxTones_part1);
	MachineTone *ton = (is_backups) ? tone[i] : 0;
	if (!ton) {
		ton = new MachineTone();
	}
	if (is_backups) {
		ton->setup_backups(PRM Backups7);
	}

	//Запуск тона
	ton->setup(i, sound, &params_[i]);

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
	//обновление барабанов
	drums_update(dt);

	//считывание параметров
	for (int i = 0; i < maxTones; i++) {
		auto &p = params_[i];
		string name = ofToString(i + 1);

		//модуляция только для первой части дорожек
		int mod = (i < maxTones_part1 && *gui.findVarStringList("Variate" + name));	//включена ли модуляция

		//Volume
		float vol = *gui.findVarFloat("w_vol" + name);

		if (i >= 7 - 1 && i <= 10 - 1) vol *= PRM w_volMix7;		//модуляция дорожек 7,8,9,10 с дорожки 7 микшера
		if (i >= 11 - 1 && i <= 12 - 1) vol *= PRM w_volMix8;		//модуляция дорожек 11,12 с дорожки 8 микшера

		if (mod) vol = ofClamp(vol + *gui.findVarFloat("v_vol" + name), 0, 1); //модуляция
		vol = ofxSoundUtils::volume_linear_to_exp(vol);	//экспонента
		vol *= (1 + *gui.findVarStringList("w_louder" + name));//опционально увеличиваем с помощью дополнительного флажка "w_louder" - Solo / Que на APC40
		p.vol = vol;
		//cout << "vol " << i << " " << vol << endl;
		
		//BPM
		int bpm_index = *gui.findVarStringList("TEMP" + name);
		p.bpm = ((bpm_index == 0) ? PRM BPM_1 : PRM BPM_2) * 2;	//умножаем на 2, чтобы побольше скорость


		//Pan
		p.pan = *gui.findVarFloat("w_pan" + name);
		if (mod) p.pan = ofClamp(p.pan + *gui.findVarFloat("v_pan" + name), -1, 1);	//модуляция

		//Effects
		p.send_fx1 = *gui.findVarFloat("w_fxA" + name);
		p.send_fx2 = *gui.findVarFloat("w_fxB" + name);

		//Mode
		p.mode = *gui.findVarStringList("w_mode" + name);


		//Loop delay, smoothed
		float pdelay_log2_raw = 6 - gui.updateSmoothedValue("w_delay" + name, dt, PRM smth_delay_sec);
		//0 -> 1
		//6 -> 64
		p.delay = pow(2, pdelay_log2_raw);
		//cout << i << " " << p.delay << endl;

		//дорожки 7..12 - дополнительно удлиняются
		if (i >= maxTones_part1) {
			p.delay *= *gui.findVarFloat("w_delay" + name + "kf");
		}

		//Position
		p.pos = *gui.findVarFloat("w_pos" + name);
		if (mod) p.pos = ofClamp(p.pos + *gui.findVarFloat("v_pos" + name), 0, 1); //модуляция

		//Length
		float len = *gui.findVarFloat("w_len" + name);
		//диапазон
		p.len = ofMap(len, 0, 1, 0.01, 1);
		//нелинейность и диапазон
		//p.len = ofMap(len*len, 0, 1, 0.01, 5);	

		//Grain speed
		float spd = gui.updateSmoothedValue("w_spd" + name, dt, PRM smth_spd_sec); //*gui.findVarFloat("w_spd" + name);
		if (mod) spd = ofClamp(spd + *gui.findVarFloat("v_spd" + name), 0, 1); //модуляция

		//нелинейность
		p.spd = spd*spd;

		//Grain length
		float grain_len = gui.updateSmoothedValue("w_grain_len" + name, dt, PRM sm_gr_len_sec); //*gui.findVarFloat("w_grain_len" + name);
		if (mod) grain_len = ofClamp(grain_len + *gui.findVarFloat("v_grain_len" + name)*0.1, 0, 1); //модуляция

		//нелинейность
		p.grain_len = (grain_len/0.1)*(grain_len / 0.1)*0.1;

		//Variations
		p.voltype = *gui.findVarStringList("w_voltype" + name);
		p.volstp = *gui.findVarInt("w_volstp" + name);
		p.volmov = *gui.findVarFloat("w_volmov" + name);
		p.pantype = *gui.findVarStringList("w_pantype" + name);
		p.panstp = *gui.findVarInt("w_panstp" + name);
		p.panmov = *gui.findVarFloat("w_panmov" + name);
		p.flttype = *gui.findVarStringList("w_flttype" + name);
		p.fltstp = *gui.findVarInt("w_fltstp" + name);
		p.fltmov = *gui.findVarFloat("w_fltmov" + name);

		//Morph
		p.morph_id = *gui.findVarStringList("w_morph" + name);
		p.morph_insensity = gui.updateSmoothedValue("w_percent" + name, dt, PRM sm_morph_sec) / 100.0f; //*gui.findVarInt("w_percent" + name) / 100.0f;

		//Filter type
		p.flt_mode = *gui.findVarStringList("w_flt" + name);

		//Filter freq
		float cutoff = *gui.findVarFloat("w_cutoff" + name);
		if (mod) cutoff = ofClamp(cutoff + *gui.findVarFloat("v_cutoff" + name), 0, 1); //модуляция

		//нелинейность и диапазон
		cutoff = ofMap(cutoff, 0, 1, 0.11, 1);
		p.flt_cutoff = ofMap(cutoff*cutoff, 0, 1, 0.003, 1);
		//cout << "cutoff " << cutoff << " " << p.flt_cutoff << endl;
	}

	//Update tones
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
