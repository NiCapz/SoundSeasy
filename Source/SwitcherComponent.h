/*
  ==============================================================================

    SwitcherComponent.h
    Created: 3 Jul 2025 2:59:29pm
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SwitcherComponent  : public juce::ToggleButton
{
public:
    SwitcherComponent();
    ~SwitcherComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SwitcherComponent)
};
