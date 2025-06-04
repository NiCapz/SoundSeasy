#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    for (int i = 0; i < 4; i++) 
    {
        auto* track = new TrackComponent();
        tracks.add(track);
        addAndMakeVisible(track);
    }

    setSize(860, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    using namespace juce;
    g.fillAll(Colours::antiquewhite);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();
    int trackHeight = bounds.getHeight() / 4;
    
    for (int i = 0; i < tracks.size(); i++) 
    {
        tracks[i]->setBounds(0, i * trackHeight, bounds.getWidth(), trackHeight);
    }
}
