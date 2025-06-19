/*
  ==============================================================================

    SamplerTrack.h
    Created: 12 May 2025 8:17:21pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <vector>
#include "../Envelope.h"

class SamplerTrack
{
public:
    SamplerTrack();
    ~SamplerTrack();
    
    void setSampleRate(float);
    void setGate(bool);
    void setNoteNumber(int);
    void setSample(const float* sampleData, int numSamples, float sampleRate, float referencePitch);
    
    float getNextValue();
    void processBlock(float*, int, int);
    
    int getNoteNumber();
    bool getGate();
    float getAmplitude();
    long getNoteLength();
    
    
private:
    void calculateIncrement();
    
    float projectSampleRate = 44100;
    float sampleSampleRate = 44100;
    
    float referencePitch = 440;
    float pitch = 440;
    int noteNumber = 64;
    long noteLengthCounter = 10000;
    
    bool gateValue = false;
    float envelopeValue = 0;
    
    const float* sampleData;
    const int padding = 2;
    int sampleSize = 0;
    float playIndex = 0;
    float playIncrement = 1;
    
    std::atomic<float> envAttack = 0.0;
    std::atomic<float> envDecay = 10.0;
    std::atomic<float> envSustain = 1.0;
    std::atomic<float> envRelease = 0.3;
    
    Envelope ampEnvelope;
};
