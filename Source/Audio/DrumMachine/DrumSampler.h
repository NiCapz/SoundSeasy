/*
  ==============================================================================

    DrumSampler.h
    Created: 12 May 2025 8:17:02pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "OneShotSamplerTrack.h"

class DrumSampler
{
public:
    DrumSampler();
    ~DrumSampler();
    
    void setSampleRate(float);
    
    void addToBuffer(juce::AudioBuffer<float>&, juce::MidiBuffer&);
    
private:
    float sampleRate = 44100;
    
    std::array<OneShotSamplerTrack, 5> samplerTracks{};
    std::unordered_map<int, int> trackMapping =
    {
        { 60, 0 },
        { 61, 1 },
        { 62, 2 },
        { 63, 3 },
        { 64, 4 }
    };
    
    struct BinaryDataFile
    {
        const char* data;
        const int size;
    };
    
    std::array<BinaryDataFile, 5> sampleFiles =
    {{
        { BinaryData::Kick_wav, BinaryData::Kick_wavSize },
        { BinaryData::Snare_wav, BinaryData::Snare_wavSize },
        { BinaryData::HiHat_wav, BinaryData::HiHat_wavSize },
        { BinaryData::OpenHat_wav, BinaryData::OpenHat_wavSize },
        { BinaryData::Crash_wav, BinaryData::Crash_wavSize }
    }};
};
