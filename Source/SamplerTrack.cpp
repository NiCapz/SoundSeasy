/*
  ==============================================================================

    SamplerTrack.cpp
    Created: 12 May 2025 8:17:34pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#include "SamplerTrack.h"
#include "Utils.h"

SamplerTrack::SamplerTrack()
{
    
}

SamplerTrack::~SamplerTrack()
{
    
}

void SamplerTrack::setSampleRate(float val)
{
    projectSampleRate = val;
    calculateIncrement();
}

void SamplerTrack::setSample(const std::vector<float>& sample, float sampleRate)
{
    sampleSize = sample.size();
    sampleData = std::vector<float>(sampleSize + 2 * padding);
    
    for(int i = 0; i < sampleSize; i++)
        sampleData[i + padding] = sample[i];
    
    playIndex = sampleData.size();
    sampleSampleRate = sampleRate;
    calculateIncrement();
}

void SamplerTrack::setReferencePitch(float val)
{
    referencePitch = val;
    calculateIncrement();
}

void SamplerTrack::setPitch(float val)
{
    pitch = val;
    calculateIncrement();
}

float SamplerTrack::getNextValue()
{
    float val = 0;
    
    std::array<float, 4> interpolationSamples{0};
    
    if(playIndex < sampleSize)
    {
        for(int i = 0; i < 4; i++)
            interpolationSamples[i] = sampleData[(int) playIndex + i - 2];
        
        
        val = Utils::cubicLagrangeInterpolation(interpolationSamples, playIndex - (int) playIndex);
        
        playIndex += playIncrement;
    }
    
    return val;
}

void SamplerTrack::trigger()
{
    playIndex = padding;
}

void SamplerTrack::calculateIncrement()
{
    playIncrement = (sampleSampleRate / projectSampleRate) * (pitch / referencePitch);
}

