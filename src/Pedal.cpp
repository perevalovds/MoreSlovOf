#include "Pedal.h"
#include "gui_generated.h"
#include "ofxKuMessageLog.h"

ofSerial arduino_;
int ard_connected_ = 0;

//--------------------------------------------------------------
void pedal_setup() {
	if (!PRM Arduino_Pedal) return;

	//перебор устройств для подключения
	bool inited = false;
	for (int i = 0; i < 32; i++) {
		string name = "COM" + ofToString(i);
		inited = arduino_.setup(name, ofToInt(PRM Pedal_baud));
		if (inited) {
			MLOG("Arduino connected at " + name, ofColor(0,200,0));
			ofSleepMillis(500);	//Ожидание после старта - чтобы началась работа
			ard_connected_ = 1;
			PRM Pedal_status_ = "Connected " + name;
			break;
		}
	}
	if (!ard_connected_) {
		MLOG("ERROR: Arduino NOT cnnected!", ofColor(255, 64, 64));
		PRM Pedal_status_ = "!!! Not connected !!!";
	}
}

//--------------------------------------------------------------
void pedal_update() {
	if (!PRM Arduino_Pedal) return;

	if (PRM Print_Arduinos) {
		MLOG("Connected COM devices (expect Arduino)");
		vector <ofSerialDeviceInfo> deviceList = arduino_.getDeviceList();
		vector<string> list;
		for (int i = 0; i < deviceList.size(); i++) {
			MLOG("    " + ofToString(i) + ": " + deviceList[i].getDeviceName());
		}

	}

	if (ard_connected_) {
		while (arduino_.available()) {
			int key = arduino_.readByte();
			if (key == '0') set_pedal_value((PRM Pedal_invert) ? 1 : 0);
			if (key == '1') set_pedal_value((PRM Pedal_invert) ? 0 : 1);
		}
	}
}

//--------------------------------------------------------------
void set_pedal_value(int v) {
	PRM PEDAL_ = v;
}

//--------------------------------------------------------------
