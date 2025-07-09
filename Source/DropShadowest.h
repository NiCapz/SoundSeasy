/*
  ==============================================================================

    DropShadowest.h
    Created: 9 Jul 2025 2:44:49pm
    Author:  Niko

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DropShadowest
{
public:
    DropShadowest(juce::DropShadow& dropShadow) : shadow(dropShadow)
    {
      
    }
    ~DropShadowest() {}

    void renderPath(juce::Path path, juce::Rectangle<float> bounds)
    {
        cachedShadow = juce::Image(juce::Image::PixelFormat::ARGB,
            bounds.getWidth(),
            bounds.getHeight(),
            true);
        shadow.drawForPath(graphics, path);
    }
    void draw(juce::Graphics& g, juce::Rectangle<float> bounds)
    {
        if (cachedShadow.isValid())
            g.drawImage(cachedShadow, bounds.toFloat());
    }

private:
    juce::DropShadow shadow;
    juce::Image cachedShadow{ juce::Image::PixelFormat::ARGB, 10, 10, true };
    juce::Graphics graphics{ cachedShadow };
};