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
class SwitchComponent  : public juce::Button
{
public:
    SwitchComponent(juce::String&);
    ~SwitchComponent() override;

    void paintButton(juce::Graphics&, bool, bool) override;

    void resized() override;
    float scaled(float val);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SwitchComponent)

        std::unique_ptr<juce::Drawable> pianoIcon;
    float scaleFactor = 1;
};
