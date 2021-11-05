#pragma once

#include "ofMain.h"
#include "Common.h"

//LFO для громкости и панорамы

extern int SR;  //sample rate

//LFO на уровне генерации новых звуков

struct LfoBeat {
    //stringlist d_voltype=0 [const,up,down,rand,sin,-sin,cos,-cos]
    //float d_volloop=1 1:64 1,10
    //float d_vol=0.5 0:1 100,10
    //float d_volrnd=0.5 0:1 100,10
    //float d_volmov=0.5 0:1 100,10
    static const int TypeConst = 0;
    static const int TypeUp    = 1;
    static const int TypeDown  = 2;
    static const int TypeRand  = 3;
    static const int TypeSin   = 4;
    static const int TypeSinM   = 5;
    static const int TypeCos   = 6;
    static const int TypeCosM   = 7;

    LfoBeat();
    void setup(int type, int steps, float value0, float rnd, float mov);
    void setRange(float range0, float range1);
    float nextValue();
    
    int type;
    int steps;
    float value0;
    float rnd;
    float mov;
    
    float range0, range1;
    
    //value = value0 + ofRandom(-1,1)*rnd + mov*LFO

    float pos;          //[0,1]
    float pos_step;
    float pos_correction;
};




