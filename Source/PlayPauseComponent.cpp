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

}

PlayPauseComponent::~PlayPauseComponent()
{
}

void PlayPauseComponent::clicked() {
	isPlaying = !isPlaying;
}

void PlayPauseComponent::paintButton(juce::Graphics& g, bool isHighlighted, bool isDown)
{
	auto area = getLocalBounds();
	g.setColour(juce::Colours::white);
	auto height = area.getHeight();
	auto paddingLeft = area.getWidth() * 0.3;
	juce::Path p;

	if (!isPlaying)
	{
		p.startNewSubPath(paddingLeft, height * 0.3);
		p.lineTo(paddingLeft, height * 0.7);
		p.lineTo(paddingLeft + height * 0.4, height * 0.5);
		p.closeSubPath();

	}
	else
	{
		p.startNewSubPath(paddingLeft, height * 0.3);
		p.lineTo(paddingLeft, height * 0.7);
		p.lineTo(paddingLeft * 2, height * 0.7);
		p.lineTo(paddingLeft * 2, height * 0.3);
		p.closeSubPath();

		auto morePadding = paddingLeft * 2 + area.getWidth() * .1;

		p.startNewSubPath(morePadding, height * 0.3);
		p.lineTo(morePadding, height * 0.7);
		p.lineTo(morePadding + paddingLeft, height * 0.7);
		p.lineTo(morePadding + paddingLeft, height * 0.3);
		p.closeSubPath();
	}

	g.fillPath(p);
	g.setColour(juce::Colours::black);
	g.strokePath(p, juce::PathStrokeType(1.0f));
}

void PlayPauseComponent::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..

}
