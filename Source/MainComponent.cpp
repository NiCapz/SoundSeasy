#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(header);
    addAndMakeVisible(body);
    setSize(1600/2, 720/2);

    header.setTempoLabelText(bpm);
    header.bpmLabel.addListener(this);

    header.setTempoIncrementCallback([&]() {
        bpm += 1;
        header.setTempoLabelText(bpm);
        bpmChanged();
    });

    header.setTempoDecrementCallback([&]() {
        bpm -= 1;
        header.setTempoLabelText(bpm);
        bpmChanged();
    });

    header.setPlayPauseCallback([&](bool buttonPlaying) {
        isPlaying = buttonPlaying;
        if (buttonPlaying) {
            startTimer((60.0 / bpm) * 1000);
        }
        else
        {
            stopTimer();
        }
    });

    header.setRewindCallback([&]() {
        currentStepIndex = 0;
        body.updateStepIndexes(currentStepIndex);
    });
}

MainComponent::~MainComponent()
{
}

void MainComponent::bpmChanged() {
    repaint();
    if (isPlaying) {
        stopTimer();
        startTimer((60.0 / bpm) * 1000);
    }
}

void MainComponent::textEditorTextChanged(juce::TextEditor& editor) {
    juce::String value = editor.getText();
    int intValue = value.getIntValue();
    bpm = intValue;
    bpmChanged();
}

void MainComponent::paint (juce::Graphics& g)
{
}

void MainComponent::timerCallback() {
    currentStepIndex++;
    currentStepIndex %= stepsTotal;
    body.updateStepIndexes(currentStepIndex);
    repaint();
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    auto headerHeight = area.getHeight() * 0.2;
    auto bodyheight = area.getHeight() * 0.75;
    
    header.setBounds(area.removeFromTop(headerHeight));
    body.setBounds(area.removeFromTop(bodyheight));
}