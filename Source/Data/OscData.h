/*
  ==============================================================================

    OscData.h
    Created: 21 May 2021 2:59:27pm
    Author:  Diego Ignacio Ortega Martínez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay (juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFrequency (const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setFmParams (const float depth, const float freq);
    
private:
    juce::dsp::Oscillator<float> fmOsc { [](float x) {return std::sin (x); } };
    float fmMod { 0.0f };
    float fmDepth {0.0f};
    int lastMidiNoteNumber {0};
};
