/*
  ==============================================================================

    RewindComponent.cpp
    Created: 18 Jun 2025 2:31:16pm
    Author:  Niko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RewindComponent.h"

//==============================================================================
RewindComponent::RewindComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

RewindComponent::~RewindComponent()
{
}

void RewindComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    
    auto area = getLocalBounds();
    //g.drawRect(area);

    auto height = area.getHeight();
    auto paddingLeft = area.getWidth() * 0.1;

    juce::Path p;

    // left bar
    p.startNewSubPath(paddingLeft, height * 0.3);
    p.lineTo(paddingLeft, height * 0.7);
    p.lineTo(paddingLeft * 2, height * 0.7);
    p.lineTo(paddingLeft * 2, height * 0.3);
    p.closeSubPath();


    // triangle
    p.startNewSubPath(paddingLeft, height * 0.5);
    p.lineTo(paddingLeft + height * 0.4, height * 0.3);
    p.lineTo(paddingLeft + height * 0.4, height * 0.7);
    p.closeSubPath();

    g.fillPath(p);

    g.setColour(juce::Colours::black);
    g.strokePath(p, juce::PathStrokeType(1.0f));

}

void RewindComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
