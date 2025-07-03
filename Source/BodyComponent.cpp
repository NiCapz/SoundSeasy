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

void BodyComponent::paint (juce::Graphics& g)
{
    juce::DropShadow shadow(juce::Colours::black.withAlpha(.7f), 100, { 0, 0 });
    juce::Path shadowPath;

    for (auto& track : tracks) 
    {
        auto instBounds = track->inst.getBoundsInParent();
        instBounds.setPosition(track->getX() + 90, track->getY());
        shadowPath.addRoundedRectangle(instBounds, 15);
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
    auto area = getLocalBounds();
   

    juce::FlexBox fb;
    fb.flexDirection = juce::FlexBox::Direction::column;
    fb.flexWrap = juce::FlexBox::Wrap::noWrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;

    for (auto* track : tracks)
    {
        fb.items.add(juce::FlexItem(*track).withMinHeight(75));
    }

    area.reduce(50, 50);

    fb.performLayout(area);
}
