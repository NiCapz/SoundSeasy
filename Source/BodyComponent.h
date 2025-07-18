/*
  ==============================================================================

    BodyComponent.h
    Created: 4 Jun 2025 11:28:45am
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TrackComponent.h"
#include "ChordSequencer.h"
#include "PianoSynthSwitch.h"

//==============================================================================
/*
*/
class BodyComponent  : public juce::Component
{
public:
    BodyComponent();
    ~BodyComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setDrumSequencerIndex(int index);
    void setChordSequencerIndex(int index);
    std::array<bool, 5> getDrumSequencerStep();
    std::optional<std::array<int, 3>> getChordStep();

    float scaled(float val);

    void setShowAccordSequencer(bool show);

    void toggleChordSequencer();
    
    void setPianoSynthSwitchCallback(std::function<void(bool)>);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BodyComponent)
    juce::String trackNames[5] = { "Crash", "Hi-Hat 1", "Hi-Hat 2", "Snare", "Kick" };
    float scaleFactor = 1.0f;
    bool shadowsRendered = false;
    
    bool showAccordSequencer = false;
    
    juce::OwnedArray<TrackComponent> tracks;
    ChordSequencer chordSequencer{};
    
    const juce::String pianoSynthName{"PianoSynthSwitch"};
    PianoSynthSwitch pianoSynthSwitch{pianoSynthName};
};
