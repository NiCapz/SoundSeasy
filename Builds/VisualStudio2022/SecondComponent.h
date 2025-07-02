#pragma once

#include <JuceHeader.h>
#include "HeaderComponent.h"
#include "BodyComponent.h"

class SecondComponent : public juce::Component, juce::Timer, juce::TextEditor::Listener
{

public:
	SecondComponent();
	~SecondComponent() override;


	void paint(juce::Graphics& g) override;
	void resized() override;

	void timerCallback() override;

	void textEditorTextChanged(juce::TextEditor& editor) override;

	void bpmChanged();

private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SecondComponent)
		HeaderComponent header;
		BodyComponent body;
		int bpm = 120; // Default BPM
		int currentStepIndex = 0; // Current step index
		const int stepsTotal = 8; // Total number of steps
		bool isPlaying = false; // Playback state
};