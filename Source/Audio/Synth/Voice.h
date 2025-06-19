/*
  ==============================================================================

    Voice.h
    Created: 5 May 2025 6:13:37pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Envelope.h"
#include "../SmoothedParameter.h"

typedef juce::dsp::IIR::Filter<float> IIRFilter;
typedef juce::dsp::IIR::Coefficients<float> IIRCoefficients;

typedef juce::dsp::StateVariableFilter::Filter<float> SVFilter;

class Voice
{
public:
    Voice();
    Voice(Voice&& other);
    ~Voice();
    Voice& operator= (Voice& other);
    
    float getNextValue();
    
    void processBlock(float*, int, int);
    
    int getNoteNumber();
    bool getGate();
    float getAmplitude();
    long getNoteLength();
    
    void setSampleRate(float);
    void setGate(bool);
    void setNoteNumber(int);
    void resetEnvelope();
    
private:
    void updateParameterTargets();
    
    float sampleRate = 44100;
    
    bool gateValue = false;
    bool free = true;
    
    float envelopeValue = 0;
    
    int noteNumber = 64;
    float pitch = 440;
    long noteLengthCounter = 0;
    
    Envelope ampEnvelope;
    Envelope filEnvelope;
    
    std::unique_ptr<SVFilter> svFilter;
    
    SmoothedParameter<float> filterCutoff;
    SmoothedParameter<float> filterRes;
    SmoothedParameter<float> filEnvDepth;
    
    SmoothedParameter<float> unison;
    SmoothedParameter<float> detune;
    
    static constexpr int maxOscillators = 8;
    std::array<float, maxOscillators> sawOscValues{};
    
    std::vector<std::unique_ptr<IIRFilter>> antiAliasingFilters;
    static constexpr int oversampling = 4;
    const float antiAliasingCutoff = 15000;
    
    static constexpr int maxBufferSize = (1<<7);
    
};
