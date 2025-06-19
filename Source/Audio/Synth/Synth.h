/*
  ==============================================================================

    Synth.h
    Created: 5 May 2025 6:14:11pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Voice.h"

class Synth
{
public:
    Synth(juce::AudioProcessorValueTreeState&);
    ~Synth();
    
    void setSampleRate(float);
    
    void addToBuffer(juce::AudioBuffer<float>& buffer, const juce::MidiBuffer& midiBuffer);
    
private:
    static const int numVoices = 8;
    std::vector<Voice> voices;
    
    int findIndexOfFreeVoice();
    
};
