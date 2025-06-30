/*
  ==============================================================================

    BodyComponent.h
    Created: 4 Jun 2025 11:28:45am
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TrackComponent.h"

//==============================================================================
/*
*/
class BodyComponent  : public juce::Component
{
public:
    BodyComponent();
    ~BodyComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void updateStepIndexes(int index);
    juce::OwnedArray<TrackComponent> tracks;

private:
    juce::String trackNames[5] = { "Crash", "Hi-Hat 1", "Hi-Hat2", "Snare", "Kick" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BodyComponent)
};
