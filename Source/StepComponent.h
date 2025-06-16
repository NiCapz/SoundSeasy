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

        g.setColour(juce::Colours::darkgreen);
        //g.drawRect(bounds, 1.0f);
        
        bounds.setRight(bounds.getHeight());

        g.setColour(juce::Colours::lightgrey);
        g.drawEllipse(bounds.reduced(5.0f), 5.0f);

    }

private:
};