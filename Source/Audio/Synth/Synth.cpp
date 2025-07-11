/*
  ==============================================================================

    Synth.cpp
    Created: 5 May 2025 6:14:17pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#include "Synth.h"

Synth::Synth()
{
    for(int i = 0; i < numVoices; i++)
        voices.emplace_back();
}

Synth::~Synth()
{
    
}

void Synth::setSampleRate(double val)
{
    for(auto& voice : voices)
        voice.setSampleRate(val);
}

void Synth::addToBuffer(juce::AudioBuffer<float>& buffer, const juce::MidiBuffer& midiBuffer)
{
    using namespace juce;
    std::queue<MidiMessage> noteEvents{};
    
    for(MidiMessageMetadata m : midiBuffer)
        if(m.getMessage().isNoteOnOrOff() && m.getMessage().getChannel() == midiChannel)
            noteEvents.push(m.getMessage());
    
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();
    
    std::array<std::queue<MidiMessage>, numVoices> voiceNoteEvents{};
    
    std::array<int, numVoices> voiceAges{};
    std::array<bool, numVoices> voiceGateValues{};
    std::array<int, numVoices> voiceNoteNumbers{};
    
    for(int voice = 0; voice < numVoices; voice++)
    {
        voiceAges[voice] = voices[voice].getNoteLength();
        voiceGateValues[voice] = voices[voice].getGate();
        voiceNoteNumbers[voice] = voices[voice].getNoteNumber();
    }
    
    int lastTimestamp = 0;
    
    while(!(noteEvents.empty()))
    {
        MidiMessage noteEvent = noteEvents.front();
        int timeStamp = noteEvent.getTimeStamp();
        int noteNumber = noteEvent.getNoteNumber();
        
        for(int voice = 0; voice < numVoices; voice++)
            voiceAges[voice] += timeStamp - lastTimestamp;
            
        if(noteEvent.isNoteOn())
        {
            int oldestVoiceIndex = -1;
            int oldestAge = -1;
            
            int oldestFreeVoiceIndex = -1;
            int oldestFreeAge = -1;
            
            for(int voice = 0; voice < numVoices; voice++)
            {
                if(voiceGateValues[voice])
                {
                    if(voiceAges[voice] > oldestAge)
                    {
                        oldestAge = voiceAges[voice];
                        oldestVoiceIndex = voice;
                    }
                }
                else
                {
                    if(voiceAges[voice] > oldestFreeAge)
                    {
                        oldestFreeAge = voiceAges[voice];
                        oldestFreeVoiceIndex = voice;
                    }
                }
            }
            
            if(oldestFreeVoiceIndex != -1)
            {
                voiceNoteEvents[oldestFreeVoiceIndex].push(noteEvent);
                voiceGateValues[oldestFreeVoiceIndex] = true;
                voiceNoteNumbers[oldestFreeVoiceIndex] = noteNumber;
            }
            else
            {
                voiceNoteEvents[oldestVoiceIndex].push(noteEvent);
                voiceGateValues[oldestVoiceIndex] = true;
                voiceNoteNumbers[oldestVoiceIndex] = noteNumber;
            }
        }
        else if(noteEvent.isNoteOff())
        {
            for(int voice = 0; voice < numVoices; voice++)
            {
                if(voiceNoteNumbers[voice] == noteNumber && voiceGateValues[voice] == true)
                {
                    voiceNoteEvents[voice].push(noteEvent);
                    voiceGateValues[voice] = false;
                }
            }
        }
        
        lastTimestamp = timeStamp;
        noteEvents.pop();
    }
    
    juce::AudioBuffer<float> processBuffer(1, numSamples);
    processBuffer.clear();
    float* processChannelData = processBuffer.getWritePointer(0);
    
    for(int voice = 0; voice < numVoices; voice++)
    {
        if(voiceNoteEvents[voice].empty())
        {
            if(voices[voice].getGate() || voices[voice].getAmplitude() > 0.00001)
                voices[voice].processBlock(processChannelData, 0, numSamples);
        }
        else
        {
            int startSample = 0;
            
            while(!(voiceNoteEvents[voice].empty()))
            {
                MidiMessage noteEvent = voiceNoteEvents[voice].front();
                int timeStamp = (int) noteEvent.getTimeStamp();
                
                voices[voice].processBlock(processChannelData, startSample, timeStamp - startSample);
                
                if(voices[voice].getGate() && noteEvent.isNoteOn())
                    voices[voice].resetEnvelope();
                
                voices[voice].setGate(noteEvent.isNoteOn());
                voices[voice].setNoteNumber(noteEvent.getNoteNumber());
                
                startSample = timeStamp;
                voiceNoteEvents[voice].pop();
            }
            
            voices[voice].processBlock(processChannelData, startSample, numSamples - startSample);
        }
    }
    
    for(int channel = 0; channel < numChannels; channel++)
    {
        float* channelData = buffer.getWritePointer(channel);
        for(int sample = 0; sample < numSamples; sample++)
            channelData[sample] += outputGain * processChannelData[sample];
    }
}

int Synth::findIndexOfFreeVoice()
{
    int freeVoiceIndex = -1;
    
    //find a voice in release state with low amplitude
    float lowestAmplitude = 1;
    for(int i = 0; i < numVoices; i++)
    {
        bool isRelease = !(voices[i].getGate());
        float amplitude = voices[i].getAmplitude();
        
        if(isRelease && (amplitude < lowestAmplitude))
        {
            lowestAmplitude = voices[i].getAmplitude();
            freeVoiceIndex = i;
        }
    }
    
    if(freeVoiceIndex != -1)
    {
        return freeVoiceIndex;
    }
    else
    {
        //find a voice that isnt actively pressed
        for(int i = 0; i < numVoices; i++)
        {
            if(!(voices[i].getGate()))
            {
                freeVoiceIndex = i;
                break;
            }
        }
    }
    
    if(freeVoiceIndex != -1)
    {
        return freeVoiceIndex;
    }
    else
    {
        //find oldest voice
        int oldestVoiceIndex = -1;
        long oldestVoiceValue = 0;
        
        for(int i = 0; i < numVoices; i++)
        {
            if(voices[i].getNoteLength() > oldestVoiceValue)
            {
                oldestVoiceIndex = i;
                oldestVoiceValue = voices[i].getNoteLength();
            }
        }
        
        return oldestVoiceIndex;
    }
}
