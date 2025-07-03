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
    
    addAndMakeVisible(sw);
    addAndMakeVisible(pp);
    addAndMakeVisible(rw);
    addAndMakeVisible(bpmLabel);
    addAndMakeVisible(plus);
    addAndMakeVisible(minus);



    bpmLabel.setJustification(juce::Justification::centred);
    bpmLabel.setInputRestrictions(3, "1234567890");
    bpmLabel.applyColourToAllText(juce::Colours::black);
}

HeaderComponent::~HeaderComponent()
{
}


void HeaderComponent::setTempoLabelText(int bpm) 
{
    bpmLabel.setText((juce::String) bpm);
}

void HeaderComponent::paint(juce::Graphics& g)
{
    g.setColour(juce::Colour (0xFF585858));
    g.fillAll();

    auto bpmBounds = minus.getBounds();
    bpmBounds = bpmBounds.getUnion(bpmLabel.getBounds());
    bpmBounds = bpmBounds.getUnion(plus.getBounds());
    bpmBounds.reduce(0, 25);
    g.setColour(juce::Colour(0xffb9b9b9));
    g.fillRoundedRectangle(bpmBounds.toFloat(), 25);
}

void HeaderComponent::setRewindCallback(std::function <void()> callback) {
    rw.onClick = callback;
}

void HeaderComponent::setTempoIncrementCallback(std::function <void()> callBack) {
    plus.onClick = callBack;
}

void HeaderComponent::setTempoDecrementCallback(std::function <void()> callback) {
    minus.onClick = callback;
}

void HeaderComponent::setPlayPauseCallback(std::function <void(bool isButtonPlaying)> callback) 
{
    pp.onClick = [this, callback]() {
        pp.toggleState();
        callback(pp.getState());
    };
}

void HeaderComponent::resized()
{
    juce::FlexBox fb;
    fb.flexDirection = juce::FlexBox::Direction::row;
    fb.flexWrap = juce::FlexBox::Wrap::noWrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::spaceAround;

    fb.items.add(
        juce::FlexItem(sw).withMinWidth(150.0f),
        juce::FlexItem(rw).withMinWidth(150.0f),
        juce::FlexItem(pp).withMinWidth(150.0f),
        juce::FlexItem(minus).withMinWidth(150.0f),
        juce::FlexItem(bpmLabel).withMinWidth(150.0f),
        juce::FlexItem(plus).withMinWidth(150.0f)
    );

    fb.performLayout(getLocalBounds());
}
