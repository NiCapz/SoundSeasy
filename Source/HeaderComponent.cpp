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
    scaleFactor = juce::jmin(getTopLevelComponent()->getWidth() / 1600.0f,
        getTopLevelComponent()->getHeight() / 720.0f);
    
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
    
    static juce::Image shadowImage;
    static bool shadowsRendered = false;
    juce::DropShadow shadow(juce::Colours::black.withAlpha(.5f), 20, { 0, 4 });

    if (!shadowsRendered) 
    {
        shadowImage = juce::Image(juce::Image::PixelFormat::ARGB,
            getLocalBounds().getWidth(),
            getLocalBounds().getHeight(),
            true);
        juce::Graphics shadowGraphics(shadowImage);
        
        juce::Path shadowPath;
        shadowPath.addRoundedRectangle(sw.getBounds().reduced(scaled(30), 0), scaled(15.0f));
        shadowPath.addRoundedRectangle(rw.getBounds().reduced(scaled(10), 0), scaled(15.0f));
        shadowPath.addRoundedRectangle(pp.getBounds().reduced(scaled(10), 0), scaled(15.0f));
        shadowPath.addRoundedRectangle(bpmBounds, scaled(15.0f));
        shadow.drawForPath(shadowGraphics, shadowPath);
        shadowsRendered = true;
    }

    g.drawImage(shadowImage, getLocalBounds().toFloat());
   
    g.setColour(juce::Colour(0xffb9b9b9));
    g.fillRoundedRectangle(bpmBounds.toFloat(), scaled(15.0f));

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

float HeaderComponent::scaled(float val) {
    return val * scaleFactor;
}

void HeaderComponent::resized()
{
    scaleFactor = juce::jmin(getTopLevelComponent()->getWidth() / 1600.0f,
        getTopLevelComponent()->getHeight() / 720.0f);

    juce::FlexBox mainFlex;
    mainFlex.flexDirection = juce::FlexBox::Direction::row;
    mainFlex.flexWrap = juce::FlexBox::Wrap::noWrap;
    mainFlex.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;

    juce::FlexBox switchGroup;
    switchGroup.flexDirection = juce::FlexBox::Direction::row;
    switchGroup.items.add(juce::FlexItem(sw).withMinWidth(scaled(150)));

    juce::FlexBox ppGroup;
    ppGroup.flexDirection = juce::FlexBox::Direction::row;
    ppGroup.items.add(
        juce::FlexItem(rw).withMinWidth(scaled(125)),
        juce::FlexItem(pp).withMinWidth(scaled(125))
    );

    juce::FlexBox bpmGroup;
    bpmGroup.flexDirection = juce::FlexBox::Direction::row;
    //bpmGroup.alignItems = juce::FlexBox::AlignItems::center;
    bpmGroup.items.add(
        juce::FlexItem(minus).withMinWidth(scaled(75)),
        juce::FlexItem(bpmLabel).withMinWidth(scaled(125)),
        juce::FlexItem(plus).withMinWidth(scaled(75))
    );

    mainFlex.items.add(
        juce::FlexItem(switchGroup).withFlex(1),
        juce::FlexItem(ppGroup).withFlex(1),
        juce::FlexItem(bpmGroup).withFlex(1)
    );

    auto area = getLocalBounds();
    area.reduce(scaled(60), scaled(20));
    area.removeFromLeft(scaled(100));
    mainFlex.performLayout(area);

}

void HeaderComponent::setupBpmLabel(juce::TextEditor& bpmLabel) {
    bpmLabel.setJustification(juce::Justification::centred);
    bpmLabel.setInputRestrictions(3, "1234567890");
    bpmLabel.setColour(juce::TextEditor::backgroundColourId, juce::Colours::transparentWhite);
    bpmLabel.setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentWhite);
    bpmLabel.setColour(juce::TextEditor::focusedOutlineColourId, juce::Colours::transparentWhite);
    bpmLabel.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    
    juce::Font interFont = 
        juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::InterVariableFont_opszwght_ttf, 
            BinaryData::InterVariableFont_opszwght_ttfSize));

    interFont.setBold(true);
    bpmLabel.setFont(interFont.withPointHeight(32.0f));
}