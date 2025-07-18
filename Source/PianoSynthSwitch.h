/*
  ==============================================================================

    PianoSynthSwitch.h
    Created: 18 Jul 2025 12:36:43pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PianoSynthSwitch : public juce::Button
{
public:
    PianoSynthSwitch(const juce::String& buttonName) : Button(buttonName)
    {
        onClick = [&] ()
        {
            switch(state)
            {
                case PIANO:
                    state = SYNTH;
                    callback(false);
                    break;
                case SYNTH:
                    state = PIANO;
                    callback(true);
                    break;
            }
        };
    }
    ~PianoSynthSwitch() {}
    
    void resized() {}

    void paintButton(juce::Graphics& g, bool isDown, bool isHighlighted)
    {
        auto area = getLocalBounds();
        float localAspectRatio = (float) area.getWidth() / area.getHeight();
        juce::Rectangle<float> backgroundArea;
        if(localAspectRatio > aspectRatio)
            backgroundArea.setBounds(0, 0, area.getHeight() * aspectRatio, area.getHeight());
        else
            backgroundArea.setBounds(0, 0, area.getWidth(), area.getWidth() / aspectRatio);
        
        g.setColour(backgroundColour);
        g.fillRoundedRectangle(backgroundArea, 20);
        
        juce::Rectangle<float> highlightArea{0, 0, backgroundArea.getWidth() / 2, backgroundArea.getHeight()};
        
        if(state == SYNTH)
            highlightArea.setX(backgroundArea.getWidth() / 2);
        
        g.setColour(highlightColour);
        g.fillRoundedRectangle(highlightArea, 20);
        
        g.setFont(backgroundArea.getHeight() / 2);
        
        if(state == PIANO)
            g.setColour(darkTextColour);
        else
            g.setColour(lightTextColour);
        
        g.drawText("Piano", highlightArea.withX(0), juce::Justification::centred);
        
        
        if(state == SYNTH)
            g.setColour(darkTextColour);
        else
            g.setColour(lightTextColour);
        
        g.drawText("Synth", highlightArea.withX(backgroundArea.getWidth() / 2), juce::Justification::centred);
        
    }

    void setCallback(std::function<void(bool)> c) { callback = c; }
    
private:
    std::function<void(bool)> callback;
    enum SwitchState
    {
        PIANO,
        SYNTH
    };
    
    SwitchState state = PIANO;
    
    const float aspectRatio = 166.0 / 32.0;
    
    const juce::Colour backgroundColour{0xFF393939};
    const juce::Colour highlightColour{0xFFB9B9B9};
    const juce::Colour darkTextColour{0xFF000000};
    const juce::Colour lightTextColour{0xFFD0D0D0};
};

