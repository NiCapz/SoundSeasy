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
    
    transposeUpButton.setIcon(juce::Drawable::createFromImageData(BinaryData::up_arrow_svg, BinaryData::up_arrow_svgSize));
    transposeDownButton.setIcon(juce::Drawable::createFromImageData(BinaryData::down_arrrow_svg, BinaryData::down_arrrow_svgSize));
    
    transposeUpButton.onClick = [&] ()
    {
        if(baseNoteNumber < 100)
            baseNoteNumber += 1;
        
        for(auto& step : steps)
            for(auto* button : step)
                button->setBaseNoteNumber(baseNoteNumber);
        
        repaint();
    };
    
    transposeDownButton.onClick = [&] ()
    {
        if(baseNoteNumber >= 48)
            baseNoteNumber -= 1;
        
        for(auto& step : steps)
            for(auto* button : step)
                button->setBaseNoteNumber(baseNoteNumber);
        
        repaint();
    };
    
    addAndMakeVisible(&transposeUpButton);
    addAndMakeVisible(&transposeDownButton);
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
    
    auto mainButtonArea = columnLayout[0].reduced(buttonPadding, buttonPadding);
    const float strokeWeight = 3;
    
    g.setColour(juce::Colour(0xffb9b9b9));
    g.fillRoundedRectangle(mainButtonArea.toFloat(), 15);
    
    g.setFont(area.getHeight() / 5);
    g.setColour(juce::Colours::black);
    g.drawText(noteNumberToName(baseNoteNumber), columnLayout[0].reduced(0, area.getHeight() / 3), juce::Justification(36));
 
    if(activeStepIndex == 0)
    {
        g.setColour(juce::Colour(0xffD0D0D0));
        g.drawRoundedRectangle(columnLayout[0].reduced(1.3 * strokeWeight, 1.3 * strokeWeight), 20, strokeWeight);
    }
}

void ChordSequencer::resized()
{
    auto area = getLocalBounds();
    const float leftMargin = area.getWidth() / 4;
    const float topMargin = area.getHeight() / 40;
    area.removeFromRight(leftMargin);
    area.removeFromTop(topMargin);
    area.removeFromBottom(topMargin);
    area.translate(leftMargin, topMargin / 2);
    
    float columnWidth = (area.getWidth() - (numSteps - 1) * columnMarign) / numSteps;
    float xIncrement = columnWidth + columnMarign;
    
    for(int i = 0; i < numSteps; i++)
        columnLayout[i] = juce::Rectangle<float>(area.getX() + i * xIncrement, area.getY(), columnWidth, area.getHeight());
    
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
    
    juce::FlexBox flex;
    flex.flexDirection = juce::FlexBox::Direction::column;
    flex.flexWrap = juce::FlexBox::Wrap::noWrap;
    flex.justifyContent = juce::FlexBox::JustifyContent::center;
    
    const float outerMargin = area.getHeight() / 7;
    const float horizontalMargin = columnLayout[0].getWidth() / 2.7;
    
    flex.items.add(juce::FlexItem(transposeUpButton).withFlex(1).withMargin({outerMargin, horizontalMargin, 0, horizontalMargin}));
    flex.items.add(juce::FlexItem(transposeDownButton).withFlex(1).withMargin({0, horizontalMargin, outerMargin, horizontalMargin}));
    flex.performLayout(columnLayout[0]);
}

void ChordSequencer::increment()
{
    if(activeStepIndex != 0)
    {
        for(auto* button : steps[activeStepIndex - 1])
            if(button->getActive())
                button->setHighlighted(false);
    }
    
    activeStepIndex++;
    activeStepIndex %= numSteps;
    
    if(activeStepIndex != 0)
    {
        for(auto* button : steps[activeStepIndex - 1])
            if(button->getActive())
                button->setHighlighted(true);
    }
    
}

void ChordSequencer::setIndex(int i)
{
    if(activeStepIndex != 0)
    {
        for(auto* button : steps[activeStepIndex - 1])
            if(button->getActive())
                button->setHighlighted(false);
    }
    
    activeStepIndex = i % numSteps;
    
    if(activeStepIndex != 0)
    {
        for(auto* button : steps[activeStepIndex - 1])
            if(button->getActive())
                button->setHighlighted(true);
    }
}

std::optional<std::array<int, 3>> ChordSequencer::getCurrentChord()
{
    if(activeStepIndex == 0)
    {
        return chordToNotes(baseNoteNumber, {1, MAJOR});
    }
    
    for(auto* button : steps[activeStepIndex - 1])
    {
        if(button->getActive())
        {
            Chord chord = button->getChord();
            int offset = 0;
            if(chord.degree > 5)
                offset = -12;
            
            return chordToNotes(baseNoteNumber + offset, button->getChord());
        }
    }
        
    return {};
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
            button->setHighlighted(false);
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
    auto innerArea = area.reduced(buttonPadding, buttonPadding);
    const float strokeWeight = 3;
    auto highlightArea = area.reduced(1.3 * strokeWeight, 1.3 * strokeWeight);
    if(isActive)
    {
        g.setColour(juce::Colour(0xffb9b9b9));
    }
    else
    {
        g.setColour(juce::Colour(0xff919191));
    }
    
    g.fillRoundedRectangle(innerArea.toFloat(), 15);
    
    if(isHighlighted)
    {
        g.setColour(juce::Colour(0xffD0D0D0));
        g.drawRoundedRectangle(highlightArea.toFloat(), 20, strokeWeight);
    }
    
    g.setFont(area.getHeight() / 5);
    g.setColour(juce::Colours::black);
    g.drawText(chordName(baseNoteNumber, chordTree->chord), area, juce::Justification(36));
    
    
}
