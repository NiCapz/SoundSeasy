/*
  ==============================================================================

    HeaderComponent.h
    Created: 4 Jun 2025 11:28:32am
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HeaderComponent)
};
