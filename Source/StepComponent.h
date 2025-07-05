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
            g.fillEllipse(bounds.reduced(scaled(7)));
        }
        if (highlighted)
        {
            g.setColour(juce::Colour (0xffD0D0D0));
            g.drawEllipse(bounds.reduced(scaled(3)), scaled(3));
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

    float scaled(float val) 
    {
        return val * scaleFactor;
    }

    void resized() override 
    {
        scaleFactor = juce::jmin(getTopLevelComponent()->getWidth() / 1600,
            getTopLevelComponent()->getHeight() / 720);
    }

private:

    bool highlighted = false;
    bool isActive = false;
    float scaleFactor;
};