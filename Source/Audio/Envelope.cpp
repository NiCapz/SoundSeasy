/*
  ==============================================================================

    Envelope.cpp
    Created: 16 May 2025 6:59:06pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#include "Envelope.h"
#include <cMath>

Envelope::Envelope(std::atomic<float>* attackParam,
                   std::atomic<float>* decayParam,
                   std::atomic<float>* sustainParam,
                   std::atomic<float>* releaseParam) :
        attackParam(attackParam),
        decayParam(decayParam),
        sustainParam(sustainParam),
        releaseParam(releaseParam)
{
}

Envelope::Envelope(Envelope& other) :
    attackParam(other.attackParam),
    decayParam(other.decayParam),
    sustainParam(other.sustainParam),
    releaseParam(other.releaseParam)
{
}

Envelope::~Envelope()
{
}


void Envelope::setSampleRate(float val)
{
    sampleRate = val;
    
    float smoothing = pow(0.1, 1000.0 / (sampleRate * 50));
    
    attackParam.setSmoothing(smoothing);
    decayParam.setSmoothing(smoothing);
    sustainParam.setSmoothing(smoothing);
    releaseParam.setSmoothing(smoothing);
}

float Envelope::getNextValue(bool gate)
{
    if(!(this->gate) && gate)
    {
        state = ATTACK;
    }
    else if(this->gate && !gate)
    {
        state = RELEASE;
    }
    
    this->gate = gate;
    
    
    float attackCoeff =  1 - pow(0.01, 1.0 / (sampleRate * attackParam.getValue()));
    float decayCoeff =   1 - pow(0.01, 1.0 / (sampleRate * decayParam.getValue()));
    float releaseCoeff = 1 - pow(0.01, 1.0 / (sampleRate * releaseParam.getValue()));
    
    switch(state)
    {
        case ATTACK:
            value = attackCoeff + value * (1 - attackCoeff);
            if(value > 0.99)
                state = DECAY;
            break;
            
        case DECAY:
            value = sustainParam.getValue() * decayCoeff + value * (1 - decayCoeff);
            break;
            
        case RELEASE:
            value = value * (1 - releaseCoeff);
            break;
    }
    
    attackParam.update();
    decayParam.update();
    sustainParam.update();
    releaseParam.update();
    
    return value;
}

void Envelope::reset()
{
    state = ATTACK;
}

void Envelope::updateTarget()
{
    attackParam.updateTarget();
    decayParam.updateTarget();
    sustainParam.updateTarget();
    releaseParam.updateTarget();
}
