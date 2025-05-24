/*
  ==============================================================================

    PlayButton.h
    Created: 24 Apr 2025 11:14:52pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PlayButton : public juce::ToggleButton
{
public:
    PlayButton(const juce::String& buttonName) : ToggleButton(buttonName)
    {
        playIcon.addTriangle(0.0, 0.0,
                             8.0, 5.0,
                             0.0, 10.0);
        
        pauseIcon.addRectangle(0.0, 0.0, 4.0, 10.0);
        pauseIcon.addRectangle(6.0, 0.0, 4.0, 10.0);
    }
    
    class PlayButtonListener : public juce::Button::Listener
    {
    public:
        PlayButtonListener(std::function<void(bool)> callback)
        {
            this->callback = callback;
        }
        
        void buttonClicked(Button* b) override
        {
            callback(b->getToggleState());
        }
        
    private:
        std::function<void(bool)> callback;
    };

    
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
            g.setColour(juce::Colour::fromHSV(0.0, 0.0, 1.0, 0.3));
            g.fillEllipse(lineWidth / 2,
                          lineWidth / 2,
                          d,
                          d);
            
            g.setColour(juce::Colour::fromHSV(0.0, 0.0, 0.0, 1.0));
            g.fillPath(pauseIcon, juce::AffineTransform::scale(2.0, 2.0).translated(10.0, 10.0));
        }
        else
        {
            g.setColour(juce::Colour::fromHSV(0.0, 0.0, 0.0, 1.0));
            g.fillPath(playIcon, juce::AffineTransform::scale(2.0, 2.0).translated(14.0, 10.0));
        }
        
        g.setColour(juce::Colour::fromHSV(0.0, 0.0, 0.0, 1.0));
        g.drawEllipse(lineWidth / 2,
                      lineWidth / 2,
                      d,
                      d,
                      3.0);

        
    }
    
private:
    juce::Path playIcon{};
    juce::Path pauseIcon{};
};
