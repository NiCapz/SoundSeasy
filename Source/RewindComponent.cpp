/*
  ==============================================================================

    RewindComponent.cpp
    Created: 18 Jun 2025 2:31:16pm
    Author:  Niko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RewindComponent.h"

//==============================================================================
RewindComponent::RewindComponent(juce::String& name) : juce::Button(name)
{
    rewindIcon = juce::Drawable::createFromImageData(BinaryData::rewind_svg, BinaryData::rewind_svgSize);
}

float RewindComponent::scaled(float val) {
    return val * scaleFactor;
}

RewindComponent::~RewindComponent()
{
}

void RewindComponent::paintButton (juce::Graphics& g, bool isHighlighted, bool isDown)
{
    auto area = getLocalBounds().toFloat().reduced(scaled(10), 0);

    g.setColour (juce::Colour (0xffb9b9b9));
    g.fillRoundedRectangle(area, scaled(15));


    area.reduce(scaled(25), scaled(25));
    if (rewindIcon != nullptr) 
    {
        rewindIcon->drawWithin(g, area, juce::RectanglePlacement::centred, 1);
    }
    
    
}

void RewindComponent::resized()
{
    scaleFactor = juce::jmin(getTopLevelComponent()->getWidth() / 1600,
        getTopLevelComponent()->getHeight() / 720);
}
