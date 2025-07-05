/*
  ==============================================================================

    Shadower.h
    Created: 5 Jul 2025 6:47:55pm
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Shadower  : public juce::Component
{
public:
    Shadower();
    ~Shadower() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void drawShadowImage(juce::Graphics&, juce::Rectangle<int>, juce::Path, juce::Image);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Shadower)
};
