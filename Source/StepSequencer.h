/*
  ==============================================================================

    StepSequencer.h
    Created: 24 Apr 2025 2:04:03pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SequencerButton.h"

class StepSequencer : public juce::Component
{
public:
    StepSequencer(int numTracks, int numSteps);
    ~StepSequencer();
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
    void nextStep();
    void reset();
    
private:
    std::vector<std::vector<std::unique_ptr<SequencerButton>>> buttons;
    int highlightIndex = 0;
    int numSteps = 0;
    int numTracks = 0;
    float timerFrequency = 6.0;
    void incrementHighlight();
    
};
