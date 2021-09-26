#include "MidiApc40.h"
#include "ofxKuMessageLog.h"
#include "gui_generated.h"
#include "Machines.h"
#include "Pedal.h"

extern ofxKuTextGui gui;

MidiApc40 APC40;


//--------------------------------------------------------------
void MidiApc40::setup() {
	PRM log_midi = 0;	//отключаем печать всех сообщений MIDI

	inputAPC = true; 
	inputLPD = true;
	//outputAPC = true;
    
	auto list_in = midiInAPC.getInPortList();
	if (inputAPC) {
		bool result = true;

		//APC40
		int i = find_index(PRM APC_midi_in, list_in);
		if (i < 0) {
			result = false;
			MLOG("No APC40 MIDI IN in device " + PRM APC_midi_in, ofColor(255, 0, 0));
		}
		if (result) result = midiInAPC.openPort(i);
		if (!result) {
			MLOG("Can't open APC40 MIDI IN device " + PRM APC_midi_in, ofColor(255, 0, 0));
		}
		else {
			// add this class a listener
			apc_port = i;
			midiInAPC.addListener(this);
			MLOG("Started APC40 MIDI IN device " + list_in[i] + ", port " + ofToString(apc_port), ofColor(0, 200, 0));
		}
		inputAPC = result;
	}

	//LPD8
	if (inputLPD) {
		int i = find_index(PRM LPD_midi_in, list_in);
		bool result = true;
		if (i < 0) {
			result = false;
			MLOG("No LPD8 MIDI IN in device " + PRM LPD_midi_in, ofColor(255, 0, 0));
		}
		if (result) result = midiInLPD.openPort(i);
		if (!result) {
			MLOG("Can't open LPD40 MIDI IN device " + PRM LPD_midi_in, ofColor(255, 0, 0));
		}
		else {
			lpd_port = i;
			// add this class a listener
			midiInLPD.addListener(this);
			MLOG("Started LPD8 MIDI IN device " + list_in[i] + ", port " + ofToString(lpd_port), ofColor(0, 200, 0));
		}
		inputLPD = result;

        // print received messages to the console
        //midiIn.setVerbose(true);
	
		/*
		//Useful functions:
		//midiIn.openPort("IAC Pure Data In");	// by name
		//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port

		// don't ignore sysex, timing, & active sense messages,
		// these are ignored by default
		//midiIn.ignoreTypes(false, false, false);
		*/
	}
    
	if (outputAPC) {
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

			//set_apc40_mode();
		}
		outputAPC = result;
	}
	PRM APC_status_ = inputAPC /* && output)*/ ? "Connected" : "NOT Connected !!!";
	PRM LPD_status_ = inputLPD /* && output)*/ ? "Connected" : "NOT Connected !!!";

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
		MLOG("Connected MIDI IN devices (expected APC40,LPD8)");
		auto list = midiInAPC.getInPortList();
		for (int i = 0; i < list.size(); i++) {
			MLOG("    " + ofToString(i) + ": " + list[i]);
		}

		MLOG("Connected MIDI OUT devices (expected APC40)");
		auto list1 = midiOut.getOutPortList();
		for (int i = 0; i < list1.size(); i++) {
			MLOG("    " + ofToString(i) + ": " + list1[i]);
		}
	}
	//if (PRM APC_TestSend) {
	//	test_send();
	//}
}

//--------------------------------------------------------------
void MidiApc40::draw(float x, float y) {
/*    if (input) {
        
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
    }*/
}

