/*
  ==============================================================================

    OscData.cpp
    Created: 21 May 2021 2:59:27pm
    Author:  Diego Ignacio Ortega Martínez

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    fmOsc.prepare(spec);
    prepare(spec);
}


void OscData::setWaveType (const int choice)
{
    switch (choice) {
        case 0:
            initialise([](float x) {return std::sin (x); });
            break;
        case 1:
            initialise([](float x) {return x / juce::MathConstants<float>::pi;});
            break;
        case 2:
            initialise([](float x) {return x < 0.0f ? -1.0 : 1.0f; });
            break;
            
        default:
            jassertfalse;
            break;
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency (juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber) + fmMod);
    lastMidiNoteNumber = midiNoteNumber;
}

void OscData::getNextAudioBlock (juce::dsp::AudioBlock<float>& block)
{
    for( int ch = 0; ch < block.getNumChannels(); ++ch)
    {
        for (int s = 0; s < block.getNumSamples(); ++s)
        {
            fmMod = fmOsc.processSample(block.getSample(ch, s)) * fmDepth;
        }
    }
    
    process(juce::dsp::ProcessContextReplacing<float> (block));
}

void OscData::setFmParams (const float depth, const float freq)
{
    fmOsc.setFrequency(freq);
    fmDepth = depth;
    auto currentFreq = juce::MidiMessage::getMidiNoteInHertz (lastMidiNoteNumber) + fmMod;
    setFrequency (currentFreq >= 0 ? currentFreq : currentFreq * - 1.0f);
}
