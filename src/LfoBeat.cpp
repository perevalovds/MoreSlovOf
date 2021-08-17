#include "LfoBeat.h"


//--------------------------------------------------
LfoBeat::LfoBeat() {
    setup(0,4,0.5,0,0);
    setRange(0,1);
}

//--------------------------------------------------
void LfoBeat::setup(int type0, int steps0, float value00, float rnd0, float mov0) {
    type = type0;
    steps = max(steps0,1);
    value0 = value00;
    rnd = rnd0;
    mov = mov0;
    
    pos = 0;
    pos_step = 1.0 / max(steps,1);
    pos_correction = max(steps,1) / max(steps-1,1);
}

//--------------------------------------------------
void LfoBeat::setRange(float range00, float range10) {
    range0 = range00;
    range1 = range10;
}

//--------------------------------------------------
float LfoBeat::nextValue() {
    float lfo = 0;
    if (type == TypeConst)  lfo = 0;
    if (type == TypeUp)     lfo = ofLerp(-1,1,pos*pos_correction);
    if (type == TypeDown)   lfo = ofLerp(1,-1,pos*pos_correction);
    if (type == TypeRand)   lfo = ofRandom(-1,1);
    if (type == TypeSin)    lfo = sin(TWO_PI*pos);
    if (type == TypeSinM)   lfo = -sin(TWO_PI*pos);
    if (type == TypeCos)    lfo = cos(TWO_PI*pos);
    if (type == TypeCosM)   lfo = -cos(TWO_PI*pos);
    
    float v = value0 + ofRandom(-rnd,rnd) + mov*lfo;
    
    pos += pos_step;
    pos = fmodf(pos,1);
    return ofClamp(v,range0,range1);
}

//--------------------------------------------------
