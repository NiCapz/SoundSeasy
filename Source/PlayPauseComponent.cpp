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
    g.drawText ("PlayPauseComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlayPauseComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
