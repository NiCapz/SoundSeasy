/*
  ==============================================================================

    DrumSampler.cpp
    Created: 12 May 2025 8:17:07pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#include "DrumSampler.h"

DrumSampler::DrumSampler()
{
    using namespace juce;
    
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    for(int i = 0; i < 5; i++)
    {
        auto reader = std::unique_ptr<AudioFormatReader>(formatManager
            .createReaderFor(std::make_unique<MemoryInputStream>(sampleFiles[i].data,
                                                                 sampleFiles[i].size,
                                                                 false)));
        
        const int sampleSize = sampleFiles[i].size / (24 / 8);
        
        std::vector<int> fileData(sampleSize);
        int* const p = { &fileData[0] };
        
        bool readSuccessful = reader->read(&p, 1, 0, sampleSize, false);
        
        std::vector<float> sampleData(sampleSize);
        
        if(readSuccessful)
        {
            for(int sample = 0; sample < sampleSize; sample++)
                sampleData[sample] = (float) fileData[sample] / (1<<31);
            
            samplerTracks[i].setSample(sampleData, 48000);
        }
    }
}

DrumSampler::~DrumSampler()
{
    
}

void DrumSampler::setSampleRate(double val)
{
    sampleRate = val;
    
    for(auto& samplerTrack : samplerTracks)
        samplerTrack.setSampleRate(val);
}

void DrumSampler::addToBuffer(juce::AudioBuffer<float>& buffer, const juce::MidiBuffer& midiBuffer)
{
    using namespace juce;
    std::queue<MidiMessage> noteEvents{};
    
    for(MidiMessageMetadata m : midiBuffer)
        if(m.getMessage().isNoteOn() && m.getMessage().getChannel() == midiChannel)
            noteEvents.push(m.getMessage());
    
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();
    
    juce::AudioBuffer<float> processBuffer(1, numSamples);
    processBuffer.clear();
    float* processChannelData = processBuffer.getWritePointer(0);
    

    for(int sample = 0; sample < numSamples; sample++)
    {
        while(!(noteEvents.empty()))
        {
            MidiMessage event = noteEvents.front();
            if(sample < event.getTimeStamp())
            {
                break;
            }
            else if(event.getChannel())
            {
                auto trackNumberIt = trackMapping.find(event.getNoteNumber());
                
                if(trackNumberIt != trackMapping.end())
                {
                    int trackNumber = trackNumberIt->second;
                    samplerTracks[trackNumber].trigger();
                }
                noteEvents.pop();
            }
        }
        
        for(auto& track : samplerTracks)
        {
            processChannelData[sample] += 0.5 * track.getNextValue();
        }
    }
    
    
    for(int channel = 0; channel < numChannels; channel++)
    {
        float* channelData = buffer.getWritePointer(channel);
        
        for(int sample = 0; sample < numSamples; sample++)
            channelData[sample] += outputGain * processChannelData[sample];
    }
}
