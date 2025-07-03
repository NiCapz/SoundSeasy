/*
  ==============================================================================

    InstrumentSelectorComponent.h
    Created: 4 Jun 2025 11:29:51am
    Author:  Niko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class InstrumentSelectorComponent  : public juce::Component
{
public:
    InstrumentSelectorComponent();
    ~InstrumentSelectorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setName(juce::String);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InstrumentSelectorComponent)
    
    juce::String name;

    std::unique_ptr<juce::Drawable> icon;
};
