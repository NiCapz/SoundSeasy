/*
  ==============================================================================

    Voice.cpp
    Created: 5 May 2025 6:13:46pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#include "Voice.h"

Voice::Voice(juce::AudioProcessorValueTreeState& parameters):
ampEnvelope(parameters.getRawParameterValue("ampAtk"),
            parameters.getRawParameterValue("ampDec"),
            parameters.getRawParameterValue("ampSus"),
            parameters.getRawParameterValue("ampRel")),
    filEnvelope(parameters.getRawParameterValue("filAtk"),
                parameters.getRawParameterValue("filDec"),
                parameters.getRawParameterValue("filSus"),
                parameters.getRawParameterValue("filRel")),
    filterCutoff(parameters.getRawParameterValue("filCut")),
    filterRes(parameters.getRawParameterValue("filRes")),
    filEnvDepth(parameters.getRawParameterValue("filEnvDepth")),
    unison(parameters.getRawParameterValue("unison")),
    detune(parameters.getRawParameterValue("detune"))
{
    svFilter = std::make_unique<SVFilter>();
}

Voice::Voice(Voice&& other) :
    ampEnvelope(other.ampEnvelope),
    filEnvelope(other.filEnvelope),
    filterCutoff(other.filterCutoff),
    filterRes(other.filterRes),
    filEnvDepth(other.filEnvDepth),
    unison(other.unison),
    detune(other.detune)
{
    svFilter = std::move(other.svFilter);
    
    setSampleRate(other.sampleRate);
    
    envelopeValue = other.envelopeValue;
    
    gateValue = other.gateValue;
    noteLengthCounter = other.noteLengthCounter;
    noteNumber = other.noteNumber;
}

Voice::~Voice() {}

Voice& Voice::operator= (Voice& other)
{
    svFilter = std::move(other.svFilter);
    
    setSampleRate(other.sampleRate);
    
    gateValue = other.gateValue;
    noteLengthCounter = other.noteLengthCounter;
    noteNumber = other.noteNumber;
    
    return *this;
}

float Voice::getNextValue()
{
    updateParameterTargets();
    noteLengthCounter++;
    
    int unisonVal = (int) unison.getValue();
    float detuneVal = detune.getValue() / (sqrt(unisonVal) * 30);
    int offset = 0;
    if(unisonVal % 2 == 0)
    {
        offset = 1;
        detuneVal *= 0.5;
    }
    /*
    for(int osc = 0; osc < unisonVal; osc++)
    {
        float detunePitch = pitch;
        if(osc % 2 == 0)
            detunePitch *= 1 + ((offset + osc) * detuneVal);
        else
            detunePitch /= 1 + ((offset + osc) * detuneVal);
        
        //oscillators[osc]->setPitchHz(detunePitch);
        saws[osc].frequency = detunePitch;
    }
    */
    float out = 0;
    /*
    for(int i = 0; i < oversampling; i++)
    {
        out = 0;
        for(int osc = 0; osc < unisonVal; osc++)
        {
            //out += oscillators[osc]->getNextSample();
            saws[osc].val -= 2 * (saws[osc].frequency / (oversampling * sampleRate));
            if(saws[osc].val < -1) saws[osc].val += 2;
            
            out += saws[osc].val;
        }
        
        for(auto& filter : antiAliasingFilters)
            out = filter->processSample(out);
    }
    
    out /= sqrt((int) unison.getValue());
    envelopeValue = pow(ampEnvelope.getNextValue(gateValue), 4);
    out *= 0.1 * envelopeValue;
    
    float cutoff = filterCutoff.getValue() + 20000 * pow(filEnvDepth.getValue() * filEnvelope.getNextValue(gateValue), 4);
    
    if(cutoff > 20000) cutoff = 20000;
    
    filter->coefficients = IIRCoefficients::makeLowPass(sampleRate, cutoff, filterRes.getValue());
    out = filter->processSample(out);
    
    filterCutoff.update();
    filEnvDepth.update();
    filterRes.update();
    unison.update();
    detune.update();
    */
    return out;
}

