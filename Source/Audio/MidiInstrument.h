/*
  ==============================================================================

    MidiInstrument.h
    Created: 19 Jun 2025 9:21:15pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MidiInstrument
{
public:
    virtual void setSampleRate(double val) { sampleRate = val; }
    void setGainDB(float val) { outputGain = pow(10, val / 20.0); }
    void setMidiChannel(int channel) { midiChannel = std::clamp(channel, 1, 128); }
    
    virtual void addToBuffer(juce::AudioBuffer<float>& buffer, const juce::MidiBuffer& midiBuffer) {}
    
protected:
    double sampleRate = 44100;
    float outputGain = 1.0;
    int midiChannel = 1;
};
