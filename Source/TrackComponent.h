/*
  ==============================================================================

    TackComponent.h
    Created: 23 May 2025 12:55:24pm
    Author:  Niko

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "StepComponent.h"
#include "InstrumentSelectorComponent.h"

class TrackComponent : public juce::Component
{
public:
    TrackComponent() {

        addAndMakeVisible(inst);

        for (int i = 0; i < 8; i++) {
            auto* step = new StepComponent();
            steps.add(step);
            addAndMakeVisible(step);
        }
    }

    void paint(juce::Graphics &g) override 
    {
		g.setColour(juce::Colours::white);
		//g.drawRect(getLocalBounds(), 1); // Draw a border around the track
    }

    void resized() override
    {
        auto area = getLocalBounds();
        auto stepWidth = area.getWidth() / 12;
        auto instWidth = stepWidth;
        auto padding = stepWidth/5;

        area.removeFromLeft(0.5 * stepWidth);
        //area.removeFromRight(0.5 * stepWidth);

        inst.setBounds(area.removeFromLeft(instWidth));

        for (auto* step : steps) {
			area.removeFromLeft(padding);
            step->setBounds(area.removeFromLeft(stepWidth));
        }
    }

private:
    juce::OwnedArray<StepComponent> steps;
    InstrumentSelectorComponent inst;
};