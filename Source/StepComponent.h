/*
  ==============================================================================

    StepComponent.h
    Created: 23 May 2025 12:46:42pm
    Author:  Niko

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class StepComponent : public juce::Button
{
public:
    StepComponent(juce::String& name) : Button(name)
    {
    }

    void paintButton(juce::Graphics& g, bool isHighlighted, bool isDown) override
    {
        auto bounds = getLocalBounds().toFloat();

        bounds.setRight(bounds.getHeight());

        if (highlighted) 
        {
            g.setColour(juce::Colours::white);
            g.drawEllipse(bounds.reduced(5.0f), 5.0f);
        }
        else
        {
            g.setColour(juce::Colours::darkgrey);
            g.drawEllipse(bounds.reduced(5.0f), 3.0f);
        }

        if (isSample) {
            g.setColour(juce::Colours::beige);
            g.fillEllipse(bounds.reduced(7.0f));
        }


	}
   
    void clicked() override
    {
        isSample = !isSample;
    }

    void setHighlighted(bool highlighted) {
        this->highlighted = highlighted;
    }

private:
    bool highlighted = false;
    bool isSample = false;
};