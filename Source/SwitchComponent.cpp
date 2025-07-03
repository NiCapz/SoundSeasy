/*
  ==============================================================================

    SwitchComponent.cpp
    Created: 4 Jun 2025 11:29:24am
    Author:  Niko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SwitchComponent.h"

//==============================================================================
SwitchComponent::SwitchComponent()
{
    pianoIcon = juce::Drawable::createFromImageData(BinaryData::piano_svg, BinaryData::piano_svgSize);
}

SwitchComponent::~SwitchComponent()
{
}

void SwitchComponent::paint (juce::Graphics& g)
{
    auto area = getLocalBounds().toFloat().reduced(30, 0);

    g.setColour(juce::Colour(0xffb9b9b9));
    g.fillRoundedRectangle(area, 15);

    area.reduce(20, 20);
    if (pianoIcon != nullptr) 
    {
        pianoIcon->drawWithin(g, area, juce::RectanglePlacement::centred, 1);
    }
}

void SwitchComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
