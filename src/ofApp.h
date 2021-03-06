#pragma once

//Демоны второй природы
//Программа для трансформации звука с помощью ИИ

#include "ofMain.h"
#include "ofxKuTextGui.h"
#include "Common.h"

class ofApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();

	void load();
	void save();
	void exit();
	void flash(ofColor color = ofColor(255));

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	float flash_ = 0;
	ofColor flash_color_;
	int show_gui = 1;
	float time0_ = 0;

	int gui_was_shown = 0;
	void update_buttons();  //нажатия кнопок

	//Экран
	void setup_screen();
	bool screen_was_setup_ = false;	//раз обновляем экран через 1 сек после старта - для второго окна
	bool was_borderless = false;	//для переключение режима borderless
	void restore_screen();		//восстановление экрана - помещение в 0,0 и нормальный размер

};
