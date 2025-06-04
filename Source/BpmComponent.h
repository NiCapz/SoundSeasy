/*
  ==============================================================================

    BpmComponent.h
    Created: 4 Jun 2025 11:29:10am
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class BpmComponent  : public juce::Component
{
public:
    BpmComponent();
    ~BpmComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BpmComponent)
};
