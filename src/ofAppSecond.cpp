#include "ofAppSecond.h"
#include "Machines.h"
#include "gui_generated.h"

AppSecond *APP_SECOND = 0;
extern shared_ptr<ofAppBaseWindow> *SECOND_WINDOW;

extern ofxKuTextGui gui;

//--------------------------------------------------------------
void AppSecond::setup(){
	APP_SECOND = this;

	ofSetWindowShape(1024, 600);
	ofSetVerticalSync(false);

	font_.load("fonts/verdana.ttf", 30);
}

//--------------------------------------------------------------
void AppSecond::set_screen_size(int x, int y, int w, int h) {
	if (SECOND_WINDOW) {
		shared_ptr<ofAppBaseWindow> &ptr = *SECOND_WINDOW;
		ptr->setWindowPosition(x, y);
		ptr->setWindowShape(w, h);
	}
	else {
		cout << "Can't set AppSecond::set_screen_size - window is NULL" << endl;
	}
}

//--------------------------------------------------------------
void AppSecond::update(){

}

//--------------------------------------------------------------
void AppSecond::draw(){
	ofBackground(64);

	//ставим размеры для использования
	W_ = ofGetWidth();
	H_ = ofGetHeight();
	int step1 = H_ / 5;
	int step6 = H_ / 6;
	int step2 = H_ / 8;
	int step3 = H_ / 10;
	int step16 = H_ / 16;

	int sample_h = step1;
	int id_h = step2;
	int circle_h = step2;

	int morph_h = step2;
	int vol_h = step6;


	//дорожки
	for (int k = 0; k < n+1; k++) {		//n+1, чтобы показать 7-й трек
		auto *tone = MACHINE.tone[k];
		int w = get_w(k);
		ofPushMatrix();
		ofTranslate(pos_x(k), 0);
		//если выделенная дорожка - то рисуем фон
		if (k == PRM EDIT_ - 1) {
			ofSetColor(70,100,70);
			ofFill();
			ofDrawRectangle(0, 0, w, H_);

			ofSetColor(255);
			ofNoFill();
			ofDrawRectangle(1, 1, w-2, H_-2);
		}

		//сэмпл
		if (tone) {
			tone->draw_thumb(0, 0, w, sample_h);
		}
		int y = sample_h;
		//номер
		ofSetColor(255);
		font_.drawString(ofToString(k + 1), w / 2, y + id_h / 2);
		y += id_h;

		//запись
		if (k == PRM REC) {
			ofSetColor(255, 0, 0);
			ofFill();	
			int circle_r = w / 12;
			ofDrawCircle(w / 2, y, circle_r);
		}
		y += step16;

		//len
		string name = ofToString(k + 1);
		float len = *gui.findVarFloat("w_len" + name);
		ofSetColor(len > 0.05 ? ofColor(150) : ofColor(255, 255, 0));
		font_.drawString("len " + ofToString(len,3), 20, y + step16 / 2);
		ofLine(0, y + step16, w * len, y + step16);
		y += step16;

		//morph и тип
		
		float morph = gui.getSmoothedValue("w_percent" + name) / 100.0f;
		int type = *gui.findVarStringList("w_mode" + name);

		if (morph > 0) {
			ofSetColor(0,255,0,morph*255.0f);
			font_.drawString("morph", 20, y + morph_h / 2);
		}
		y += morph_h;

		string type_str;
		if (type == 0) {
			type_str = "Grain";
			ofSetColor(200, 200, 100);
		}
		if (type == 1) {
			type_str = "Spectr";
			ofSetColor(100, 100, 200);
		}
		if (type == 2) {
			type_str = "Repeat";
			ofSetColor(150);
		}
		if (type == 3) {
			type_str = "Drum1";
			ofSetColor(100, 200, 200);
		}
		if (type == 4) {
			type_str = "Drum2";
			ofSetColor(100, 200, 200);
		}
		font_.drawString(type_str, 20, y + morph_h / 2);
		y += morph_h;


		//громкость
		float vol = (k < n) ? *gui.findVarFloat("w_vol" + name) : PRM w_volMix7;	//TODO еще выдавать 8ю
		{
			int yv1 = H_ - vol_h - 10;
			int yv0 = yv1 + vol_h;
			ofSetColor(160);
			ofFill();
			int xc = w / 2;
			ofDrawRectangle(xc - 1.5, yv0, 3, -vol_h);


			ofSetColor(255);
			int y = int(ofMap(vol, 0, 1, yv0, yv1));
			ofDrawRectangle(xc - w / 8, y-2, w / 8 * 2, 2);


			//Delay faders
			int delay_r = w / 8;
			float delay1 = *gui.findVarFloat("w_fxA" + name);
			float delay2 = *gui.findVarFloat("w_fxB" + name);
			ofSetColor(230);
			draw_fader(w / 4, yv1 - delay_r * 1, delay_r, delay1);
			draw_fader(3*w / 4, yv1 - delay_r * 1, delay_r, delay2);


		}

		ofPopMatrix();
	}

	//разметочные линии
	ofSetColor(200);
	for (int k = 0; k < n+1; k++) {
		float x = int(pos_x(k))+0.5;
		ofDrawLine(x, 0, x, H_);
	}

}

//--------------------------------------------------------------
void AppSecond::draw_fader(int x, int y, int r, float value) {
	ofNoFill();
	ofDrawCircle(x, y, r);
	float angl = ofMap(value, 0, 1, (270 - 30) * DEG_TO_RAD, (-90 + 30) * DEG_TO_RAD);
	float dx = r * cos(angl);
	float dy = -r * sin(angl);
	ofDrawLine(x, y, x + dx, y + dy);
}

//--------------------------------------------------------------
float AppSecond::pos_x(int k) {
	return ofMap(k, 0, n + 0.5, 0, W_);
}

//--------------------------------------------------------------
float AppSecond::get_w(int k) {
	return ((k < n) ? 1.0f : 0.5f) / (n+0.5f) * W_;
}

//--------------------------------------------------------------

