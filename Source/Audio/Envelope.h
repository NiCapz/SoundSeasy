/*
  ==============================================================================

    Envelope.h
    Created: 16 May 2025 6:59:00pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <atomic>
#include "SmoothedParameter.h"

class Envelope
{
public:
    Envelope(std::atomic<float>* attackParam,
             std::atomic<float>* decayParam,
             std::atomic<float>* sustainParam,
             std::atomic<float>* releaseParam);
    Envelope(Envelope& other);
    ~Envelope();
    
    void setSampleRate(float);
    
    float getNextValue(bool gate);
    void reset();
    
    void store() { storedValue = value; }
    void recall() { value = storedValue; }
    
    void updateTarget();
    
private:
    
    enum State
    {
        ATTACK,
        DECAY,
        RELEASE
    };
    
    float sampleRate = 44100;
    
    SmoothedParameter<float> attackParam;
    SmoothedParameter<float> decayParam;
    SmoothedParameter<float> sustainParam;
    SmoothedParameter<float> releaseParam;
    
    bool gate = false;
    float value = 0;
        
    float storedValue = 0;
    
    State state = RELEASE;
};
