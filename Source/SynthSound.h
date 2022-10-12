/*
  ==============================================================================

    SynthSound.h
    Created: 19 May 2021 5:20:04pm
    Author:  Diego Ignacio Ortega Martínez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
};
