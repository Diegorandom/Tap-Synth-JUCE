/*
  ==============================================================================

    SynthVoice.cpp
    Created: 19 May 2021 5:19:23pm
    Author:  Diego Ignacio Ortega Martínez

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
    modAdsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    modAdsr.noteOff();
    if(! allowTailOff || ! adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc.prepare(spec);
    adsr.setSampleRate(sampleRate);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    modAdsr.setSampleRate(sampleRate);
    gain.prepare(spec);
    
    gain.setGainLinear(0.3f);
    
    isPrepared = true;
}

void SynthVoice::updateAdsr (const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    
    if(! isVoiceActive())
        return;
    
    synthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
    modAdsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    osc.getNextAudioBlock (audioBlock);
    adsr.applyEnvelopeToBuffer(synthBuffer, startSample, numSamples);
    filter.process(synthBuffer);
    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if(! adsr.isActive())
        {
            clearCurrentNote();
        }
    }
    
}

void SynthVoice::updateFilter (const int filterType, const float filterCutOff, const float filterResonance)
{
    float modulator = modAdsr.getNextSample();
    filter.updateParameters(filterType, filterCutOff, filterResonance, modulator);
}

void SynthVoice::updateModAdsr (const float attack, const float decay, const float sustain, const float release)
{
    modAdsr.updateADSR(attack, decay, sustain, release);
}

