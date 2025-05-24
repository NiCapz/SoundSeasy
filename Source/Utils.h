/*
  ==============================================================================

    Utils.h
    Created: 16 May 2025 1:46:13pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once
#include <array>

namespace Utils
{
    float cubicLagrangeInterpolation(std::array<float, 4> y, float x)
    {
        float basisPolynomial[4] = {1, 1, 1, 1};
        for(int i = 0; i < 4; i++)
        {
            for(int m = 0; m < i; m++)
                basisPolynomial[i] *= (x - (m - 1)) / ((i - 1) - (m - 1));
        
            for(int m = i + 1; m < 4; m++)
                basisPolynomial[i] *= (x - (m - 1)) / ((i - 1) - (m - 1));
        }
        
        float res = 0;
        for(int i = 0; i < 4; i++)
            res += y[i] * basisPolynomial[i];
        
        return res;
    }
}
