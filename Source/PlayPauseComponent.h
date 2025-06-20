/*
  ==============================================================================

    PlayPauseComponent.h
    Created: 4 Jun 2025 11:28:58am
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlayPauseComponent  : public juce::Component
{
public:
    PlayPauseComponent();
    ~PlayPauseComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayPauseComponent)

};
