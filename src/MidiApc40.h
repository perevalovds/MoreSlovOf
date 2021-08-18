#pragma once

#include "ofMain.h"
#include "ofxMidi.h"



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


	/*
    //Novation launchpad
    //определить, какая кнопка нажата от 0 до 63
    static int launchpad_parse_button(int pitch);

    //включить освещение LED, btn от 0 до 63, green,red - от 0 до 1
    void launchpad_set_led(int btn, float red, float green);
	*/
};


extern MidiApc40 APC40;