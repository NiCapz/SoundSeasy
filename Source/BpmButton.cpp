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

void BpmButton::paintButton(juce::Graphics& g, bool isHighlighted, bool isDown) {

    auto area = getLocalBounds().toFloat();

    area.reduce(0, 50);
    
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
    // This method is where you should set the bounds of any child
    // components that your component contains..

}