#include "MidiApc40.h"
#include "ofxKuMessageLog.h"
#include "gui_generated.h"
#include "Machines.h"

extern ofxKuTextGui gui;

MidiApc40 APC40;


//--------------------------------------------------------------
void MidiApc40::setup() {
	PRM log_midi = 0;	//отключаем печать всех сообщений MIDI

	input = true; 
	output = true; 
    
    if (input) {
		bool result = true;
		auto list = midiIn.getInPortList();
		int i = find_index(PRM APC_midi_in, list);
		if (i < 0) {
			result = false;
			MLOG("No MIDI IN device " + PRM APC_midi_in, ofColor(255, 0, 0));
		}
		if (result) result = midiIn.openPort(i);
		if (!result) {
			MLOG("Can't open MIDI IN device " + PRM APC_midi_in, ofColor(255, 0, 0));
		}
        //midiIn.openPort("IAC Pure Data In");	// by name
        //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
	
        // don't ignore sysex, timing, & active sense messages,
        // these are ignored by default
        //midiIn.ignoreTypes(false, false, false);
	
        // add this class a listener
		if (result) {
			MLOG("Started MIDI IN device " + list[i], ofColor(0,200,0));
			midiIn.addListener(this);
		}
		input = result;
        // print received messages to the console
        //midiIn.setVerbose(true);
    }
    
	if (output) {
		bool result = true;
		auto list = midiOut.getOutPortList();
		int i = find_index(PRM APC_midi_out, list);
		if (i < 0) {
			result = false;
			MLOG("No MIDI OUT device " + PRM APC_midi_out, ofColor(255, 0, 0));
		}
		if (result) result = midiOut.openPort(i);
		if (!result) {
			MLOG("Can't open MIDI OUT device " + PRM APC_midi_out, ofColor(255, 0, 0));
		}
		if (result) {
			MLOG("Started MIDI OUT device " + list[i], ofColor(0,200,0));
		}
		output = result;
	}
	PRM APC_status_ = (input && output) ? "Connected" : "NOT Connected !!!";
}

//--------------------------------------------------------------
int MidiApc40::find_index(string name_part, vector<string> list) {
	for (int i = 0; i < list.size(); i++) {
		if (ofIsStringInString(list[i], name_part)) return i;
	}
	return -1;
}

//--------------------------------------------------------------
void MidiApc40::update() {
	if (PRM Print_MIDI) {
		MLOG("Connected MIDI IN devices (expect APC40)");
		auto list = midiIn.getInPortList();
		for (int i = 0; i < list.size(); i++) {
			MLOG("    " + ofToString(i) + ": " + list[i]);
		}

	}
}

