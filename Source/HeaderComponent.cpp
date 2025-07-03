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

    setupBpmLabel(bpmLabel);
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
    
    juce::DropShadow shadow(juce::Colours::black.withAlpha(.7f), 100, { 0, 0 });
    
    juce::Path shadowPath;

    shadowPath.addRoundedRectangle(sw.getBounds().reduced(30, 0), 15.0f);
    shadowPath.addRoundedRectangle(rw.getBounds().reduced(10, 0), 15.0f);
    shadowPath.addRoundedRectangle(pp.getBounds().reduced(10, 0), 15.0f);
    shadowPath.addRoundedRectangle(bpmBounds, 15.0f);
    
    shadow.drawForPath(g, shadowPath);

    g.setColour(juce::Colour(0xffb9b9b9));
    g.fillRoundedRectangle(bpmBounds.toFloat(), 15);
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
    juce::FlexBox mainFlex;
    mainFlex.flexDirection = juce::FlexBox::Direction::row;
    mainFlex.flexWrap = juce::FlexBox::Wrap::noWrap;
    mainFlex.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;

    juce::FlexBox switchGroup;
    switchGroup.flexDirection = juce::FlexBox::Direction::row;
    switchGroup.items.add(juce::FlexItem(sw).withMinWidth(150));

    juce::FlexBox ppGroup;
    ppGroup.flexDirection = juce::FlexBox::Direction::row;
    ppGroup.items.add(
        juce::FlexItem(rw).withMinWidth(125),
        juce::FlexItem(pp).withMinWidth(125)
    );

    juce::FlexBox bpmGroup;
    bpmGroup.flexDirection = juce::FlexBox::Direction::row;
    //bpmGroup.alignItems = juce::FlexBox::AlignItems::center;
    bpmGroup.items.add(
        juce::FlexItem(minus).withMinWidth(75),
        juce::FlexItem(bpmLabel).withMinWidth(125),
        juce::FlexItem(plus).withMinWidth(75)
    );

    mainFlex.items.add(
        juce::FlexItem(switchGroup).withFlex(1),
        juce::FlexItem(ppGroup).withFlex(1),
        juce::FlexItem(bpmGroup).withFlex(1)
    );

    auto area = getLocalBounds();
    area.reduce(60, 20);
    area.removeFromLeft(100);
    mainFlex.performLayout(area);
}

void HeaderComponent::setupBpmLabel(juce::TextEditor& bpmLabel) {
    bpmLabel.setJustification(juce::Justification::centred);
    bpmLabel.setInputRestrictions(3, "1234567890");
    bpmLabel.setColour(juce::TextEditor::backgroundColourId, juce::Colours::transparentWhite);
    bpmLabel.setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentWhite);
    bpmLabel.setColour(juce::TextEditor::focusedOutlineColourId, juce::Colours::transparentWhite);
    bpmLabel.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    /*
    juce::Font interFont = 
        juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::InterVariableFont_opszwght_ttf, 
            BinaryData::InterVariableFont_opszwght_ttfSize));
    bpmLabel.setFont(interFont.withPointHeight(32.0f));
    */
    bpmLabel.setFont(40.0f);
}