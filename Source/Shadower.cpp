/*
  ==============================================================================

    Shadower.cpp
    Created: 5 Jul 2025 6:47:55pm
    Author:  Niko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Shadower.h"

//==============================================================================
Shadower::Shadower()
{
}

Shadower::~Shadower()
{
}

void Shadower::drawShadowImage(juce::Graphics& g, juce::Rectangle<int> bounds, juce::Path path, juce::Image shadowImage) {

    static bool shadowsRendered = false;

    if ( !shadowsRendered ) 
    {
        shadowImage = juce::Image(juce::Image::PixelFormat::ARGB,
            bounds.getWidth(),
            bounds.getHeight(),
            true);
        juce::Graphics shadowGraphics{ shadowImage };
        juce::DropShadow shadow(juce::Colours::black.withAlpha(.25f), 100, { 0, 10 });
        shadow.drawForPath(shadowGraphics, path);
        shadowsRendered = true;
    }
        g.drawImage(shadowImage, bounds.toFloat());
}

void Shadower::paint (juce::Graphics& g)
{
}

void Shadower::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
