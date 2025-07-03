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
PlayPauseComponent::PlayPauseComponent(juce::String& name) : Button(name)
{
	playIcon = juce::Drawable::createFromImageData(BinaryData::play_svg, BinaryData::play_svgSize);
	pauseIcon = juce::Drawable::createFromImageData(BinaryData::pause_svg, BinaryData::pause_svgSize);
}

PlayPauseComponent::~PlayPauseComponent()
{
}

bool PlayPauseComponent::getState() {
	return isPlaying;
}

void PlayPauseComponent::toggleState() {
	isPlaying = !isPlaying;
}

void PlayPauseComponent::paintButton(juce::Graphics& g, bool isHighlighted, bool isDown)
{
	auto area = getLocalBounds().toFloat();
	area.reduce(10, 0);
	g.setColour(juce::Colour(0xffb9b9b9));
	g.fillRoundedRectangle(area, 15);
	
	area.reduce(25, 25);
	
	if (!isPlaying)
	{
		if (playIcon != nullptr) {
			playIcon->drawWithin(g, area, juce::RectanglePlacement::centred, 1.0f);
		}  
	}
	else
	{
		if (pauseIcon != nullptr) {
			pauseIcon->drawWithin(g, area, juce::RectanglePlacement::centred, 1.0f);
		}
	}
}

void PlayPauseComponent::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..

}
