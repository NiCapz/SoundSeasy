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

        for (int i = 0; i <= 8; i++) {
            auto* step = new StepComponent();
            steps.add(step);
            addAndMakeVisible(step);
        }
    }

    void paint(juce::Graphics &g) override 
    {
        g.drawRoundedRectangle(getLocalBounds().toFloat(), 0.0f, 1.0f);
    }

    void resized() override
    {
        auto area = getLocalBounds();
        auto stepWidth = area.getWidth() * 0.1;
        auto instWidth = stepWidth * 2;

        inst.setBounds(area.removeFromLeft(instWidth));

        for (auto* step : steps) {
            step->setBounds(area.removeFromLeft(stepWidth));

        }
    }

private:
    juce::OwnedArray<StepComponent> steps;
    InstrumentSelectorComponent inst;
};