#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(header);
    addAndMakeVisible(body);
    setSize(1600/2, 720/2);

    header.setTempoLabelText(bpm);

    header.setTempoIncrementCallback([&]() {
        bpm += 1;
        header.setTempoLabelText(bpm);
    });

    header.setTempoDecrementCallback([&]() {
        bpm -= 1;
        header.setTempoLabelText(bpm);
    });

    header.setPlayPauseCallback([&](bool buttonPlaying) {
        isPlaying = buttonPlaying;
    });
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    using namespace juce;
    
    auto area = getLocalBounds();
    juce::String isPlayingString;
    if (isPlaying) {
        isPlayingString = "playing...";
    }
    else {
        isPlayingString = "paused";
    }
}

void MainComponent::timerCallback() {
    currentStepindex++;
    currentStepindex %= stepsTotal;
}

void MainComponent::startPlayback() {
    startTimer(60 / bpm * 1000);
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    auto headerHeight = area.getHeight() * 0.2;
    auto bodyheight = area.getHeight() * 0.75;
    
    header.setBounds(area.removeFromTop(headerHeight));
    body.setBounds(area.removeFromTop(bodyheight));
}
