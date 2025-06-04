#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(header);
    addAndMakeVisible(body);
    setSize(1600/2, 720/2);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    using namespace juce;
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    auto headerHeight = area.getHeight() * 0.2;
    auto bodyheight = area.getHeight() * 0.8;
    
    header.setBounds(area.removeFromTop(headerHeight));
    body.setBounds(area.removeFromBottom(bodyheight));
}
