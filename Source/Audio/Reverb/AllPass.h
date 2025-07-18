/*
  ==============================================================================

    AllPass.h
    Created: 28 Mar 2025 6:40:46pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <array>
#include <vector>

class AllPass
{
public:
    AllPass();
    AllPass(float delayMs, float feedbackPercent, int sampleRate);
    
    void setDelayMs(float);
    void setFeedbackPercent(float);
    void setSampleRate(int);
    
    float process(float);
    void processBlock(float*, int);
private:
    
    static constexpr float cubicLagrangeInterpolation(std::array<float, 4>& y, float x)
    {
        const float b[4] = {1.0 / -6, 1.0 / 2, 1.0 / -2, 1.0 / 6};
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
    
    std::vector<float> backBuffer;
    int backBufferIndex = 0;
    
    int sampleRate;
    const float parameterSmoothingMs = 10;
    float smoothingCoeff;
    
    const float maxDelayMs = 10;
    float targetDelayMs;
    float currentDelayMs;
    
    float targetFeedback;
    float currentFeedback;
    
    std::array<float, 4> interpolationSamples{0.0};
};
