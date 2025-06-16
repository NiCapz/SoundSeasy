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

}

HeaderComponent::~HeaderComponent()
{
}

void HeaderComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::black);
    
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour(juce::Colours::white);
    
    g.setFont(juce::FontOptions(14.0f));
    g.drawText ("HeaderComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void HeaderComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
