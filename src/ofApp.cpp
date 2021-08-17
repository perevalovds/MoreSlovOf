#include "ofApp.h"

#include "ofxKuTextGuiGen.h"
#include "ofxKuFile.h"
#include "gui_generated.h"
#include "ofxKuMessageLog.h"
#include "SoundEngine.h"
#include "Pedal.h"
#include "Sea.h"
#include "Pedal.h"
#include "Common.h"

string app_ver = "v.01 (64 bit, autosave off)";
string Title = "MoreSlov " + app_ver;
string Title_RU = "МореСлов " + app_ver;

//--------------------------------------------------------------
void ofApp::setup() {
	cout << "------------------------------------------" << endl;
	MLOG(Title_RU, Title);
	MLOG("Press Enter to clear logs");

	cout << "Press Enter to clear logs" << endl;
	cout << "    Space - Pedal" << endl;
	cout << "    Shift+F - toggle fullscreen, Shift+Q - restore borderless screen" << endl;
	cout << "1,2,Shift+1,2 - select page, cursor - select value, [,],{,},mouseL/R - change value" << endl;
	cout << "s - save settings, l - load settings" << endl;
	cout << "------------------------------------------" << endl;
	cout << endl;

	ofSetWindowTitle(Title);

	//----------------------------
	//GUI
	PRM setup(gui, "param.ini");
	//gui.set_tab_w(140, 10, -10.5);
	//gui.set_tab_h(20, 2, -14.5);

	//cout << "NOTE: Disabled editing strings in GUI, so please directly edit ini files" << endl;
	//gui.set_editing_strings(false);

	//gui.setPage(0); //переход на начальную страницу

	show_gui = 1;

	//----------------------------
	//Сообщения на экран
	ofxKuMessageLogParams prm;
	prm.capacity = PRM messages_n;
	prm.pos = ofPoint(PRM messages_x, PRM messages_y);
	prm.font_size = PRM messages_font; 
	prm.color = ofColor(140);
	MLOGGER.setup("fonts/Arial Unicode.ttf");
	MLOGGER.set_parameters(prm);


	//----------------------------
	//Screen
	setup_screen();

	//----------------------------
	//Sound & content
	Common::setup();

	pedal_setup();
	SEA.setup();
	SOUND.setup();

	//----------------------------
	MLOG("Работа...", "Working...");

}


//--------------------------------------------------------------
void ofApp::setup_screen() {
	//берем переменные не "FPS", а "_FPS_" - то есть значения, 
	//которые моглы бы быть изменены пользователем - это на перспективу динамической подстройки параметров
	ofSetFrameRate(PRM _FPS_);

	int full_scr = PRM _FULL_SCR_;
	bool no_fullscr = full_scr == 0;
	bool borderless = full_scr == 1;
	bool pure_fullscr = full_scr == 2;

	ofSetWindowPosition(PRM _scr_x_, PRM _scr_y_);

	if (no_fullscr) {
		ofSetFullscreen(false);
		ofSetWindowShape(PRM _scr_w_, PRM _scr_h_);
	}

	if (pure_fullscr) {
		ofSetFullscreen(true);
	}

	//восстановление из borderless - выдаем предупреждение, что надо перезагрузить приложение
	if (no_fullscr && was_borderless) {
		//Сейчас закомментировано - не восстанавливаем заголовок, 
		//а выдаем сообщение с просьбой перезагрузить приложение, 
		//так как после RestoreMainWindowBorder по Y мышь выдает неправильные координаты
		//ofxKuOsWindows::RestoreMainWindowBorder(); 

		ofxKuMessageLogBigMessage big;
		big.message = "Для восстановления заголовка окна,\nнажмите Save и перезапустите приложение";
		big.message_console = "To restore window's caption, click Save and restart app";
		float W = ofGetWidth();
		float H = ofGetHeight();
		float w = max(500.0f, W / 2);
		float h = max(200.0f, H / 2);
		big.rect = ofRectangle(W / 2 - w / 2, H / 2 - h / 2, w, h);
		big.font_size = 30;
		big.color_font = ofColor(255, 255, 0);
		big.color_back = ofColor(64, 64, 64);
		MLOGGER.big_message(big);
	}
	if (borderless) was_borderless = true;

}

