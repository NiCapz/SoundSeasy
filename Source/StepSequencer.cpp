/*
  ==============================================================================

    StepSequencer.cpp
    Created: 24 Apr 2025 2:04:10pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#include "StepSequencer.h"

StepSequencer::StepSequencer(int numTracks, int numSteps)
{
    this->numSteps = numSteps;
    this->numTracks = numTracks;
    
    for(int track = 0; track < numTracks; track++)
    {
        buttons.emplace_back();
        for(int step = 0; step < numSteps; step++)
        {
            juce::String name = "Track ";
            juce::String trackNum(track);
            juce::String stepNum(step);
            name += trackNum;
            name += " Step ";
            name += stepNum;
            buttons[track].push_back(std::make_unique<SequencerButton>(name));
            addAndMakeVisible(*(buttons[track][step]));
            buttons[track][step]->setToggleable(true);
        }
    }
    
    for(auto& track : buttons)
        track[0]->setHightlighted(true);
}

StepSequencer::~StepSequencer()
{
    
}

void StepSequencer::paint(juce::Graphics& g)
{
    
}

void StepSequencer::resized()
{
    const auto localBounds = getLocalBounds();
    int width = localBounds.getWidth();
    int height = localBounds.getHeight();
    
    if(localBounds.getWidth() < localBounds.getHeight())
    {
        width = localBounds.getHeight();
        height = localBounds.getWidth();
    }
    
    const int numTracks = (int) buttons.size();
    const int numSteps = (int) buttons[0].size();
    
    const int buttonSize = 40;
    
    const int xPadding = (width - buttonSize * numSteps) / (numSteps - 1);
    const int yPadding = (height - buttonSize * numTracks) / (numTracks - 1);
    
    if(localBounds.getWidth() > localBounds.getHeight())
        for(int track = 0; track < numTracks; track++)
            for(int step = 0; step < numSteps; step++)
                buttons[track][step]->setBounds(step * (buttonSize + xPadding), track * (buttonSize + yPadding), buttonSize, buttonSize);
    else
        for(int track = 0; track < numTracks; track++)
            for(int step = 0; step < numSteps; step++)
                buttons[track][step]->setBounds(track * (buttonSize + yPadding), step * (buttonSize + xPadding), buttonSize, buttonSize);
}


void StepSequencer::nextStep()
{
    incrementHighlight();
}

void StepSequencer::reset()
{
    for(auto& track : buttons)
        track[highlightIndex]->setHightlighted(false);
    
    highlightIndex = 0;
    
    for(auto& track : buttons)
        track[highlightIndex]->setHightlighted(true);
}

void StepSequencer::incrementHighlight()
{
    for(auto& track : buttons)
        track[highlightIndex]->setHightlighted(false);
    
    highlightIndex++;
    highlightIndex %= numSteps;
    
    for(auto& track : buttons)
        track[highlightIndex]->setHightlighted(true);
}
