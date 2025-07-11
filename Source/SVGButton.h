/*
  ==============================================================================

    SVGButton.h
    Created: 11 Jul 2025 3:29:03pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SVGButton : public juce::Button
{
public:
    SVGButton(const juce::String& name, juce::Colour backgroundColour) : Button(name), backgroundColour(backgroundColour)
    {
    }
    ~SVGButton() {}
    
    void setIcon(std::unique_ptr<juce::Drawable> d) { icon = std::move(d); }

    void resized()
    {
        scaleFactor = juce::jmin(getTopLevelComponent()->getWidth() / 1600,
            getTopLevelComponent()->getHeight() / 720);
    }
    
    void paintButton(juce::Graphics& g, bool down, bool highlighted)
    {
        auto area = getLocalBounds().toFloat();
        //area.reduce(scaled(10), 0);
        g.setColour(juce::Colour(backgroundColour));
        g.fillRoundedRectangle(area, scaled(15));
        
        g.setColour(juce::Colours::black);
        area.reduce(scaled(25), scaled(25));
        if(icon != nullptr)
            icon->drawWithin(g, area, juce::RectanglePlacement::centred, 1.0f);
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SVGButton)
    
    std::unique_ptr<juce::Drawable> icon;
    juce::Colour backgroundColour;
    
    float scaled(float val) { return val * scaleFactor; }

    float scaleFactor = 1;
};
