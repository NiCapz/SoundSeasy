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
    
    std::array<BinaryDataFile, 9> sampleFiles =
    {{
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