//--------------------------------------------------------------
void ofApp::restore_screen() {		//восстановление экрана - помещение в 0,0 и нормальный размер
	int full_mode = PRM _FULL_SCR_;
	PRM _FULL_SCR_ = 0;
	setup_screen();
	PRM _FULL_SCR_ = full_mode;
	
}

//--------------------------------------------------------------
void ofApp::load() {
	gui.loadFromFile("param.ini");
	flash();
}

//--------------------------------------------------------------
void ofApp::save() {
	PRM save();
	flash();
}

//--------------------------------------------------------------
void ofApp::flash() {
	flash_ = 1;
}

//--------------------------------------------------------------
void ofApp::exit() {
	cout << "Exiting..." << endl;
	//save();

	//Sound
	SOUND.exit();
	

}

//--------------------------------------------------------------
void ofApp::update_buttons() {  //нажатия кнопок
	
	//if (PRM Close) {
	//	show_gui = 0;
	//}
	if (PRM ClearLog) {
		MLOGGER.clear();
	}

	if (PRM Save) {
		save();
	}
	if (PRM Exit) {
		ofExit(0);
	}

	if (PRM update_scr) {
		setup_screen();
	}

}
//--------------------------------------------------------------
void ofApp::update(){
	float dt = 1.0 / PRM FPS;	//фиксированный dt для точного моделирования

	//----------------------------
	//GUI
	if (flash_ > 0) flash_ -= dt / 0.3;

	PRM fps_ = int(ofGetFrameRate());

	gui.update();     //GUI
	update_buttons(); //кнопки

	//----------------------------
	//Sound & content
	pedal_update();
	SEA.update(dt);
	SOUND.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);

	float w = ofGetWidth();
	float h = ofGetHeight();
	
	//------------------
	SOUND.draw();

	//------------------
	if (show_gui) {
		int w = ofGetWidth();
		int h = ofGetHeight();

		//Затемняем фон
		ofSetColor(0, 160);
		ofFill();
		ofDrawRectangle(0, 0, w, h);

		gui.draw(20, 20, true, 255, 255);	//draw gui
		ofShowCursor();		//show mouse

		//Сообщения
		ofSetColor(255);
		ofFill();

		if (gui.pageTitle() != "Sea") {
			MLOGGER.draw();
		}
	}
	else {
		ofHideCursor();	//hide mouse
	}

	//вспышка
	if (flash_ > 0) {
		ofSetColor(255, flash_ * 128);
		ofFill();
		ofRect(0, 0, w, h);
	}


	//string page = gui.pageTitle();
	//bool perf = page == "Performance";


}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
	//if (key == VK_ESCAPE) {			//Выход
	//	ofExit();
	//}

	if (key == ' ') set_pedal_value(1);	//Pedal

	if (key == OF_KEY_RETURN) MLOGGER.clear(); //сброс логов


	if (key == 'Q') {	//восстановление экрана
		restore_screen();
	}

	if (key == 'F') ofToggleFullscreen();

	//Если нет окна настроек - то не реагировать на остальную клавиатуру
	if (!show_gui) return;

	//Ставим обработку клавиш gui здесь 
	//- так как они перехватывают '1' и '2' - которые используем для имитации кнопок
	if (show_gui) {
		if (gui.keyPressed(key)) return;
	}



	if (key == 'G') {   //Generate .H and .CPP files for parameters
		ofxKuTextGuiGen::generateCPP("gui/gui-script.ini",
			"../../src/", "gui_generated",
			"Parameters", "params", "PRM");
		flash();
	}
	if (key == 's') {							//записать параметры в файл
		save();
	}
	if (key == 'L') {							//загрузить параметры из файла
		load();
	}


}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){
	if (key == ' ') set_pedal_value(0);	//Pedal

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (show_gui) gui.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (!show_gui && button == 2) {	//если нажали правую клавишу мыши - то показ настроек
		show_gui = 1;
		return;
	}
	if (show_gui) gui.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (show_gui) gui.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}



//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
