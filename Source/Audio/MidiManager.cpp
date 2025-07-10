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
    {
        messages.insert(messageIterator, message);
        return;
    }
    
    bool isNoteOff = message.isNoteOff();
    double t = message.getTimeStamp();
    while(messageIterator != messages.end())
    {
        double t1 = messageIterator->getTimeStamp();
        if(messageIterator->getTimeStamp() >= message.getTimeStamp())
        {
            messages.insert(messageIterator, message);
            return;
        }
        else
        {
            messageIterator++;
        }
    }
    
    if(messageIterator == messages.end())
        messages.push_back(message);
    
    if(messages.size() == 6)
    {
        
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
