/*
  ==============================================================================

    ChordSequencer.h
    Created: 10 Jul 2025 11:50:36am
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ChordProgressions.h"
#include "SVGButton.h"

class ChordSequencer : public juce::Component
{
public:
    ChordSequencer();
    ~ChordSequencer();
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void increment();
    void setIndex(int);
    
    std::optional<std::array<int, 3>> getCurrentChord();
    
private:
    
    class ChordButton : public juce::Button
    {
    public:
        ChordButton(const juce::String& name, const ChordTree* tree, std::function<void()> callback) : Button(name), chordTree(tree)
        {
            onClick = [this, callback] ()
            {
                this->isActive = !this->isActive;
                callback();
            };
            setToggleable(true);
        }
        ~ChordButton() {}

        void resized() override;

        void paintButton(juce::Graphics&, bool, bool) override;
        
        const Chord getChord() { return chordTree->chord; }
        const std::list<ChordTree>* getNextChords() { return &(chordTree->nextChords); }
        
        void setBaseNoteNumber(int noteNumber) { baseNoteNumber = noteNumber; }
        
        bool getActive() { return isActive; }
        void setActive(bool val)
        {
            isActive = val;
            repaint();
        }
        void setHighlighted(bool val)
        {
            isHighlighted = val;
            repaint();
        }
    private:
        const ChordTree* chordTree;
        int baseNoteNumber = 60;
        bool isActive = false;
        bool isHighlighted = false;
    };
    
    static constexpr int numSteps = 4;
    std::array<juce::OwnedArray<ChordButton>, numSteps - 1> steps;
    int activeStepIndex = 0;
    
    int baseNoteNumber = 60;
    
    const juce::String buttonName{"Chord Button"};
    
    void onChordButtonClicked(int step, int chordIndex);
    
    std::array<juce::Rectangle<float>, numSteps> columnLayout;
    static constexpr float columnMarign = 20;
    static constexpr float buttonPadding = 7;
    
    
    const juce::String n{"Transpose Button"};
    
    SVGButton transposeUpButton{n, juce::Colour(0x00000000)};
    SVGButton transposeDownButton{n, juce::Colour(0x00000000)};
};
