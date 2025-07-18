/*
  ==============================================================================

    AllPass.cpp
    Created: 9 Feb 2025 9:00:32am
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#include "AllPass.h"

AllPass::AllPass()
{
    AllPass(5, 0.1, 44100);
}

AllPass::AllPass(float delayMs, float feedbackPercent, int sampleRate)
{
    if(delayMs > maxDelayMs)
    {
        targetDelayMs = maxDelayMs;
        currentDelayMs = maxDelayMs;
    }
    else if(delayMs < 0)
    {
        targetDelayMs = 0;
        currentDelayMs = 0;
    }
    else
    {
        targetDelayMs = delayMs;
        currentDelayMs = delayMs;
    }
    
    if(feedbackPercent > 100)
    {
        targetFeedback = 100;
        currentFeedback = 100;
    }
    else if(feedbackPercent < 0)
    {
        targetFeedback = 0;
        currentFeedback = 0;
    }
    else
    {
        targetFeedback = feedbackPercent;
        currentFeedback = feedbackPercent;
    }
    
    this->sampleRate = sampleRate;
    smoothingCoeff = pow(0.1, 1000.0 / (parameterSmoothingMs * sampleRate));
    
    int backBufferSize = maxDelayMs * ((float) sampleRate / 1000) + 1;
    backBuffer = std::vector<float> (backBufferSize, 0);
}

void AllPass::setDelayMs(float delayMs)
{
    targetDelayMs = std::min(delayMs, maxDelayMs);
}

void AllPass::setFeedbackPercent(float feedbackPercent)
{
    targetFeedback = feedbackPercent;
}

void AllPass::setSampleRate(int sampleRate)
{
    this->sampleRate = sampleRate;
    smoothingCoeff = pow(0.1, 1000.0 / (parameterSmoothingMs * sampleRate));
    
    int backBufferSize = maxDelayMs * ((float) sampleRate / 1000) + 1;
    backBuffer = std::vector<float> (backBufferSize, 0);
    backBufferIndex = 0;
}

float AllPass::process(float sample)
{
    int bufferSize = backBuffer.size();
    backBufferIndex = (backBufferIndex + 1) % bufferSize;
    currentDelayMs = smoothingCoeff * currentDelayMs + (1.0 - smoothingCoeff) * targetDelayMs;
    currentFeedback = smoothingCoeff * currentFeedback + (1.0 - smoothingCoeff) * targetFeedback;
    
    float delaySamples = currentDelayMs * ((float) sampleRate / 1000);
    float delaySampleOffset = delaySamples - (int) delaySamples;
    
    for(int i = 0; i < 4; i++)
        interpolationSamples[i] = backBuffer[(bufferSize + backBufferIndex - (int) delaySamples - 2 + i) % bufferSize];
    
    if((int) delaySamples == 0)
        interpolationSamples[2] = interpolationSamples[1];
    if((int) delaySamples <= 1)
        interpolationSamples[3] = interpolationSamples[2];
    
    float delayedSample = cubicLagrangeInterpolation(interpolationSamples, 1.0 - delaySampleOffset);
    float feedback = currentFeedback / 100.0;
    
    backBuffer[backBufferIndex] = sample + feedback * delayedSample;
    return ((1.0 / feedback) - feedback) * backBuffer[backBufferIndex] - (sample / feedback);
}

void AllPass::processBlock(float* buffer, int numSamples)
{
    
    for(int sample = 0; sample < numSamples; sample++)
        buffer[sample] = process(buffer[sample]);
}
/*
float AllPass::cubicLagrangeInterpolation(std::array<float, 4>& y, float x)
{
    static const float b[4] = {1.0 / -6, 1.0 / 2, 1.0 / -2, 1.0 / 6};
    float basisPolynomial[4] = {b[0], b[1], b[2], b[3]};
    for(int i = 0; i < 4; i++)
    {
        for(int m = 0; m < i; m++)
            basisPolynomial[i] *= (x - (m - 1));
    
        for(int m = i + 1; m < 4; m++)
            basisPolynomial[i] *= (x - (m - 1));
    }
    float res = 0;
    for(int i = 0; i < 4; i++)
        res += y[i] * basisPolynomial[i];
    
    return res;
}
*/
