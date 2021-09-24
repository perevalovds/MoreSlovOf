#pragma once

#include "ofMain.h"
#include "LfoBeat.h"
#include "ofxFft.h"
#include "ofxSoundUtils.h"

//Барабаны

extern int SR;  //sample rate

const int DrumKits = 2;	//число драмок
const int DrumBeats = 16;	//число битов барабанов
extern float *DRUM_POS[DrumKits][DrumBeats];

void drums_setup();					//линк с GUI
void drums_update(float dt);		//считать положения барабанов из GUI, и обработка кнопок





