/*
  ==============================================================================

    OneShotSamplerTrack.h
    Created: 12 May 2025 8:17:21pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <vector>

class OneShotSamplerTrack
{
public:
    OneShotSamplerTrack();
    ~OneShotSamplerTrack();
    
    void setSampleRate(float);
    void setSample(const std::vector<float>& sampleData, float sampleRate);
    void setReferencePitch(float);
    void setPitch(float);
    
    float getNextValue();
    
    void trigger();
    
private:
    void calculateIncrement();
    
    float projectSampleRate = 44100;
    float sampleSampleRate = 44100;
    
    float referencePitch = 440;
    float pitch = 440;
    
    std::vector<float> sampleData;
    const int padding = 2;
    int sampleSize = 0;
    float playIndex = 0;
    float playIncrement = 1;
};
