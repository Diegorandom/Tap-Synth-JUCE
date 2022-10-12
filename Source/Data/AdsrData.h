/*
  ==============================================================================

    AdsrData.h
    Created: 21 May 2021 1:49:24pm
    Author:  Diego Ignacio Ortega Martínez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR (const float attack, const float decay, const float sustain, const float release);
    
private:
    juce::ADSR::Parameters adsrParams;
};
