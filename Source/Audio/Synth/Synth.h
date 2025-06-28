/*
  ==============================================================================

    Synth.h
    Created: 5 May 2025 6:14:11pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../MidiInstrument.h"
#include "Voice.h"


class Synth : public MidiInstrument
{
public:
    Synth();
    ~Synth();
    
    void setSampleRate(double) override;
    
    void addToBuffer(juce::AudioBuffer<float>& buffer, const juce::MidiBuffer& midiBuffer) override;
    
private:
    static const int numVoices = 8;
    std::vector<Voice> voices;
    
    int findIndexOfFreeVoice();
    
};