//--------------------------------------------------------------
void MidiApc40::exit() {
	// clean up
	if (inputAPC) {
		midiInAPC.closePort();
		midiInAPC.removeListener(this);
	}
	if (inputLPD) {
		midiInLPD.closePort();
		midiInLPD.removeListener(this);
	}
    if (outputAPC) {
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
void MidiApc40::set_int(string name, int ch, int midi_val, int max_val) {
	if (ch >= 1 && ch <= maxTones) {
		*gui.findVarInt(name + ofToString(ch)) = (max_val+1) * midi_val / 128;
	}
}

//--------------------------------------------------------------
void MidiApc40::set_stringlist(const string &name, int ch, int midi_val, int max_val) {
	if (ch >= 1 && ch <= maxTones) {
		*gui.findVarStringList(name + ofToString(ch)) = (max_val+1) * midi_val / 128;
	}
}

//--------------------------------------------------------------
void MidiApc40::set_float(const string &name, int ch, float float_val) {
	if (ch == -1) *gui.findVarFloat(name) = float_val;
	if (ch >= 1 && ch <= maxTones) {
		*gui.findVarFloat(name + ofToString(ch)) = float_val;
	}

}

//--------------------------------------------------------------
void MidiApc40::set_float(const string &name, int ch, int midi_val, float max_val) {
	set_float(name, ch, max_val * midi_val / 127.0f);
}

//--------------------------------------------------------------
void MidiApc40::set_float(const string &name, int ch, int midi_val, float min_val, float max_val) {
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
	int NPult = N - 1;	//число звуков, которыми управляем с пульта
	
	//LPD
	if (port == lpd_port) {
		//Delay FX
		if (ctrl <= NPult) {
			float v = value / 127.0;
			float delay1 = ofMap(v, 0.45, 0, 0, 1, true);	//влево - delay1
			float delay2 = ofMap(v, 0.55, 1, 0, 1, true);	//вправо - delay2
			set_float("w_fxA", ctrl, delay1);
			set_float("w_fxB", ctrl, delay2);
		}
	}

	//APC
	if (port == apc_port) {
		//Mixer - Vol
		if (ctrl == 7) {
			if (ch <= N) set_float("w_vol", ch, value, 1);	//громкость Techno
			if (ch == 8) set_float("REP_VOL", -1, value, 1);	//громкость REP_VOL
		}

		//устанавливаем, что эта дорожка редактируется - так как AKAI высыдает ее и остальные при переключении
		if (ctrl >= 16 && ctrl <= 23 && ch <= NPult) {
			PRM EDIT_ = ch;
		}

		//1 - Mode
		if (ctrl == 16 && ch <= NPult) set_stringlist("w_mode", ch, value, 2);
		//2 - Delay
		if (ctrl == 17 && ch <= NPult) set_stringlist("w_delay", ch, value, 6);
		//7 - Filter
		if (ctrl == 18 && ch <= NPult) set_float("w_cutoff", ch, value, 1);
		//8 - Pan
		if (ctrl == 19 && ch <= NPult) set_float("w_pan", ch, value, 1);
		//3 - Pos
		if (ctrl == 20 && ch <= NPult) set_float("w_pos", ch, value, 1);
		//4 - Len
		if (ctrl == 21 && ch <= NPult) set_float("w_len", ch, value, 1);
		//5 - Spd
		if (ctrl == 22 && ch <= NPult) set_float("w_spd", ch, value, 1);
		//6 - Grain Len
		if (ctrl == 23 && ch <= NPult) set_float("w_grain_len", ch, value, 0.002, 0.1);

		//Filtr type
		if (ch == 1 && ctrl >= 48 && ctrl < 48 + NPult) {
			int filters = 2; //Lowpass, Band, Hipass - в пульте
			int v = 1 + (filters + 1) * value / 128; //добавляем 1, так как начинается с bypass
			int id = ctrl - 48;
			*gui.findVarStringList("w_flt" + ofToString(id + 1)) = v;
		}

		//Pedal
		if (ctrl == 64 || ctrl == 67) {
			set_pedal_value(value == 0);
		}

		//Global Vol
		//if (ch == 1 && ctrl == 14) {
		//}
	}

	

}

//--------------------------------------------------------------
void MidiApc40::midi_in_note(int port, int ch, int pitch, int onoff, int velocity) {
	if (PRM log_midi) {
		std::ostringstream out;
		out << "APC note";
		if (onoff) out << " ON";
		else out << " OFF";
		out << ", port " << port << ", ch " << ch << ", pitch " << pitch << ", vel " << velocity;
		MLOG(out.str());
	}

	//APC
	if (port == apc_port) {
		if (ch >= 1 && ch <= maxTones) {
			//Rec (Record Arm)
			if (pitch == 48) {
				*gui.findVarStringList("REC" + ofToString(ch)) = onoff;
			}
			//if (ch == 8) {
			//	*gui.findVarStringList("REP_REC") = onoff;
			//}

			//Louder ("Solo/Que") - дополнительное увеличение громкости
			if (pitch == 49 && ch <= maxTones - 1) {
				*gui.findVarStringList("w_louder" + ofToString(ch)) = onoff;
			}

			//Activator - Morph ON/OFF
			if (pitch == 50 && ch <= maxTones - 1) {
				*gui.findVarInt("w_percent" + ofToString(ch)) = 100 * onoff;
			}
		}
	}
}

//--------------------------------------------------------------
//отправка данных
/*void MidiApc40::set_apc40_mode() {
	MLOG("Putting APC40 to mode...");
	//0x40 Generic Mode
	//0x41 Ableton Live Mode
	//0x42 Alternate Ableton Live Mode

	midiOut.sendMidiByte(0xF0);
	midiOut.sendMidiByte(0x47);
	midiOut.sendMidiByte(0x00);
	midiOut.sendMidiByte(0x73);
	midiOut.sendMidiByte(0x60);
	midiOut.sendMidiByte(0x00);
	midiOut.sendMidiByte(0x04);

	midiOut.sendMidiByte(0x42);

	midiOut.sendMidiByte(0x00);
	midiOut.sendMidiByte(0x00);
	midiOut.sendMidiByte(0x00);

	midiOut.sendMidiByte(0xF7);
}*/

//--------------------------------------------------------------
/*void MidiApc40::test_send() {
	if (!output) return;
	//RECORD ARM: note 0x30 (C_3), channel 0-7 = Track 1-8, 0=off, 1-127=on
	MLOG("Sending to APC"); //"RECORD ARM change...");

	midiOut.sendNoteOn(0, 48, 127);
	//for (int i = 0; i < 127; i++) {
	//	midiOut.sendNoteOn(0, i, 127);
	//}
		
}*/

//--------------------------------------------------------------

