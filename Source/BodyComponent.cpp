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

   
}

BodyComponent::~BodyComponent()
{
}

float BodyComponent::scaled(float val) {
    return val * scaleFactor;
}

void BodyComponent::paint (juce::Graphics& g)
{
    juce::DropShadow shadow(juce::Colours::black.withAlpha(.7f), 100, { 0, 0 });
    juce::Path shadowPath;

    for (auto& track : tracks) 
    {
        auto instBounds = track->inst.getBoundsInParent();
        instBounds.setPosition(track->getX() + scaled(90), track->getY());
        shadowPath.addRoundedRectangle(instBounds, scaled(15));
    }

    shadow.drawForPath(g, shadowPath);
}

void BodyComponent::updateStepIndexes(int index) {
    for (auto* track : tracks) {
        track->setStepIndex(index);
    }
}

void BodyComponent::resized()
{
    scaleFactor = juce::jmin(getTopLevelComponent()->getWidth() / 1600.0f,
        getTopLevelComponent()->getHeight() / 720.0f);
    auto area = getLocalBounds();
   

    juce::FlexBox fb;
    fb.flexDirection = juce::FlexBox::Direction::column;
    fb.flexWrap = juce::FlexBox::Wrap::noWrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;

    for (auto* track : tracks)
    {
        fb.items.add(juce::FlexItem(*track).withMinHeight(scaled(75)));
    }

    area.reduce(scaled(50), scaled(50));

    fb.performLayout(area);
}
