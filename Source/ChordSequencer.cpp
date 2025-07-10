/*
  ==============================================================================

    ChordSequencer.cpp
    Created: 10 Jul 2025 11:50:46am
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#include "ChordSequencer.h"

ChordSequencer::ChordSequencer()
{
    int newChordIndex = 0;
    for(const ChordTree& chord : majorProgressions.nextChords)
    {
        ChordButton* b = new ChordButton(buttonName, &chord, [&, newChordIndex] () { onChordButtonClicked(0, newChordIndex); });
        addAndMakeVisible(b);
        steps[0].add(b);
        newChordIndex++;
    }
}

ChordSequencer::~ChordSequencer()
{
    
}

void ChordSequencer::paint(juce::Graphics& g)
{
    g.setColour(juce::Colour(0xff000000));
    g.drawRect(getLocalBounds());
}

void ChordSequencer::resized()
{
    auto area = getLocalBounds();
    float columnWidth = (area.getWidth() - (numSteps - 1) * columnMarign) / numSteps;
    float xIncrement = columnWidth + columnMarign;
    
    for(int i = 0; i < numSteps; i++)
        columnLayout[i] = juce::Rectangle<float>(i * xIncrement, 0, columnWidth, area.getHeight());
    
    for(int i = 0; i < numSteps - 1; i++)
    {
        juce::FlexBox flex;
        flex.flexDirection = juce::FlexBox::Direction::column;
        flex.flexWrap = juce::FlexBox::Wrap::noWrap;
        flex.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
        
        for(ChordButton* b : steps[i])
            flex.items.add(juce::FlexItem(*b).withFlex(1, 1).withMargin({10, 0, 0, 0}));
        
        flex.performLayout(columnLayout[i + 1]);
    }
}

void ChordSequencer::onChordButtonClicked(int stepIndex, int chordIndex)
{
    bool stepHasActiveButton = false;
    const std::list<ChordTree>* nextChords;
    for(int chord = 0; chord < steps[stepIndex].size(); chord++)
    {
        
        ChordButton* button = steps[stepIndex][chord];
        if(chord == chordIndex)
        {
            if(button->getActive())
            {
                nextChords = button->getNextChords();
                stepHasActiveButton = true;
            }
        }
        else
        {
            if(button->getActive())
            {
                button->setActive(false);
            }
        }
    }
    
    for(int step = stepIndex + 1; step < steps.size(); step++)
        steps[step].clear(true);
    
    int newChordIndex = 0;
    if(stepHasActiveButton && nextChords != nullptr)
    {
        if(stepIndex < steps.size() - 1)
        {
            for(const ChordTree& chord : *nextChords)
            {
                ChordButton* b = new ChordButton(buttonName, &chord, [&, stepIndex, newChordIndex] () { onChordButtonClicked(stepIndex + 1, newChordIndex); });
                addAndMakeVisible(b);
                steps[stepIndex + 1].add(b);
                newChordIndex++;
            }
        }
    }
    resized();
}

void ChordSequencer::ChordButton::resized()
{
    
}

void ChordSequencer::ChordButton::paintButton(juce::Graphics& g, bool down, bool highlighted)
{
    g.setColour(juce::Colour(0xffb9b9b9));
    g.drawRect(getLocalBounds());
    
    if(highlighted)    
    {
        g.fillRect(getLocalBounds());
    }
    
    g.setColour(juce::Colours::black);
    g.drawText(chordName(baseNoteNumber, chordTree->chord), getLocalBounds(), juce::Justification(36));
    
    
}
