#include "ofAppSecond.h"

AppSecond *APP_SECOND = 0;
extern shared_ptr<ofAppBaseWindow> *SECOND_WINDOW;

//--------------------------------------------------------------
void AppSecond::setup(){
	APP_SECOND = this;

	ofSetWindowShape(1024, 600);
	ofSetVerticalSync(false);
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

	int n = 6; //сколько рисовать дорожек
	//for (int )

	ofSetColor(255);
	ofFill();
	ofDrawRectangle(100, 100, 200, 100);
}

//--------------------------------------------------------------
