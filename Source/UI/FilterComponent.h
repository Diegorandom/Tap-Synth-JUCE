/*
  ==============================================================================

    FilterComponent.h
    Created: 22 May 2021 6:03:47pm
    Author:  Diego Ignacio Ortega Martínez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeId, juce::String filterCutOffId, juce::String filterResonanceId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterTypeSelector { "Filter Type" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;

    juce::Slider filterCutOffSlider;
    juce::Slider filterResonanceSlider;
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<Attachment> CutOffAttachment;
    std::unique_ptr<Attachment> ResonanceAttachment;
    
    juce::Label filterSelectorLabel {"Filter Type", "Filter Type"};
    juce::Label cutOffLabel {"CutOff", "CutOff"};
    juce::Label resonanceLabel {"Resonance", "Resonance"};
    
    
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment );

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
