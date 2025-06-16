#pragma once

#include <JuceHeader.h>
#include "StepSequencer.h"
#include "PlayButton.h"

using namespace juce;
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, juce::Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;

private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
    
    int tempoBPM = 120;
    
    StepSequencer stepSequencer{4, 16};
    PlayButton playButton{"PlayButton"};
    PlayButton::Listener* playButtonListener;
};
