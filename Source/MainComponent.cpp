#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(header);
    addAndMakeVisible(body);
    //setSize(1600, 720);
    setSize(2400, 1080);

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

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
            [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(0, 2);
    }

    startTime = Time::getMillisecondCounterHiRes() * 0.001;
    midiManager.setStartTimeS(startTime);

    drumSampler.setMidiChannel(1);
    synth.setMidiChannel(2);
    piano.setMidiChannel(3);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::bpmChanged() {
    repaint();
    bpmJustChanged = true;
    if (bpm < 50) bpm = 50;
    header.setTempoLabelText(bpm);
    
    if (bpm < 70) {
        stopTimer();
        startTimer((60.0 / bpm) * 1000);
    }
    
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    drumSampler.setSampleRate(sampleRate);
    piano.setSampleRate(sampleRate);
    synth.setSampleRate(sampleRate);
    midiManager.reset(sampleRate);
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();

    MidiBuffer midiBuffer{};
    midiManager.removeNextBlockOfMessages(midiBuffer, bufferToFill.numSamples);

    drumSampler.addToBuffer(*(bufferToFill.buffer), midiBuffer);
    synth.addToBuffer(*(bufferToFill.buffer), midiBuffer);
    piano.addToBuffer(*(bufferToFill.buffer), midiBuffer);
}

void MainComponent::releaseResources()
{

}

void MainComponent::textEditorReturnKeyPressed(juce::TextEditor& editor) {
    juce::String value = editor.getText();
    int intValue = value.getIntValue();

    bpm = intValue;
    bpmChanged();
}

void MainComponent::textEditorFocusLost(juce::TextEditor& editor) {
    juce::String value = editor.getText();
    int intValue = value.getIntValue();

    bpm = intValue;
    bpmChanged();
}

void MainComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colour(0xff585858));
    g.fillAll();

    static juce::Image shadowImage;

    static bool shadowsRendered = false;

    if (!shadowsRendered)
    {
        shadowImage = juce::Image(juce::Image::PixelFormat::ARGB,
            1 * header.getBounds().getWidth(),
            1 * (header.getBounds().getHeight() + 30),
            true);
        juce::Graphics shadowGraphics{ shadowImage };
        juce::DropShadow headerShadow(juce::Colours::black.withAlpha(.25f), 100, { 0, 10 });
        juce::Path headerPath;
        headerPath.addRectangle(header.getBounds());
        headerShadow.drawForPath(shadowGraphics, headerPath);
        shadowsRendered = true;
    }

    g.drawImage(shadowImage, header.getBounds().expanded(0, 30).toFloat());
}

void MainComponent::timerCallback() {
    body.updateStepIndexes(currentStepIndex);
    repaint();


    for (int i = 0; i < 5; i++) {
        if (body.tracks[i]->isCurrentStepActive()) {
            MidiMessage message = MidiMessage::noteOn(1, 60 + 4- i, (juce::uint8)100);
            message.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
            midiManager.addMessageToQueue(message);
        }
    }

    currentStepIndex++;
    currentStepIndex %= stepsTotal;
    if (bpmJustChanged && bpm > 0)
    {
        stopTimer();
        startTimer((60.0 / bpm) * 1000);
        bpmJustChanged = false;
    }
}

void MainComponent::resized()
{
    auto area = getLocalBounds();


    auto headerHeight = area.getHeight() * 0.15;
    auto bodyheight = area.getHeight() * 0.85;
    
    header.setBounds(area.removeFromTop(headerHeight));
    body.setBounds(area.removeFromTop(bodyheight));

}