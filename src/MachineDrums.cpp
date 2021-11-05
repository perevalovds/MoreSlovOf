#include "MachineDrums.h"
#include "gui_generated.h"
#include "Common.h"
#include "Morph.h"

//барабаны
float *DRUM_POS[DrumKits][DrumBeats];
//int DRUM_POS_SAMPLES[DrumKits][DrumBeats];

bool drums_inited_ = false;

//--------------------------------------------------
void drums_setup() {		//линк с GUI
	DRUM_POS[0][0] = &PRM d1pos1;
	DRUM_POS[0][1] = &PRM d1pos2;
	DRUM_POS[0][2] = &PRM d1pos3;
	DRUM_POS[0][3] = &PRM d1pos4;
	DRUM_POS[0][4] = &PRM d1pos5;
	DRUM_POS[0][5] = &PRM d1pos6;
	DRUM_POS[0][6] = &PRM d1pos7;
	DRUM_POS[0][7] = &PRM d1pos8;
	DRUM_POS[0][8] = &PRM d1pos9;
	DRUM_POS[0][9] = &PRM d1pos10;
	DRUM_POS[0][10] = &PRM d1pos11;
	DRUM_POS[0][11] = &PRM d1pos12;
	DRUM_POS[0][12] = &PRM d1pos13;
	DRUM_POS[0][13] = &PRM d1pos14;
	DRUM_POS[0][14] = &PRM d1pos15;
	DRUM_POS[0][15] = &PRM d1pos16;

	DRUM_POS[1][0] = &PRM d2pos1;
	DRUM_POS[1][1] = &PRM d2pos2;
	DRUM_POS[1][2] = &PRM d2pos3;
	DRUM_POS[1][3] = &PRM d2pos4;
	DRUM_POS[1][4] = &PRM d2pos5;
	DRUM_POS[1][5] = &PRM d2pos6;
	DRUM_POS[1][6] = &PRM d2pos7;
	DRUM_POS[1][7] = &PRM d2pos8;
	DRUM_POS[1][8] = &PRM d2pos9;
	DRUM_POS[1][9] = &PRM d2pos10;
	DRUM_POS[1][10] = &PRM d2pos11;
	DRUM_POS[1][11] = &PRM d2pos12;
	DRUM_POS[1][12] = &PRM d2pos13;
	DRUM_POS[1][13] = &PRM d2pos14;
	DRUM_POS[1][14] = &PRM d2pos15;
	DRUM_POS[1][15] = &PRM d2pos16;

	//drums_update(0);	//ставим DRUM_POS_SAMPLES

	drums_inited_ = true;
}

//--------------------------------------------------
void drums_set_equal(int kit) {
	int n = DrumBeats;
	float clamp0 = 0.1;
	float clamp1 = 0.9;
	for (int i = 0; i < n; i++) {
		*DRUM_POS[kit][i] = ofMap(i, 0, n, clamp0, clamp1);
	}
}

//--------------------------------------------------
void drums_set_random(int kit) {
	int n = DrumBeats;
	float clamp0 = 0.1;
	float clamp1 = 0.9;
	for (int i = 0; i < n; i++) {
		*DRUM_POS[kit][i] = ofMap(ofRandom(0, n-1), 0, n, clamp0, clamp1);
	}
}

//--------------------------------------------------
void drums_update(float dt) {		//обработка кнопок
	//Проверка, что барабаны инициализированы
	x_assert(drums_inited_, "drums_setup() was not called, please call it");
	
	//Кнопки
	if (PRM d1_Equal) drums_set_equal(0);
	if (PRM d1_Random) drums_set_random(0);
	if (PRM d2_Equal) drums_set_equal(1);
	if (PRM d2_Random) drums_set_random(1);

	//Значения в сэмплах
	//for (int k = 0; k < DrumKits; k++) {

	//}

}

//--------------------------------------------------
