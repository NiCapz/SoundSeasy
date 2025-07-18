/*
  ==============================================================================

    PianoSampler.h
    Created: 16 Jun 2025 11:33:22pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../MidiInstrument.h"
#include "SamplerTrack.h"

class PianoSampler : public MidiInstrument
{
public:
    PianoSampler();
    ~PianoSampler();
    
    void setSampleRate(double) override;
    
    void addToBuffer(juce::AudioBuffer<float>&, const juce::MidiBuffer&) override;
    
private:
    struct BinaryDataFile
    {
        const char* data;
        const int size;
        const float pitch;
    };
    
    std::array<BinaryDataFile, 17> sampleFiles =
    {{
        { BinaryData::_05Mezzo_flac, BinaryData::_05Mezzo_flacSize,  34.64 },
        { BinaryData::_08Mezzo_flac, BinaryData::_08Mezzo_flacSize,  41.20 },
        { BinaryData::_11Mezzo_flac, BinaryData::_11Mezzo_flacSize,  49.00 },
        { BinaryData::_14Mezzo_flac, BinaryData::_14Mezzo_flacSize,  58.27 },
        { BinaryData::_17Mezzo_flac, BinaryData::_17Mezzo_flacSize,  69.30 },
        { BinaryData::_20Mezzo_flac, BinaryData::_20Mezzo_flacSize,  82.41 },
        { BinaryData::_23Mezzo_flac, BinaryData::_23Mezzo_flacSize,  98.00 },
        { BinaryData::_26Mezzo_flac, BinaryData::_26Mezzo_flacSize, 116.54 },
        { BinaryData::_29Mezzo_flac, BinaryData::_29Mezzo_flacSize, 138.58 },
        { BinaryData::_32Mezzo_flac, BinaryData::_32Mezzo_flacSize, 164.81 },
        { BinaryData::_35Mezzo_flac, BinaryData::_35Mezzo_flacSize, 196.00 },
        { BinaryData::_38Mezzo_flac, BinaryData::_38Mezzo_flacSize, 233.08 },
        { BinaryData::_41Mezzo_flac, BinaryData::_41Mezzo_flacSize, 277.18 },
        { BinaryData::_44Mezzo_flac, BinaryData::_44Mezzo_flacSize, 329.63 },
        { BinaryData::_47Mezzo_flac, BinaryData::_47Mezzo_flacSize, 392.00 },
        { BinaryData::_50Mezzo_flac, BinaryData::_50Mezzo_flacSize, 466.16 },
        { BinaryData::_53Mezzo_flac, BinaryData::_53Mezzo_flacSize, 554.37 }
    }};
    
    struct PianoSample
    {
        const std::vector<float> data;
        const float sampleRate;
        const float pitch;
    };
    
    std::vector<PianoSample> pianoSamples;
    
    static constexpr int numTracks = 8;
    std::array<SamplerTrack, numTracks> samplerTracks{};
};
