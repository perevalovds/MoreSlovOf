#include "ofAppSecond.h"
#include "Machines.h"
#include "gui_generated.h"

AppSecond *APP_SECOND = 0;
extern shared_ptr<ofAppBaseWindow> *SECOND_WINDOW;

//--------------------------------------------------------------
void AppSecond::setup(){
	APP_SECOND = this;

	ofSetWindowShape(1024, 600);
	ofSetVerticalSync(false);

	font_.load("fonts/verdana", 20);
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
	int sample_h = H_ / 5;
	int circle_h = H_ / 5;


	//дорожки
	for (int k = 0; k < n+1; k++) {
		auto *tone = MACHINE.tone[k];
		int w = get_w(k);
		ofPushMatrix();
		ofTranslate(pos_x(k), 0);
		//сэмпл
		if (tone) {
			tone->draw_thumb(0, 0, w, sample_h);
		}
		//запись
		int y = sample_h;
		if (k == PRM REC) {
			ofSetColor(255, 0, 0);
			ofFill();
			ofDrawCircle(w / 2, y + circle_h / 2, w / 6);
		}
		y += circle_h;
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
float AppSecond::pos_x(int k) {
	return ofMap(k, 0, n + 0.5, 0, W_);
}

//--------------------------------------------------------------
float AppSecond::get_w(int k) {
	return ((k < n) ? 1.0f : 0.5f) / (n+0.5f) * W_;
}

//--------------------------------------------------------------

