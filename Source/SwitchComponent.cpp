/*
  ==============================================================================

    SwitchComponent.cpp
    Created: 4 Jun 2025 11:29:24am
    Author:  Niko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SwitchComponent.h"

//==============================================================================
SwitchComponent::SwitchComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SwitchComponent::~SwitchComponent()
{
}

void SwitchComponent::paint (juce::Graphics& g)
{
        auto area = getLocalBounds();
        g.setColour(juce::Colours::white);
        auto height = area.getHeight();
        auto paddingLeft = area.getWidth() * 0.3;
        juce::Path p;

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("SwitchComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void SwitchComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
