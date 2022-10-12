/*
  ==============================================================================

    FilterComponent.cpp
    Created: 22 May 2021 6:03:47pm
    Author:  Diego Ignacio Ortega Martínez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeId, juce::String filterCutOffId, juce::String filterResonanceId)
{
    juce::StringArray choices {"Low Pass", "Band Pass", "High Pass"};
    filterTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(filterTypeSelector);
    
    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (apvts, filterTypeId, filterTypeSelector);
    
    setSliderWithLabel(filterCutOffSlider, cutOffLabel, apvts, filterCutOffId, CutOffAttachment);
    setSliderWithLabel(filterResonanceSlider, resonanceLabel, apvts, filterResonanceId, ResonanceAttachment);

}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void FilterComponent::resized()
{
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto sliderPosY = 80;
    
    filterTypeSelector.setBounds(0, 0, 90, 20);
    filterCutOffSlider.setBounds(0, sliderPosY, sliderWidth, sliderHeight );
    cutOffLabel.setBounds(filterCutOffSlider.getX(), filterCutOffSlider.getY() - labelYOffset, filterCutOffSlider.getWidth(), labelHeight);
    
    filterResonanceSlider.setBounds(filterCutOffSlider.getRight(), sliderPosY, sliderWidth, sliderHeight );
    resonanceLabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - labelYOffset, filterResonanceSlider.getWidth(), labelHeight);

}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void FilterComponent::setSliderWithLabel(juce::Slider& slider , juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (apvts, paramId, slider);
        
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

}
