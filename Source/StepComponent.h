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

        g.setColour(juce::Colour(0xff414141));
        g.fillEllipse(bounds);

        if (isActive) 
        {
            g.setColour(juce::Colour (0xffb9b9b9));
            g.fillEllipse(bounds.reduced(7));
        }
        if (highlighted)
        {
            g.setColour(juce::Colour (0xff585858));
            g.drawEllipse(bounds.reduced(3), 3);
        }


	}
   
    void clicked() override
    {
        isActive = !isActive;
    }

    void setHighlighted(bool highlighted) {
        this->highlighted = highlighted;
    }

    bool checkActive() {
        return isActive;
    }

private:
    bool highlighted = false;
    bool isActive = false;
};