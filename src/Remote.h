#pragma once

//Управление GUI по OSC
#include "ofMain.h"
#include "ofxKuTextGuiRemote.h"

bool Remote_parse_message(ofxOscMessage &m);


extern ofxKuTextGuiRemoteServer REMOTE;