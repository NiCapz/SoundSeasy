/*
  ==============================================================================

    RewindComponent.h
    Created: 18 Jun 2025 2:31:16pm
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class RewindComponent  : public juce::Component
{
public:
    RewindComponent();
    ~RewindComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RewindComponent)
};