void Voice::processBlock(float* buffer, int startSample, int numSamples)
{
    updateParameterTargets();
    
    numSamples = std::min(maxBufferSize, numSamples);
    const size_t osBufferSize = oversampling * (numSamples);
    std::array<float, maxBufferSize * oversampling> processingBuffer{0.0};
    
    unison.update();
    int unisonVal = (int) unison.getValue();
    float u0 = sqrt(unisonVal);
    
    for(int sample = 0; sample < numSamples; sample++)
    {
        float detuneVal = detune.getValue() / (u0 * 30);
        int offset = (unisonVal % 2 == 0);
        
        float detunePitch = pitch;
        
        for(int osc = 0; osc < unisonVal; osc++)
        {
            if(osc % 2 == 0)
                detunePitch *= 1 + ((offset + osc) * detuneVal);
            else
                detunePitch /= 1 + ((offset + osc) * detuneVal);
            
            for(int i = 0; i < oversampling; i++)
            {
                sawOscValues[osc] -= 2 * (detunePitch / (oversampling * sampleRate));
                sawOscValues[osc] += 2 * (sawOscValues[osc] < -1);

                processingBuffer[oversampling * sample + i] += sawOscValues[osc];
            }
        }
        detune.update();
    }
    
    
    for(auto& aaFilter : antiAliasingFilters)
        for(int sample = 0; sample < osBufferSize; sample++)
            processingBuffer[sample] = aaFilter->processSample(processingBuffer[sample]);
    
    for(int sample = 0; sample < numSamples; sample++)
        processingBuffer[sample] = processingBuffer[oversampling * sample];
    
    
    for(int sample = 0; sample < numSamples; sample++)
    {
        envelopeValue = pow(ampEnvelope.getNextValue(gateValue), 4);
        processingBuffer[sample] *= 0.1 * ampEnvelope.getNextValue(gateValue) / u0;
    }
    
    for(int sample = 0; sample < numSamples; sample++)
    {
        float cutoff = filterCutoff.getValue() + 20000 * pow(filEnvDepth.getValue() * filEnvelope.getNextValue(gateValue), 4);
        
        svFilter->parameters->setCutOffFrequency(sampleRate, std::min(cutoff, 20000.0f), filterRes.getValue());
        
        processingBuffer[sample] = svFilter->processSample(processingBuffer[sample]);
        
        filterCutoff.update();
        filterRes.update();
        filEnvDepth.update();
    }
    
    for(int sample = 0; sample < numSamples; sample++)
        buffer[startSample + sample] += processingBuffer[sample];
    
    noteLengthCounter += numSamples;
}

int Voice::getNoteNumber()
{
    return noteNumber;
}

bool Voice::getGate()
{
    return gateValue;
}

float Voice::getAmplitude()
{
    return envelopeValue;
}

long Voice::getNoteLength()
{
    return noteLengthCounter;
}

void Voice::setSampleRate(float val)
{
    sampleRate = val;
    
    ampEnvelope.setSampleRate(val);
    
    float smoothing = pow(0.1, 1000.0 / (sampleRate * 50));
    filterCutoff.setSmoothing(smoothing);
    filterRes.setSmoothing(smoothing);
    filEnvDepth.setSmoothing(smoothing);
    detune.setSmoothing(smoothing);
    
    
    auto filterCoeffs = IIRCoefficients::makeLowPass(oversampling * sampleRate, antiAliasingCutoff);
    
    antiAliasingFilters.clear();
    
    for(int i = 0; i < 2; i++)
        antiAliasingFilters.push_back(std::make_unique<IIRFilter>(filterCoeffs));
}

void Voice::setGate(bool val)
{
    if(gateValue != val)
        noteLengthCounter = 0;

    gateValue = val;
}

void Voice::setNoteNumber(int val)
{
    noteNumber = val;
    pitch = 440 * pow(2.0, (float) (noteNumber - 69) / 12);
}

void Voice::resetEnvelope()
{
    ampEnvelope.reset();
    filEnvelope.reset();
    noteLengthCounter = 0;
}

void Voice::updateParameterTargets()
{
    filterCutoff.updateTarget();
    filEnvDepth.updateTarget();
    filterRes.updateTarget();
    unison.updateTarget();
    detune.updateTarget();
    
    ampEnvelope.updateTarget();
    filEnvelope.updateTarget();
}
