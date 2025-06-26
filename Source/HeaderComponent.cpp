/*
  ==============================================================================

    HeaderComponent.cpp
    Created: 4 Jun 2025 11:28:32am
    Author:  Niko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HeaderComponent.h"

//==============================================================================
HeaderComponent::HeaderComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(pp);
    addAndMakeVisible(rw);
    addAndMakeVisible(bpmLabel);
    addAndMakeVisible(plus);
    addAndMakeVisible(minus);

    bpmLabel.setJustification(juce::Justification::centred);
    bpmLabel.setInputRestrictions(3, "1234567890");
}

HeaderComponent::~HeaderComponent()
{
}

void HeaderComponent::setTempoLabelText(int bpm) {
    bpmLabel.setText((juce::String) bpm);
}

void HeaderComponent::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::black);

    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
    g.setColour(juce::Colours::white);

    g.setFont(juce::FontOptions(14.0f));
    g.drawText("HeaderComponent", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text

}

void HeaderComponent::setTempoIncrementCallback(std::function <void()> callBack) {
    plus.onClick = callBack;
}

void HeaderComponent::setTempoDecrementCallback(std::function <void()> callback) {
    minus.onClick = callback;
}

void HeaderComponent::setPlayPauseCallback(std::function <void()> callback) {
    pp.onClick = callback;
}



void HeaderComponent::resized()
{
    auto area = getLocalBounds();

    auto paddingWidth = area.getWidth() / 4;
    auto buttonWidth = paddingWidth / 4;

    area.removeFromLeft(paddingWidth);
    rw.setBounds(area.removeFromLeft(buttonWidth));
    pp.setBounds(area.removeFromLeft(buttonWidth));

    area.removeFromRight(paddingWidth/2);
    minus.setBounds(area.removeFromRight(buttonWidth));
    bpmLabel.setBounds(area.removeFromRight(buttonWidth * 2));
    plus.setBounds(area.removeFromRight(buttonWidth));

}
