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
    auto area = getLocalBounds();
    juce::Path backgroundPath;
    for(auto col : columnLayout)
        backgroundPath.addRoundedRectangle(col, 20);
    
    g.setColour(juce::Colour(0xff414141));
    g.fillPath(backgroundPath);
    
    g.setColour(juce::Colour(0xffb9b9b9));
    g.fillRoundedRectangle(columnLayout[0], 20);
    
    g.setFont(area.getHeight() / 5);
    g.setColour(juce::Colours::black);
    g.drawText(noteNumberToName(baseNoteNumber), columnLayout[0].reduced(0, area.getHeight() / 3), juce::Justification(36));
 
}

void ChordSequencer::resized()
{
    auto area = getLocalBounds();
    const float leftMargin = area.getWidth() / 4;
    area.removeFromRight(leftMargin);
    
    float columnWidth = (area.getWidth() - (numSteps - 1) * columnMarign) / numSteps;
    float xIncrement = columnWidth + columnMarign;
    
    for(int i = 0; i < numSteps; i++)
        columnLayout[i] = juce::Rectangle<float>(leftMargin + i * xIncrement, 0, columnWidth, area.getHeight());
    
    for(int i = 0; i < numSteps - 1; i++)
    {
        juce::FlexBox flex;
        flex.flexDirection = juce::FlexBox::Direction::column;
        flex.flexWrap = juce::FlexBox::Wrap::noWrap;
        flex.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
        
        for(int button = 0; button < steps[i].size(); button++)
        {
            ChordButton* b = steps[i][button];
            if(button == 0)
                flex.items.add(juce::FlexItem(*b).withFlex(1, 1));
            else
                flex.items.add(juce::FlexItem(*b).withFlex(1, 1).withMargin({(float) area.getHeight() / 30, 0, 0, 0}));
        }
        
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
            button->setActive(false);
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
    auto area = getLocalBounds();
    if(isActive)
    {
        g.setColour(juce::Colour(0xffb9b9b9));
    }
    else
    {
        g.setColour(juce::Colour(0xff919191));
    }
    
    g.fillRoundedRectangle(area.toFloat(), 20);
    
    g.setFont(area.getHeight() / 5);
    g.setColour(juce::Colours::black);
    g.drawText(chordName(baseNoteNumber, chordTree->chord), area, juce::Justification(36));
    
    
}
