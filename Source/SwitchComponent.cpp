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
    auto area = getLocalBounds().toFloat();

    area.reduce(0, 25);
    g.setColour(juce::Colour(0xffb9b9b9));
    g.fillRoundedRectangle(area, 25);

    area.reduce(25, 25);
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
