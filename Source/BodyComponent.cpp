/*
  ==============================================================================

    BodyComponent.cpp
    Created: 4 Jun 2025 11:28:45am
    Author:  Niko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BodyComponent.h"

//==============================================================================
BodyComponent::BodyComponent()
{
    for (int i = 0; i < 5; i++) {
        auto* track = new TrackComponent(trackNames[i]);
        tracks.add(track);
        addAndMakeVisible(track);
    }

    
    addAndMakeVisible(chordSequencer);
    //make the chord sequencer invisible at the start
    //chordSequencer.setBounds(0, 0, 0, 0);
    
}

BodyComponent::~BodyComponent()
{
}

float BodyComponent::scaled(float val) {
    return val * scaleFactor;
}

void BodyComponent::setShowAccordSequencer(bool show) {
    showAccordSequencer = show;
}

void BodyComponent::toggleChordSequencer()
{
    showAccordSequencer = !showAccordSequencer;
    resized();
}

void BodyComponent::paint (juce::Graphics& g)
{
    //juce::DropShadow shadow(juce::Colours::black.withAlpha(.7f), 100, { 0, 0 });
    juce::Path shadowPath;

    auto area = getLocalBounds().toFloat();

    if (!showAccordSequencer)
    {

    for (auto& track : tracks) 
    {
        auto instBounds = track->inst.getBounds();
        instBounds.setPosition(track->getX()+ scaled(75), track->getY());
        shadowPath.addRoundedRectangle(instBounds, scaled(15));
    }
    }

    static juce::Image shadowImage;
    juce::DropShadow shadow(juce::Colours::black.withAlpha(.5f), 100, { 0, 0 });

    if (!shadowsRendered)
    {
        shadowImage = juce::Image(juce::Image::PixelFormat::ARGB,
            area.getWidth(),
            area.getHeight(),
            true);
        juce::Graphics shadowGraphics(shadowImage);
        shadow.drawForPath(shadowGraphics, shadowPath);
        shadowsRendered = true;
    }

    g.drawImage(shadowImage, area);

     //shadow.drawForPath(g, shadowPath);
}

void BodyComponent::updateStepIndexes(int index) {
    for (auto* track : tracks) {
        track->setStepIndex(index);
    }
}

void BodyComponent::resized()
{
    juce::FlexBox fb;
    fb.flexDirection = juce::FlexBox::Direction::column;
    fb.flexWrap = juce::FlexBox::Wrap::noWrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    for (auto* track : tracks)
    {
        fb.items.add(juce::FlexItem(*track).withMinHeight(scaled(75)));
    }
    
    if (!showAccordSequencer)
    {
        scaleFactor = juce::jmin(getTopLevelComponent()->getWidth() / 1600.0f,
            getTopLevelComponent()->getHeight() / 720.0f);
        auto area = getLocalBounds();
        
        area.reduce(scaled(50), scaled(50));
        fb.performLayout(area);
        shadowsRendered = false;
        //hide chord sequencer
        chordSequencer.setBounds({0, 0, 0, 0});
    }
    else
    {
        //hide drum sequencer
        fb.performLayout(juce::Rectangle<float>(0, 0, 0, 0));
        scaleFactor = juce::jmin(getTopLevelComponent()->getWidth() / 1600.0f,
            getTopLevelComponent()->getHeight() / 720.0f);
        auto area = getLocalBounds();
        area.reduce(scaled(50), scaled(50));
        chordSequencer.setBounds(area);
    }
}
