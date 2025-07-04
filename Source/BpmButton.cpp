/*
  ==============================================================================

    BpmButton.cpp
    Created: 18 Jun 2025 3:46:33pm
    Author:  Niko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BpmButton.h"

//==============================================================================
BpmButton::BpmButton(juce::String& name, bool isPlus) : Button(name), isPlus(isPlus)
{
    plusIcon = juce::Drawable::createFromImageData(BinaryData::plus_svg, BinaryData::plus_svgSize);
    minusIcon = juce::Drawable::createFromImageData(BinaryData::minus_svg, BinaryData::minus_svgSize);

   
}

BpmButton::~BpmButton()
{
}

float BpmButton::scaled(float val) {
    return val * scaleFactor;
}

void BpmButton::paintButton(juce::Graphics& g, bool isHighlighted, bool isDown) {

    auto area = getLocalBounds().toFloat();
    area.reduce(0, scaled(25));
    
    if (isPlus) {
        plusIcon->drawWithin(g, area, juce::RectanglePlacement::centred, 1);
    }
    else
    {
        minusIcon->drawWithin(g, area, juce::RectanglePlacement::centred, 1);
    }

}

void BpmButton::resized()
{
    scaleFactor = juce::jmin(getTopLevelComponent()->getWidth() / 1600.0f,
        getTopLevelComponent()->getHeight() / 720.0f);
}