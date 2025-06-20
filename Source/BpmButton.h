/*
  ==============================================================================

    BpmButton.h
    Created: 18 Jun 2025 3:46:33pm
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class BpmButton  : public juce::Component
{
public:
    BpmButton(bool isPlus);
    ~BpmButton() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BpmButton)
        bool isPlus;
};
