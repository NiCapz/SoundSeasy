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
}

BpmButton::~BpmButton()
{
}

void BpmButton::paintButton(juce::Graphics& g, bool isHighlighted, bool isDown) {
    g.setColour(juce::Colours::white);

    auto area = getLocalBounds();

    auto padding = (area.getHeight() - area.getWidth()) / 2;

    area.removeFromTop(padding);
    area.removeFromBottom(padding);

    auto padding2 = area.getWidth() * -.1;
    area.expand(padding2, padding2);

    g.drawEllipse(area.toFloat(), 3.0f);

    g.setFont(juce::FontOptions(50.0f));

    juce::String buttonText = "-";

    if (isPlus) {
        buttonText = "+";
    }

    g.setFont(juce::FontOptions(14.0f));
    g.drawText(buttonText, area, juce::Justification::centred);
}

void BpmButton::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}