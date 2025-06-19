#pragma once

#include <JuceHeader.h>
#include "./Audio/DrumMachine/DrumSampler.h"
#include "./Audio/Synth/Synth.h"
#include "./Audio/Piano/PianoSampler.h"
#include "./Audio/MidiManager.h"

using namespace juce;
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class MainComponent  : public AudioAppComponent, Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    void timerCallback() override;

private:
    //==============================================================================
    // Your private member variables go here...


    DrumSampler drumSampler{};
    Synth synth{};
    PianoSampler piano{};
    
    MidiManager midiManager{};
    double startTime;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
