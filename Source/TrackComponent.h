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
        auto area = getLocalBounds().reduced(60, 0);
        

        juce::FlexBox fb;
        //fb.flexWrap = juce::FlexBox::Wrap::noWrap;
        fb.flexDirection = juce::FlexBox::Direction::row;
        fb.justifyContent = juce::FlexBox::JustifyContent::spaceAround;

        fb.items.add(juce::FlexItem(inst).withMinWidth(200));

        for (auto* step : steps) 
        {
            fb.items.add(juce::FlexItem(*step).withMinWidth(80));
        }

        fb.performLayout(area);
    }

    bool isCurrentStepActive() {
        return steps[currentStepIndex]->checkActive();
    }

    InstrumentSelectorComponent inst;

private:
    juce::OwnedArray<StepComponent> steps;
    int currentStepIndex = 0;
};