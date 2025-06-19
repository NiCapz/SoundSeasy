/*
  ==============================================================================

    PianoSampler.cpp
    Created: 16 Jun 2025 11:33:30pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#include "PianoSampler.h"

PianoSampler::PianoSampler()
{
    using namespace juce;
    
    for(auto& file : sampleFiles)
    {
        
        AudioFormatManager formatManager;
        formatManager.registerBasicFormats();
        
        auto reader = std::unique_ptr<AudioFormatReader>(formatManager
                                                         .createReaderFor(std::make_unique<MemoryInputStream>(file.data,
                                                                                                              file.size,
                                                                                                              false)));
        const int sampleSize = file.size / (24 / 8);
        
        std::vector<int> fileData(sampleSize);
        int* const p = { &fileData[0] };
        
        bool readSuccessful = reader->read(&p, 1, 0, sampleSize, false);
        
        std::vector<float> sampleData(sampleSize);
        
        if(readSuccessful)
        {
            for(int sample = 0; sample < sampleSize; sample++)
                sampleData[sample] = (float) fileData[sample] / (1<<31);
            
            pianoSamples.push_back(PianoSample{sampleData, 44100, file.pitch});
        }
    }
}

PianoSampler::~PianoSampler()
{
    
}

void PianoSampler::setSampleRate(float val)
{
    sampleRate = val;
    
    for(auto& samplerTrack : samplerTracks)
        samplerTrack.setSampleRate(val);
}

void PianoSampler::addToBuffer(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer)
{
    using namespace juce;
    std::queue<MidiMessage> noteEvents{};
    
    for(MidiMessageMetadata m : midiBuffer)
        if(m.getMessage().isNoteOnOrOff())
            noteEvents.push(m.getMessage());
    
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();
    
    std::array<std::queue<MidiMessage>, numTracks> trackNoteEvents{};
    
    std::array<int, numTracks> trackAges{};
    std::array<bool, numTracks> trackGateValues{};
    std::array<int, numTracks> trackNoteNumbers{};
    
    for(int track = 0; track < numTracks; track++)
    {
        trackAges[track] = samplerTracks[track].getNoteLength();
        trackGateValues[track] = samplerTracks[track].getGate();
        trackNoteNumbers[track] = samplerTracks[track].getNoteNumber();
    }
    
    int lastTimestamp = 0;
    
    while(!(noteEvents.empty()))
    {
        MidiMessage noteEvent = noteEvents.front();
        int timeStamp = noteEvent.getTimeStamp();
        int noteNumber = noteEvent.getNoteNumber();
        
        for(int track = 0; track < numTracks; track++)
            trackAges[track] += timeStamp - lastTimestamp;
            
        if(noteEvent.isNoteOn())
        {
            int oldestVoiceIndex = -1;
            int oldestAge = -1;
            
            int oldestFreeVoiceIndex = -1;
            int oldestFreeAge = -1;
            
            for(int track = 0; track < numTracks; track++)
            {
                if(trackGateValues[track])
                {
                    if(trackAges[track] > oldestAge)
                    {
                        oldestAge = trackAges[track];
                        oldestVoiceIndex = track;
                    }
                }
                else
                {
                    if(trackAges[track] > oldestFreeAge)
                    {
                        oldestFreeAge = trackAges[track];
                        oldestFreeVoiceIndex = track;
                    }
                }
            }
            
            if(oldestFreeVoiceIndex != -1)
            {
                trackNoteEvents[oldestFreeVoiceIndex].push(noteEvent);
                trackGateValues[oldestFreeVoiceIndex] = true;
                trackNoteNumbers[oldestFreeVoiceIndex] = noteNumber;
            }
            else
            {
                trackNoteEvents[oldestVoiceIndex].push(noteEvent);
                trackGateValues[oldestVoiceIndex] = true;
                trackNoteNumbers[oldestVoiceIndex] = noteNumber;
            }
        }
        else if(noteEvent.isNoteOff())
        {
            for(int track = 0; track < numTracks; track++)
            {
                if(trackNoteNumbers[track] == noteNumber && trackGateValues[track] == true)
                {
                    trackNoteEvents[track].push(noteEvent);
                    trackGateValues[track] = false;
                }
            }
        }
        
        lastTimestamp = timeStamp;
        noteEvents.pop();
    }
    
    float* channel0Data = buffer.getWritePointer(0);
    
    for(int track = 0; track < numTracks; track++)
    {
        if(trackNoteEvents[track].empty())
        {
            samplerTracks[track].processBlock(channel0Data, 0, numSamples);
        }
        else
        {
            int startSample = 0;
            
            while(!(trackNoteEvents[track].empty()))
            {
                MidiMessage noteEvent = trackNoteEvents[track].front();
                int timeStamp = (int) noteEvent.getTimeStamp();
                
                samplerTracks[track].processBlock(channel0Data, startSample, timeStamp - startSample);
                
                float notePitch = 440 * pow(2.0, (float) (noteEvent.getNoteNumber() - 69) / 12);
                
                if(noteEvent.isNoteOn())
                {
                    int sampleIndex = 0;
                    
                    for(int i = 0; i < 9; i++)
                    {
                        if(pianoSamples[i].pitch > notePitch)
                            break;
                        else
                            sampleIndex = i;
                    }
                    samplerTracks[track].setSample(&(pianoSamples[sampleIndex].data[0]),
                                                   pianoSamples[sampleIndex].data.size(),
                                                   pianoSamples[sampleIndex].sampleRate,
                                                   pianoSamples[sampleIndex].pitch);
                }
                
                samplerTracks[track].setGate(noteEvent.isNoteOn());
                samplerTracks[track].setNoteNumber(noteEvent.getNoteNumber());
                
                startSample = timeStamp;
                trackNoteEvents[track].pop();
                
            }
            
            samplerTracks[track].processBlock(channel0Data, startSample, numSamples - startSample);
        }
    }
    
    for(int channel = 1; channel < numChannels; channel++)
    {
        float* channelData = buffer.getWritePointer(0);
        for(int sample = 0; sample < numSamples; sample++)
            channelData[sample] = channel0Data[sample];
    }
}
