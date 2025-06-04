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
    for (int i = 0; i <= 4; i++) {
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
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
}

void BodyComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto area = getLocalBounds();
    auto trackHeight = area.getHeight() * 0.25;

    for (auto* track : tracks) {
        track->setBounds(area.removeFromTop(trackHeight));
    }
}
