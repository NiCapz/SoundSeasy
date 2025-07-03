/*
  ==============================================================================

    BpmButton.h
    Created: 18 Jun 2025 3:46:33pm
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class BpmButton  : public juce::Button
{
public:
    BpmButton(juce::String& name, bool isPlus);
    ~BpmButton() override;

    void resized() override;

protected:
    void paintButton(juce::Graphics&, bool, bool) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BpmButton)
        bool isPlus;
    std::unique_ptr<juce::Drawable> plusIcon;
    std::unique_ptr<juce::Drawable> minusIcon;
};