//--------------------------------------------------------------
void MidiApc40::draw(float x, float y) {
    if (input) {
        
        ofPushMatrix();
        ofTranslate(x,y);
        
        // draw the last received message contents to the screen
        text << "Midi status: " << ofxMidiMessage::getStatusString(midiMessage.status);
        ofDrawBitmapStringHighlight(text.str(), 0, 0);
        text.str(""); // clear
        
        text << "port/chn: " << midiMessage.portNum << " / " << midiMessage.channel;
        ofDrawBitmapStringHighlight(text.str(), 0, 15);
        text.str(""); // clear
        
        text << "pitch/vel: " << midiMessage.pitch << " / " << midiMessage.velocity;
        ofDrawBitmapStringHighlight(text.str(), 0, 30);
        text.str(""); // clear
        
        text << "control/value: " << midiMessage.control << " / " << midiMessage.value;
        ofDrawBitmapStringHighlight(text.str(), 0, 45);
        text.str(""); // clear
        
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void MidiApc40::exit() {
    if (input) {
        // clean up
        midiIn.closePort();
        midiIn.removeListener(this);
    }
    if (output) {
        midiOut.closePort();
    }
}

//--------------------------------------------------------------
void MidiApc40::newMidiMessage(ofxMidiMessage& msg) {

	// make a copy of the latest message
	midiMessage = msg;
    if (msg.status == MIDI_NOTE_OFF) {
        midi_in_note(msg.portNum, msg.channel, msg.pitch, 0, msg.velocity);
    }
    if (msg.status == MIDI_NOTE_ON) {
        midi_in_note(msg.portNum, msg.channel, msg.pitch, 1, msg.velocity);
    }
    if (msg.status == MIDI_CONTROL_CHANGE) {
        midi_in_ctrl(msg.portNum, msg.channel, msg.control, msg.value);
    }
    
}


//--------------------------------------------------------------
//Novation launchpad
//определить, какая кнопка нажата от 0 до 63
/*int MidiApc40::launchpad_parse_button(int pitch) {
    //TODO можно без цикла
    for (int i=0; i<8; i++) {
        if (pitch>=i*16 && pitch<i*16+8) {
            return pitch-i*16+i*8;
        }
    }
    return -1;
}*/

//--------------------------------------------------------------
//включить освещение LED, btn от 0 до 63
/*void MidiApc40::launchpad_set_led(int btn, float redf, float greenf) {
    if (output) {
        int x = btn % 8;
        int y = btn / 8;
        int note = x + y*16;
        
        int green = ofMap(greenf,0,1,0,3,true);
        int red = ofMap(redf,0,1,0,3,true);
        int vel = 12 + red + 16*green;
        
        midiOut.sendNoteOn(1, note,  vel);
        
    }
}*/

//--------------------------------------------------------------
void MidiApc40::midi_in_note(int port, int channel, int pitch, int onoff, int velocity) {
	if (PRM log_midi) {
		std::ostringstream out;
		out << "APC note";
		if (onoff) out << " ON"; 
		else out << " OFF";
		out << ", port " << port << ", ch " << channel << ", pitch " << pitch << ", vel " << velocity;
		MLOG(out.str());
	}
}

//--------------------------------------------------------------
void MidiApc40::set_int(string name, int ch, int midi_val, int max_val) {
	if (ch >= 1 && ch <= maxTones) {
		*gui.findVarInt(name + ofToString(ch)) = (max_val+1) * midi_val / 128;
	}
}

//--------------------------------------------------------------
void MidiApc40::set_stringlist(string name, int ch, int midi_val, int max_val) {
	if (ch >= 1 && ch <= maxTones) {
		*gui.findVarStringList(name + ofToString(ch)) = (max_val+1) * midi_val / 128;
	}
}

//--------------------------------------------------------------
void MidiApc40::set_float(string name, int ch, int midi_val, float max_val) {
	if (ch == -1) *gui.findVarFloat(name) = max_val * midi_val / 127;
	if (ch >= 1 && ch <= maxTones) {
		*gui.findVarFloat(name + ofToString(ch)) = max_val * midi_val / 127;
	}
}

//--------------------------------------------------------------
void MidiApc40::set_float(string name, int ch, int midi_val, float min_val, float max_val) {
	if (ch >= 1 && ch <= maxTones) {
		*gui.findVarFloat(name + ofToString(ch)) = ofMap(midi_val, 0, 127, min_val, max_val);
	}
}

//--------------------------------------------------------------
void MidiApc40::midi_in_ctrl(int port, int ch, int ctrl, int value) {
	if (PRM log_midi) {
		std::ostringstream out;
		out << "APC ctrl ";
		out << " port " << port << ", ch " << ch << ", ctrl " << ctrl << ", value " << value;
		MLOG(out.str());
	}
	int N = maxTones;	//число техно-звуков
	//Mixer - Vol
	if (ctrl == 7) {
		if (ch <= 6) set_float("w_vol", ch, value, 1);	//громкость Techno
		if (ch == 7) set_float("REP_VOL", -1, value, 2);	//громкость REP_VOL
	}
	//1 - Mode
	if (ctrl == 16) set_stringlist("w_mode", ch, value, 2);
	//2 - Delay
	if (ctrl == 17) set_stringlist("w_delay", ch, value, 6);
	//7 - Filter
	if (ctrl == 18) set_int("w_cutoff", ch, value, 1000);
	//8 - Pan
	if (ctrl == 19) set_float("w_pan", ch, value, 1);
	//3 - Pos
	if (ctrl == 20) set_float("w_pos", ch, value, 1);
	//4 - Len
	if (ctrl == 21) set_float("w_len", ch, value, 1);
	//5 - Spd
	if (ctrl == 22) set_float("w_spd", ch, value, 1);
	//6 - Grain Len
	if (ctrl == 23) set_float("w_grain_len", ch, value, 0.002, 0.1);


	//Global Vol
	if (ch == 1 && ctrl == 14) {

	}

	

}

//--------------------------------------------------------------

