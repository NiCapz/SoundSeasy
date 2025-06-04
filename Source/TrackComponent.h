/*
  ==============================================================================

    TackComponent.h
    Created: 23 May 2025 12:55:24pm
    Author:  Niko

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "StepComponent.h"

class TrackComponent : public juce::Component
{
public:
    TrackComponent() {
        for (int i = 0; i < 8; i++) {
            auto* step = new StepComponent();
            steps.add(step);
            addAndMakeVisible(step);
        }
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        int stepWidth = bounds.getWidth() / 8;

        for (int i = 0; i < steps.size(); i++) 
        {
            steps[i]->setBounds(i * stepWidth + 10, 10, stepWidth - 20, bounds.getHeight() - 20);
        }
    }
private:
    juce::OwnedArray<StepComponent> steps;
};