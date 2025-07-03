/*
  ==============================================================================

    SwitchComponent.h
    Created: 4 Jun 2025 11:29:24am
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SwitchComponent  : public juce::Component
{
public:
    SwitchComponent();
    ~SwitchComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SwitchComponent)

        std::unique_ptr<juce::Drawable> pianoIcon;
};
