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
class RewindComponent  : public juce::Button
{
public:
    RewindComponent(juce::String&);
    ~RewindComponent() override;

    void paintButton(juce::Graphics&, bool, bool) override;

    void resized() override;

    float scaled(float val);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RewindComponent)

        std::unique_ptr<juce::Drawable> rewindIcon;
    float scaleFactor;
};
