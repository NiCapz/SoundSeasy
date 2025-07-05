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

float SwitchComponent::scaled(float val) {
    return val * scaleFactor;
}

void SwitchComponent::paint (juce::Graphics& g)
{
    auto area = getLocalBounds().toFloat().reduced(scaled(30), 0);

    g.setColour(juce::Colour(0xffb9b9b9));
    g.fillRoundedRectangle(area, scaled(15));

    area.reduce(scaled(20), scaled(20));
    if (pianoIcon != nullptr) 
    {
        pianoIcon->drawWithin(g, area, juce::RectanglePlacement::centred, 1);
    }
}

void SwitchComponent::resized()
{
    scaleFactor = juce::jmin(getTopLevelComponent()->getWidth() / 1600,
        getTopLevelComponent()->getHeight() / 720);
}
