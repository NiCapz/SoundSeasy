/*
  ==============================================================================

    SmoothedParameter.h
    Created: 15 Mar 2025 8:41:07pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#pragma once

#include <atomic>

template <typename T>
class SmoothedParameter
{
public:
    SmoothedParameter(std::atomic<T>* target)
    {
        targetValue = target;
        value = *target;
        smoothing = 0;
    }
    SmoothedParameter(SmoothedParameter& other)
    {
        targetValue = other.targetValue;
        value = other.value;
        smoothing = other.smoothing;
    }

    void setSmoothing(float s) { smoothing = s; }
    float getSmoothing() { return smoothing; }
    
    void update()
    {
        value = smoothing * value + (1 - smoothing) * target;
    }
    
    void updateTarget()
    {
        target = *targetValue;
    }
    
    void setTarget(std::atomic<T>* t) { targetValue = t; }
    
    T getTargetValue() { return *targetValue; }
    T getValue() { return value; }
    
    void store() { storedValue = value; }
    void recall() { value = storedValue; }
    
    bool targetReached() { return abs(*targetValue - value) < 1e-8; }
    
private:
    std::atomic<T>* targetValue;
    float target;
    T value;
    T storedValue;
    float smoothing;
};
