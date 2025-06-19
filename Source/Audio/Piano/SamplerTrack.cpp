/*
  ==============================================================================

    SamplerTrack.cpp
    Created: 12 May 2025 8:17:34pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#include "SamplerTrack.h"
#include "../Utils.h"

SamplerTrack::SamplerTrack() : ampEnvelope(&envAttack, &envDecay, &envSustain, &envRelease)
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

void SamplerTrack::setGate(bool val)
{
    if(gateValue != val)
    {
        noteLengthCounter = 0;
        
        if(val)
            ampEnvelope.reset();
    }
    
    if(val)
    {
        playIndex = padding;
    }
    
    gateValue = val;
}

void SamplerTrack::setNoteNumber(int val)
{
    noteNumber = val;
    pitch = 440 * pow(2.0, (float) (noteNumber - 69) / 12);
    calculateIncrement();
}

void SamplerTrack::setSample(const float* sample, int numSamples, float sampleRate, float referencePitch)
{
    sampleSize = numSamples;
    sampleData = sample;
    
    sampleSampleRate = sampleRate;
    this->referencePitch = referencePitch;
    calculateIncrement();
}

float SamplerTrack::getNextValue()
{
    float val = 0;
    ampEnvelope.updateTarget();
    
    std::array<float, 4> interpolationSamples{0};
    
    if(playIndex < sampleSize)
    {
        for(int i = 0; i < 4; i++)
            interpolationSamples[i] = sampleData[(int) playIndex + i - 2];
        
        val = Utils::cubicLagrangeInterpolation(interpolationSamples, playIndex - (int) playIndex);
        
        envelopeValue = ampEnvelope.getNextValue(gateValue);
        val *= envelopeValue;
        
        playIndex += playIncrement;
    }
    return val;
}

void SamplerTrack::processBlock(float* buffer, int startSample, int numSamples)
{
    if(gateValue || envelopeValue > 0.00001)
        for(int sample = startSample; sample < startSample + numSamples; sample++)
            buffer[sample] += getNextValue();
    
    noteLengthCounter += numSamples;
}

void SamplerTrack::calculateIncrement()
{
    playIncrement = (sampleSampleRate / projectSampleRate) * (pitch / referencePitch);
}

int SamplerTrack::getNoteNumber()
{
    return noteNumber;
}

bool SamplerTrack::getGate()
{
    return gateValue;
}

float SamplerTrack::getAmplitude()
{
    return envelopeValue;
}
    
long SamplerTrack::getNoteLength()
{
    return noteLengthCounter;
}

