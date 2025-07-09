#pragma once

#include <JuceHeader.h>
#include "HeaderComponent.h"
#include "BodyComponent.h"
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
class MainComponent : public juce::AudioAppComponent, juce::Timer, juce::TextEditor::Listener
{
public:

    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    
    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

    void textEditorReturnKeyPressed(juce::TextEditor& editor) override;
    void textEditorFocusLost(juce::TextEditor& editor) override;

    void bpmChanged();

private:
    //==============================================================================
    // Your private member variables go here...
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
    HeaderComponent header;
    BodyComponent body;
    int bpm = 120;
    bool bpmJustChanged = false;
    int currentStepIndex = 0;
    const int stepsTotal = 8;
    bool isPlaying = false;


    DrumSampler drumSampler{};
    Synth synth{};
    PianoSampler piano{};

    MidiManager midiManager{};
    double startTime;

};
