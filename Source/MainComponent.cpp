#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    
    addAndMakeVisible(&stepSequencer);
    addAndMakeVisible(&playButton);
    
    std::function<void(bool)> playButtonCallback = [&] (bool state)
    {
        if(state)
        {
            this->startTimerHz(6.0);
            stepSequencer.reset();
        }
        else
        {
            this->stopTimer();
        }
    };
    
    playButtonListener = new PlayButton::PlayButtonListener(playButtonCallback);
    
    playButton.addListener(playButtonListener);
}

MainComponent::~MainComponent()
{
    delete playButtonListener;
    // This shuts down the audio device and clears the audio source.
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colour::fromHSV(0.0, 0.0, 0.4, 1.0));
    
    const auto localBounds = getLocalBounds();
    AffineTransform r = AffineTransform::translation(-localBounds.getWidth() / 2, -localBounds.getHeight() / 2);
    r = r.rotated(M_PI / 2)
         .translated(localBounds.getWidth() / 2, localBounds.getHeight() / 2);
    
    if(localBounds.getWidth() < localBounds.getHeight())
        g.addTransform(r);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    const auto localBounds = getLocalBounds();
    const auto width = localBounds.getWidth();
    const auto height = localBounds.getHeight();
    
    const int sX = 0.1 * width;
    const int sY = 0.25 * height;
    const int sW = width - 2 * sX;
    const int sH = height - 2 * sY;
    
    if(width > height)
    {
        stepSequencer.setBounds(sX, sY, sW, sH);
        playButton.setBounds(sX, 0.8 * height, 40, 40);
    }
    else
    {
        stepSequencer.setBounds(sY, sX, sH, sW);
        playButton.setBounds(0.8 * height, sX, 40, 40);
    }
}

void MainComponent::timerCallback()
{
    stepSequencer.nextStep();
}
