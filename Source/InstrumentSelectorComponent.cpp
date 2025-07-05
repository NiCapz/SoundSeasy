/*
  ==============================================================================

    InstrumentSelectorComponent.cpp
    Created: 4 Jun 2025 11:29:51am
    Author:  Niko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "InstrumentSelectorComponent.h"

//==============================================================================
InstrumentSelectorComponent::InstrumentSelectorComponent()
{
}

InstrumentSelectorComponent::~InstrumentSelectorComponent()
{
}

float InstrumentSelectorComponent::scaled(float val) {
    return val * scaleFactor;
}

void InstrumentSelectorComponent::setName(juce::String name) {
    this->name = name;

    if (name == "Crash")
    {
        icon = juce::Drawable::createFromImageData(BinaryData::crash_svg, BinaryData::crash_svgSize);
    }
    else if (name == "Hi-Hat 1")
    {
        icon = juce::Drawable::createFromImageData(BinaryData::hihat_svg, BinaryData::hihat_svgSize);
    }
    else if (name == "Hi-Hat2")
    {
        icon = juce::Drawable::createFromImageData(BinaryData::hihat_open_svg, BinaryData::hihat_open_svgSize);
    } 
    else if (name == "Snare") 
    {
        icon = juce::Drawable::createFromImageData(BinaryData::snare_svg, BinaryData::snare_svgSize);
    }
    else if (name == "Kick")
    {
        icon = juce::Drawable::createFromImageData(BinaryData::kick_svg, BinaryData::kick_svgSize);
    }
}

void InstrumentSelectorComponent::paint (juce::Graphics& g)
{
    auto area = getLocalBounds().toFloat();

    scaleFactor = juce::jmin(getTopLevelComponent()->getWidth() / 1600,
        getTopLevelComponent()->getHeight() / 720);

    g.setColour(juce::Colour(0xffb9b9b9));
    g.fillRoundedRectangle(area, scaled(15.0f));

    if (icon != nullptr)
    {
        if (name != "Crash")
        {
        icon->drawWithin(g, area.reduced(scaled(20)), juce::RectanglePlacement::centred, 1.0f);
        }
        else {
        icon->drawWithin(g, area.reduced(scaled(22)), juce::RectanglePlacement::centred, 1.0f);
        }
    }

    g.setColour(juce::Colours::black);
}

void InstrumentSelectorComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
