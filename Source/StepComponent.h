/*
  ==============================================================================

    StepComponent.h
    Created: 23 May 2025 12:46:42pm
    Author:  Niko

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class StepComponent : public juce::Component
{
public:
    StepComponent() {}

    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();
        g.setColour(isActive ? juce::Colours::green : juce::Colours::darkgrey);
        g.fillEllipse(bounds);
        g.setColour(juce::Colours::lightgrey);
        g.drawEllipse(bounds, 5.0f);
    }

    void setActive(bool shouldBeActive) {
        isActive = shouldBeActive;
        repaint();
    }


private:
    bool isActive = false;
};