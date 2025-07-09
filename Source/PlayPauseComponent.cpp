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

float PlayPauseComponent::scaled(float val) {
	return val * scaleFactor;
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
	//area.reduce(scaled(10), 0);
	g.setColour(juce::Colour(0xffb9b9b9));
	g.fillRoundedRectangle(area, scaled(15));
	
	area.reduce(scaled(25), scaled(25));
	
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
	scaleFactor = juce::jmin(getTopLevelComponent()->getWidth() / 1600,
		getTopLevelComponent()->getHeight() / 720);
}
