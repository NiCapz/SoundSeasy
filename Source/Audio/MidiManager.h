/*
  ==============================================================================

    MidiManager.h
    Created: 19 Jun 2025 7:58:49pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MidiManager
{
public:
    MidiManager();
    ~MidiManager();
    
    void reset(double);
    void setStartTimeS(double val) { startTime = val; }
    
    void addMessageToQueue(const juce::MidiMessage&);
    void removeNextBlockOfMessages(juce::MidiBuffer&, int);
    
private:
    
    std::mutex messageListMutex{};
    std::list<juce::MidiMessage> messages{};
    
    double startTime = 0.0;
    double timeElapsed = 0.0;
    
    double sampleRate = 44100;
};
