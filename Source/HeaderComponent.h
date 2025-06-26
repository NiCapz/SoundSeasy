/*
  ==============================================================================

    HeaderComponent.h
    Created: 4 Jun 2025 11:28:32am
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PlayPauseComponent.h"
#include "RewindComponent.h"
#include "BpmButton.h"

//==============================================================================
/*
*/
class HeaderComponent  : public juce::Component
{
public:
    HeaderComponent();
    ~HeaderComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setTempoIncrementCallback(std::function<void()>);
    void setTempoDecrementCallback(std::function<void()>);

    void setPlayPauseCallback(std::function<void(bool)>);

    void setTempoLabelText(int);


    juce::String ppComponentName = "pp";
    PlayPauseComponent pp{ ppComponentName };
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
    RewindComponent rw;
    juce::TextEditor bpmLabel;
    juce::String plusName = "plus";
    juce::String minusName = "minus";
    BpmButton plus { plusName, true};
    BpmButton minus { minusName, false};
};
