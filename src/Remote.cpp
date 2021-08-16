#include "Remote.h"
#include "gui_generated.h"

ofxKuTextGuiRemoteServer REMOTE;

//--------------------------------------------------------------
bool Remote_parse_message(ofxOscMessage &m) {
	//всегда включен
	return REMOTE.processMessage(m);
}

//--------------------------------------------------------------
