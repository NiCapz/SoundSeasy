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
    TrackComponent(juce::String instrumentName) {

        addAndMakeVisible(inst);

        inst.setName(instrumentName);

        for (int i = 0; i < 8; i++) {
            juce::String stepName = "Step " + (juce::String)i;
            auto* step = new StepComponent(stepName);
            steps.add(step);
            addAndMakeVisible(step);
        }
    }

    void paint(juce::Graphics &g) override 
    {
    }

    void setStepIndex(int index) {
        steps[currentStepIndex]->setHighlighted(false);
        currentStepIndex = index;
        steps[currentStepIndex]->setHighlighted(true);
        repaint();
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

    bool isCurrentStepActive() {
        return steps[currentStepIndex]->checkActive();
    }


private:
    juce::OwnedArray<StepComponent> steps;
    InstrumentSelectorComponent inst;
    int currentStepIndex = 0;
};