/*
  ==============================================================================

    MidiManager.cpp
    Created: 19 Jun 2025 7:58:55pm
    Author:  Karl Diedrichsen

  ==============================================================================
*/

#include "MidiManager.h"

MidiManager::MidiManager()
{
    
}

MidiManager::~MidiManager()
{
    
}

void MidiManager::reset(double sampleRate)
{
    this->sampleRate = sampleRate;
    
    messages.clear();
}

void MidiManager::addMessageToQueue(const juce::MidiMessage& message)
{
    std::lock_guard<std::mutex> guard(messageListMutex);
    
    auto messageIterator = messages.begin();
    
    if(messageIterator == messages.end())
        messages.insert(messageIterator, message);
    
    
    while(messageIterator != messages.end())
    {
        if(messageIterator->getTimeStamp() < message.getTimeStamp())
        {
            messages.insert(++messageIterator, message);
            break;
        }
        else
        {
            messageIterator++;
        }
    }
}

void MidiManager::removeNextBlockOfMessages(juce::MidiBuffer& midiBuffer, int numSamples)
{
    std::lock_guard<std::mutex> guard(messageListMutex);
    
    double t0 = startTime + timeElapsed;
    double t1 = t0 + (numSamples / sampleRate);
    
    while(messages.begin() != messages.end() && messages.front().getTimeStamp() < t1)
    {
        int sampleNumber = numSamples * (messages.front().getTimeStamp() - t0) / (t1 - t0);
        sampleNumber = std::clamp(sampleNumber, 0, numSamples);
        midiBuffer.addEvent(messages.front(), sampleNumber);
        
        messages.pop_front();
    }
    
    timeElapsed += (numSamples / sampleRate);
}
