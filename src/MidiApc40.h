#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "Common.h"


class MidiApc40 : public ofxMidiListener {	
public:
	void setup();
	void update();
	void draw(float x, float y);
	void exit();
	
protected:
	void newMidiMessage(ofxMidiMessage& eventArgs);
	
	stringstream text;
	
    bool input;
    bool output;
    
	ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;
    
    ofxMidiOut midiOut;

	int find_index(string name_part, vector<string> list);

	void midi_in_note(int port, int channel, int pitch, int onoff, int velocity);
	void midi_in_ctrl(int port, int channel, int ctrl, int value);

	//установка значений в GUI
	void set_int(string name, int ch, int midi_val, int max_val);
	void set_stringlist(string name, int ch, int midi_val, int max_val);
	void set_float(string name, int ch, int midi_val, float max_val);
	void set_float(string name, int ch, int midi_val, float min_val, float max_val);

	//отправка данных
	//void set_apc40_mode();
	//void test_send();
};


extern MidiApc40 APC40;