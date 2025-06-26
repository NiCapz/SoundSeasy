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
    for (int i = 0; i < 4; i++) {
        auto* track = new TrackComponent();
        tracks.add(track);
        addAndMakeVisible(track);
    }
}

BodyComponent::~BodyComponent()
{
}

void BodyComponent::paint (juce::Graphics& g)
{
}

void BodyComponent::updateStepIndexes(int index) {
    for (auto* track : tracks) {
        track->setStepIndex(index);
    }
}

void BodyComponent::resized()
{
    auto area = getLocalBounds();
    auto padding = area.getHeight() / 20;
    auto trackHeight = (area.getHeight() - padding * tracks.size()) / 4;

    for (auto* track : tracks) {
		area.removeFromTop(padding);
        track->setBounds(area.removeFromTop(trackHeight));
    }
}
