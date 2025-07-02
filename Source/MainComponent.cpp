#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : reverb(new std::atomic<float> {0.3},
                                        new std::atomic<float> {0.5},
                                        new std::atomic<float> {2.7},
                                        new std::atomic<float> {0.3},
                                        new std::atomic<float> {0.5})
{
    setSize (600, 400);
    
    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
    
    startTime = Time::getMillisecondCounterHiRes() * 0.001;
    midiManager.setStartTimeS(startTime);
    
    drumSampler.setMidiChannel(1);
    synth.setMidiChannel(2);
    piano.setMidiChannel(3);

    
    startTimerHz(1);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    drumSampler.setSampleRate(sampleRate);
    piano.setSampleRate(sampleRate);
    synth.setSampleRate(sampleRate);
    midiManager.reset(sampleRate);
    reverb.setSamplerate(sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
    
    const int numSamples = bufferToFill.numSamples;
    const int numChannels = bufferToFill.buffer->getNumChannels();
    
    auto* const buffer = bufferToFill.buffer;
    
    MidiBuffer midiBuffer{};
    midiManager.removeNextBlockOfMessages(midiBuffer, bufferToFill.numSamples);
    
    
    synth.addToBuffer(*buffer, midiBuffer);
    piano.addToBuffer(*buffer, midiBuffer);
    drumSampler.addToBuffer(*buffer, midiBuffer);
    
    AudioBuffer<float> reverbBuffer{};
    reverbBuffer.makeCopyOf(*buffer);
    
    reverb.processBlock(reverbBuffer);
    
    for(int channel = 0; channel < numChannels; channel++)
        buffer->addFrom(channel, 0, reverbBuffer, channel, 0, numSamples, 1.0);
    
    
}

void MainComponent::releaseResources()
{
    
}

void MainComponent::timerCallback()
{
    static int counter = 0;
    
    const double noteLengthS = 0.3;
    
    MidiMessage message = MidiMessage::noteOn (1 + counter, 60, (juce::uint8) 100);
    message.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
    
    MidiMessage messageOff = MidiMessage::noteOff (1 + counter, 60, (juce::uint8) 100);
    messageOff.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001 + noteLengthS);
    
    midiManager.addMessageToQueue(message);
    midiManager.addMessageToQueue(messageOff);
    
    counter++;
    counter %= 3;
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::FontOptions (50.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("HELLO WORLD AHHHH!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
