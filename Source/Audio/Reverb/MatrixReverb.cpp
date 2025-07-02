/*
  ==============================================================================

    MatrixReverb.cpp
    Created: 15 Mar 2025 8:41:26pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#include "MatrixReverb.h"
#include "../Utils.h"

MatrixReverb::MatrixReverb(std::atomic<float>* distance,
                           std::atomic<float>* chorus,
                           std::atomic<float>* decayS,
                           std::atomic<float>* damp,
                           std::atomic<float>* density) :
                distance(distance),
                chorus(chorus),
                decayS(decayS),
                damp(damp),
                density(density)
{
    delays = std::array<float, numKernels>{0};
    lowpassSamples = std::array<float, numKernels>{0};
    
    delayBuffer = std::array<std::vector<float>, numKernels>{std::vector<float>{0}};
    outputBuffer = std::array<std::vector<float>, numKernels>{std::vector<float>{0}};
    
    allpassBuffer = std::array<std::vector<float>, numKernels>{std::vector<float>{0}};
    
    for(auto& fb : feedbackSamples)
        fb = Eigen::MatrixXf::Zero(numKernels, 1);
    decayMatrix = Eigen::MatrixXf::Zero(numKernels, numKernels);
    diffuseMatrix = Eigen::MatrixXf::Zero(numKernels, numKernels);
    
    for(int i = 0; i < numKernels; i++)
        for(int j = 0; j < numKernels; j++)
            diffuseMatrix(i, j) = matrix_data[i + j * numKernels];
    
    for(int i = 0; i < numKernels; i++)
        modPhases[i] = i * 2 * M_PI / numKernels;
    
    this->distance.updateTarget();
    this->chorus.updateTarget();
    this->decayS.updateTarget();
    this->damp.updateTarget();
    this->density.updateTarget();
}
                

void MatrixReverb::setSamplerate(float sampleRate)
{
    projectSampleRate = sampleRate;
    
    delayBufferSize = std::ceil(maxDelayMs * projectSampleRate / 1000) * 2;
    allpassBufferSize = std::ceil(delayBufferSize * allpassDelayRatio);
    
    lowpassSamples = std::array<float, numKernels>{0};
    
    for(int i = 0; i < numKernels; i++)
    {
        delayBuffer[i] = std::vector<float>(delayBufferSize, 0);
        outputBuffer[i] = std::vector<float>(delayBufferSize, 0);
        allpassBuffer[i] = std::vector<float>(allpassBufferSize, 0);
    }
    
    smoothingCoeff = pow(0.1, 1000.0 / (smoothingMs * projectSampleRate));
    
    modIncrement = M_PI / sampleRate;
    
    for(int i = 0; i < numKernels; i++)
        modPhases[i] = i * 2 * M_PI / numKernels;
    
    chorus.setSmoothing(smoothingCoeff);
    decayS.setSmoothing(smoothingCoeff);
    damp.setSmoothing(smoothingCoeff);
    density.setSmoothing(smoothingCoeff);
}

void MatrixReverb::calculateDelays()
{
    float d0 = minD0 + (maxD0 - minD0) * distance.getValue();

    float delayScale = pow(3.0, 1.0 / numKernels);
    
    targetDelays[0] = d0 * projectSampleRate / 1000;
    for(int i = 1; i < numKernels; i++)
        targetDelays[i] = targetDelays[i - 1] * delayScale;
    
    float decaySamples = decayS.getValue() * projectSampleRate;
    for(int i = 0; i < numKernels; i++)
        targetDecays[i] = pow(0.001, targetDelays[i] / decaySamples);
    
    for(int i = 0; i < numKernels; i++)
        targetAllpassDelays[i] = allpassDelayRatio * targetDelays[i];
}

void MatrixReverb::processBlock(juce::AudioBuffer<float>& buffer)
{
    int numChannels = buffer.getNumChannels();
    int numSamples = buffer.getNumSamples();
    
    std::vector<float> inputBuffer(numSamples, 0);

    
    calculateDelays();
    
    for(int buffer = 0; buffer < numKernels; buffer++)
    {
        for(int sample = 0; sample < numSamples; sample++)
        {
            int writeIndex = (delayBufferIndex + sample) % delayBufferSize;
            delayBuffer[buffer][writeIndex] = 0;
        }
    }
    
    for(int channel = 0; channel < numChannels; channel++)
    {
        auto* channelData = buffer.getReadPointer(channel);
        for(int sample = 0; sample < numSamples; sample++)
        {
            inputBuffer[sample] += channelData[sample];
        }
    }
    
    for(int buffer = 0; buffer < numKernels; buffer++)
    {
        for(int sample = 0; sample < numSamples; sample++)
        {
            int writeIndex = (delayBufferIndex + sample) % delayBufferSize;
            delayBuffer[buffer][writeIndex] += inputBuffer[sample] / (2 * numKernels);
        }
    }
    
    std::array<float, 4> interpolationSamples{0};
    std::array<float, processingBufferSize> delayTimeBuffer{0};
    
    int samplesToProcess = numSamples;
    while(samplesToProcess > 0)
    {
        int n = 0;
        if(samplesToProcess > processingBufferSize)
            n = processingBufferSize;
        else
            n = samplesToProcess;
        
        chorus.store();
        damp.store();
        density.store();
        
        int d0 = delayBufferIndex;
        int a0 = allpassBufferIndex;
        for(int line = 0; line < numKernels; line++)
        {
            //calculate delay times
            chorus.recall();
            
            for(int sample = 0; sample < n; sample++)
            {
                delays[line] = smoothingCoeff * delays[line] + (1 - smoothingCoeff) * targetDelays[line];
                
                float mod = sin(modPhases[line]);
                float delay = delays[line] + chorus.getValue() * modDepth * mod * mod;
                
                modPhases[line] += modIncrement;
                modPhases[line] *= (modPhases[line] < 2 * M_PI);
                
                delayTimeBuffer[sample] = delay;
                chorus.update();
            }
            
            //sample from delay lines
            delayBufferIndex = d0;
            
            for(int sample = 0; sample < n; sample++)
            {
                float delay = delayTimeBuffer[sample];
                int bufferIndex = (delayBufferSize + delayBufferIndex - (int) delay) % delayBufferSize;
                
                for(int j = 0; j < 4; j++)
                {
                    int index = (delayBufferSize + bufferIndex - 2 + j) % delayBufferSize;
                    interpolationSamples[j] = delayBuffer[line][index];
                }
                
                float modulatedSample = Utils::cubicLagrangeInterpolation(interpolationSamples, 1.0 - (delay - floor(delay)));
                
                processingBuffers[line][sample] = modulatedSample;
                
                delayBufferIndex += 1;
                delayBufferIndex %= delayBufferSize;
            }
            
            //apply lowpass
            damp.recall();
            for(int sample = 0; sample < n; sample++)
            {
                float lowPassCoeff = (5000 * damp.getValue() / projectSampleRate);
                lowpassSamples[line] = (1 - lowPassCoeff) * processingBuffers[line][sample] + lowPassCoeff * lowpassSamples[line];
                processingBuffers[line][sample] = lowpassSamples[line];
                damp.update();
            }
            
            /*
            //apply allpass
            density.recall();
            allpassBufferIndex = a0;
            for(int sample = 0; sample < n; sample++)
            {
                allpassBuffer[line][allpassBufferIndex] = processingBuffers[line][sample];
                
                //std::array<float, 4> interpolationSamples{0};
                for(int j = 0; j < 4; j++)
                {
                    int index = (allpassBufferSize + allpassBufferIndex - (int) allpassDelays[line] - 2 + j) % allpassBufferSize;
                    interpolationSamples[j] = allpassBuffer[line][index];
                }
                
                float allpassSample = cubicLagrangeInterpolation(interpolationSamples, 1.0 - (allpassDelays[line] - floor(allpassDelays[line])));
                
                float in = allpassBuffer[line][allpassBufferIndex];
                float diffusion = 0.001 + 0.7 * density.getValue();
                allpassBuffer[line][allpassBufferIndex] += diffusion * allpassSample;
     
                allpassSample = ((1.0 / diffusion) - diffusion) * allpassBuffer[line][allpassBufferIndex] - (1.0 / diffusion) * in;
                
                processingBuffers[line][sample] = allpassSample;
                
                allpassBufferIndex += 1;
                allpassBufferIndex %= allpassBufferSize;
                density.update();
            }
            */
            //add to output buffer
            for(int sample = 0; sample < n; sample++)
            {
                outputBuffer[line][numSamples - samplesToProcess + sample] = processingBuffers[line][sample];
            }
        }
        
        
        for(int sample = 0; sample < n; sample++)
            for(int line = 0; line < numKernels; line++)
                feedbackSamples[sample](line, 0) = processingBuffers[line][sample];
            
        
        for(int sample = 0; sample < n; sample++)
        {
            Eigen::Matrix<float, 1, numKernels> t = feedbackSamples[sample].transpose();
            feedbackSamples[sample].noalias() = t * diffuseMatrix;
        }
        //add feedback to delay lines
        
        delayBufferIndex = d0;
        for(int sample = 0; sample < n; sample++)
        {
            for(int i = 0; i < numKernels; i++)
                decayCoeffs[i] = smoothingCoeff * decayCoeffs[i] + (1 - smoothingCoeff) * targetDecays[i];
            
            for(int line = 0; line < numKernels; line++)
                delayBuffer[line][delayBufferIndex] += feedbackSamples[sample](line, 0) * decayCoeffs[line];

            delayBufferIndex += 1;
            delayBufferIndex %= delayBufferSize;
            
            decayS.update();
        }
        
        samplesToProcess -= n;
    }
    
    buffer.applyGain(0);
    for(int channel = 0; channel < numChannels; channel++)
    {
        auto* channelData = buffer.getWritePointer(channel);
        
        for(int kernel = 0; kernel < numKernels; kernel += 2)
            for(int sample = 0; sample < numSamples; sample++)
                channelData[sample] += outputBuffer[kernel + channel][sample];
    }
    
}

