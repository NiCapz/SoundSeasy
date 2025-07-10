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
#include "SwitchComponent.h"

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

    void setRewindCallback(std::function <void()>);

    void setSwitchCallback(std::function<void()>);

    void setTempoLabelText(int);

    void setupBpmLabel(juce::TextEditor&);

    // modify this to change the state from drumsampler to cord helper
    bool showDrumSampler = true;

    juce::TextEditor bpmLabel;

    float scaled (float val);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)

        juce::String swComponentName = "sw";
    SwitchComponent sw { swComponentName } ;

    juce::String rwComponentName = "pp";
    RewindComponent rw { rwComponentName };

    juce::String ppComponentName = "pp";
    PlayPauseComponent pp { ppComponentName };
    
    juce::String plusName = "plus";
    BpmButton plus { plusName, true};
    
    juce::String minusName = "minus";
    BpmButton minus { minusName, false};

    float scaleFactor;

    bool shadowsRendered = false;
};
