/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SpectralDistortionAudioProcessorEditor  : 
    public 
    AudioProcessorEditor,
    private
    ComboBox::Listener
{
public:
    SpectralDistortionAudioProcessorEditor (SpectralDistortionAudioProcessor&, AudioProcessorValueTreeState&);
    ~SpectralDistortionAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    SpectralDistortionAudioProcessor& processor;
    AudioProcessorValueTreeState& treeState;

Slider driveKnob;
Slider cutoffKnob;
Slider blendKnob;
Slider gainKnob;

Slider lowvolumeKnob;
Slider highvolumeKnob;



    //links between parameters and sliders
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveValue;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffValue;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> blendValue;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainValue;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lowvolumeValue;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> highvolumeValue;
    

  

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.


    ComboBox disChoice;

    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectralDistortionAudioProcessorEditor)
};
