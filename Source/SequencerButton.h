/*
  ==============================================================================

    SequencerButton.h
    Created: 24 Apr 2025 2:04:18pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SequencerButton : public juce::ToggleButton
{
public:
    SequencerButton(const juce::String& buttonName) : ToggleButton(buttonName)
    {
    }
    
    void setHightlighted(bool val)
    {
        isHighlighted = val;
        repaint();
    }
    
protected:
    void paintButton(juce::Graphics& g,
                     bool shouldDrawButtonAsHighlighted,
                     bool shouldDrawButtonAsDown) override
    {
        const auto localBounds = getLocalBounds();
        const float width = localBounds.getWidth();
        const float height = localBounds.getHeight();
        const float lineWidth = 3.0;
        float d = ((width < height) ? width : height) - lineWidth;
        
        if(getToggleState())
        {
            g.setColour(juce::Colour::fromHSV(0.0, 0.0, 1.0, 0.7));
            g.fillEllipse(lineWidth / 2,
                          lineWidth / 2,
                          d,
                          d);
        }
        
        if(isHighlighted)
        {
            g.setColour(juce::Colour::fromHSV(0.0, 0.0, 1.0, 0.3));
            g.fillEllipse(lineWidth / 2,
                          lineWidth / 2,
                          d,
                          d);
        }
        
        g.setColour(juce::Colour::fromHSV(0.0, 0.0, 0.0, 1.0));
        g.drawEllipse(lineWidth / 2,
                      lineWidth / 2,
                      d,
                      d,
                      3.0);
    }

private:
    bool isHighlighted = false;
};
