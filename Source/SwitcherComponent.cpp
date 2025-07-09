/*
  ==============================================================================

    SwitcherComponent.cpp
    Created: 3 Jul 2025 2:59:29pm
    Author:  Niko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SwitcherComponent.h"

//==============================================================================
SwitcherComponent::SwitcherComponent(juce::String& name)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SwitcherComponent::~SwitcherComponent()
{
}

void SwitcherComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("SwitcherComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void SwitcherComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
