/*
  ==============================================================================

    InstrumentSelectorComponent.cpp
    Created: 4 Jun 2025 11:29:51am
    Author:  Niko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "InstrumentSelectorComponent.h"

//==============================================================================
InstrumentSelectorComponent::InstrumentSelectorComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

InstrumentSelectorComponent::~InstrumentSelectorComponent()
{
}

void InstrumentSelectorComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::darkslategrey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void InstrumentSelectorComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
