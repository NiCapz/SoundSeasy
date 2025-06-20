/*
  ==============================================================================

    PlayPauseComponent.cpp
    Created: 4 Jun 2025 11:28:58am
    Author:  Niko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayPauseComponent.h"

//==============================================================================
PlayPauseComponent::PlayPauseComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

PlayPauseComponent::~PlayPauseComponent()
{
}

void PlayPauseComponent::paint (juce::Graphics& g)
{
    auto area = getLocalBounds();
    g.setColour(juce::Colours::white);
    //g.drawRect(area);

    auto height = area.getHeight();
    auto paddingLeft = area.getWidth() * 0.3;
    

    juce::Path p;
    p.startNewSubPath(paddingLeft, height * 0.3);
    p.lineTo(paddingLeft, height * 0.7);
    p.lineTo(paddingLeft + height * 0.4, height* 0.5);
    p.closeSubPath();

    g.fillPath(p);

    g.setColour(juce::Colours::black);
    g.strokePath(p, juce::PathStrokeType(1.0f));
}

void PlayPauseComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
