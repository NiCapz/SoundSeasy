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
}

InstrumentSelectorComponent::~InstrumentSelectorComponent()
{
}



void InstrumentSelectorComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    auto area = getLocalBounds();
    //g.drawRoundedRectangle(lb.getX() + lb.getWidth() * .1, lb.getY() + lb.getY() * .1, lb.getWidth() * .9, lb.getHeight() * .9, 10.0f, 1.0f);
    
	//g.drawRect(lb, 1.0f);

    auto padding = area.getHeight() * 0.1;
    area.removeFromTop(padding);
    area.removeFromBottom(padding);
    g.drawRoundedRectangle(area.getX(), area.getY(), area.getWidth(), area.getHeight(), 10.0f, 1.0f);

    
    g.drawText("Kickdrum", area, juce::Justification::centred, true);

}

void InstrumentSelectorComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
