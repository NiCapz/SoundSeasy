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
class PlayPauseComponent  : public juce::Button
{
public:
    PlayPauseComponent(juce::String&);
    ~PlayPauseComponent() override;

    //void paint (juce::Graphics&) override;
    void resized() override;

    void paintButton(juce::Graphics&, bool, bool) override;


    bool getState();
    void toggleState();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayPauseComponent)
        bool isPlaying = false;

};
