#pragma once

#include <JuceHeader.h>
#include "HeaderComponent.h"
#include "BodyComponent.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::Component, juce::Timer, juce::TextEditor::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

    void textEditorTextChanged(juce::TextEditor& editor) override;

    void bpmChanged();

private:
    //==============================================================================
    // Your private member variables go here...
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
    HeaderComponent header;
    BodyComponent body;
    int bpm = 120;
    int currentStepIndex = 0;
    const int stepsTotal = 8;
    bool isPlaying = false;
    
};
