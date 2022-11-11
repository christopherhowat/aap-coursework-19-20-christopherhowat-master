/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpectralDistortionAudioProcessorEditor::SpectralDistortionAudioProcessorEditor (SpectralDistortionAudioProcessor& p, 
    AudioProcessorValueTreeState& vts)
: AudioProcessorEditor (&p), processor (p), treeState(vts)

{ // adding knobs changing desgin etc

    setSize(800, 400);

    getLookAndFeel().setColour(Slider::thumbColourId, Colours::whitesmoke);


    lowvolumeValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "lowVolume", lowvolumeKnob);
    lowvolumeKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    lowvolumeKnob.setRange(0.0f, 2.f, 0.f);
    lowvolumeKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&lowvolumeKnob);


    highvolumeValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "highVolume", highvolumeKnob);
    highvolumeKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    highvolumeKnob.setRange(0.0f, 2.f, 0.f);
    highvolumeKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&highvolumeKnob);

    
    driveValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "drive", driveKnob);
    driveKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    driveKnob.setRange (0.0f, 20.0f, 0.0f);
    driveKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&driveKnob);
    
    cutoffValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "cutoff", cutoffKnob);
    cutoffKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    cutoffKnob.setRange (20.0f, 3000.0f, 0.0f);
    cutoffKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&cutoffKnob);

    blendValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "blend", blendKnob);
    blendKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    blendKnob.setRange (0.0f, 1.0f, 0.0f);
    blendKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&blendKnob);
    
    gainValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "gain", gainKnob);
    gainKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    gainKnob.setRange (0.0f, 1.0f, 0.0f);
    gainKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&gainKnob);
    
    //adding text to combobox

    addAndMakeVisible(&disChoice); // 1
    disChoice.addItem("Soft Clip", 1);
    disChoice.addItem("Soft Clip 2", 2);
    disChoice.addItem("Overdrive", 3); 
    disChoice.setSelectedId(1);
    disChoice.addListener(this);

}

SpectralDistortionAudioProcessorEditor::~SpectralDistortionAudioProcessorEditor()
{
}

//==============================================================================
void SpectralDistortionAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colour(240, 223, 242));




    g.setFont(Font("Helvetica", 30.0f, Font::italic));
    g.setColour(Colours::darkgrey);
    g.drawFittedText("Spectral Distortion :~)", 260, 30, 300, 10, Justification::centred, 1, 0.0f);



    //eq border

    Rectangle <float> area3(((getWidth() / 7) * 1.5) - (90), (getHeight() / 2) - 95, 230, 240);
   // g.setColour(Colour(227, 151, 70));
    g.setColour(Colour(117, 176, 0));
    g.drawRoundedRectangle(area3, 7.0f, 3.0f);
        
    //plugin border
    Rectangle <float> area4(0, 0, 800, 400);
    g.setColour(Colour(164, 236, 252));
    g.drawRoundedRectangle(area4, 10.0f, 20.0f);     
    
    //dist border
    Rectangle <float> area10(((getWidth() / 7) * 4) - (86), (getHeight() / 2) - 95, 350, 240);
    g.setColour(Colour(235, 140, 23));
    g.drawRoundedRectangle(area10, 7.0f, 3.0f);
    // 66, 135, 245)

    //knob rings
    Rectangle <float> area2(((getWidth() / 7) * 1), (getHeight() / 2) - 50, 50, 50);
    g.setColour(Colour(178, 219, 94));
    g.drawRoundedRectangle(area2, 100.0f, 5.0f);

    Rectangle <float> area5(((getWidth() / 7) * 2), (getHeight() / 2) - 50, 50, 50);
    g.setColour(Colour(178, 219, 94));
    g.drawRoundedRectangle(area5, 100.0f, 5.0f);

    Rectangle <float> area6(((getWidth() / 7) * 4) - (50), (getHeight() / 2) + 15 + 25, 50, 50);
    g.setColour(Colour(237, 195, 135));
    g.drawRoundedRectangle(area6, 100.0f, 5.0f);

    Rectangle <float> area7(((getWidth() / 7) * 1.5), ((getHeight() / 6) * 4) - 25, 50, 50);
    g.setColour(Colour(178, 219, 94));
    g.drawRoundedRectangle(area7, 100.0f, 5.0f);
    
    Rectangle <float> area8(((getWidth() / 7) * 5) - (50), 170 + 25, 50, 50);
    g.setColour(Colour(237, 195, 135));
    g.drawRoundedRectangle(area8, 100.0f, 5.0f);
    
    Rectangle <float> area9(((getWidth() / 7) * 6) - (50), (getHeight() / 2) - (100 / 2), 50, 50);
    g.setColour(Colour(237, 195, 135));
    g.drawRoundedRectangle(area9, 100.0f, 5.0f);
    
 

    g.setColour(Colours::darkgrey);
    g.setFont(16.0f);

    g.setFont(Font("Ariel", 16.0f, Font::plain));

    //display text
    g.drawText("LPF", ((getWidth() / 7) * 1) - (100 / 2) + 25, (getHeight() / 2) - 20, 100, 100, Justification::centred, false);
    g.drawText("HPF", ((getWidth() / 7) * 2) - (100 / 2) + 25, (getHeight() / 2) - 20, 100, 100, Justification::centred, false);
    g.drawText("Drive", ((getWidth() / 7) * 4) - (100 / 2) - 25, (getHeight() / 2) + 15 + 55, 100, 100, Justification::centred, false);
    g.drawText("Cutoff", ((getWidth() / 7) * 1.5) - (100 / 2) + 25, (getHeight() / 2) + 70, 100, 100, Justification::centred, false);
    g.drawText("Blend", ((getWidth() / 7) * 5) - (100 / 2) - 25, 170 + 55, 100, 100, Justification::centred, false);
    g.drawText("Gain", ((getWidth() / 7) * 6) - (100 / 2) - 25, (getHeight() / 2) - ((100 / 2) + 25) + 55, 100, 100, Justification::centred, false);
    g.setFont(Font("Ariel", 20.0f, Font::italic));
    g.drawText("EQ", ((getWidth() / 7) * 1.5) - (100 / 2) - 75, (getHeight() / 2) - 155, 100, 100, Justification::centred, false);
    g.drawText("Distortion", ((getWidth() / 7) * 1.5) - (100 / 2) + 240, (getHeight() / 2) - 155, 100, 100, Justification::centred, false);


}

void SpectralDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    //display knobs
  

    lowvolumeKnob.setBounds(((getWidth() / 7) * 1) - (100 / 2) + 25, (getHeight() / 2) - ((100 / 2) + 25 ), 100, 100);
    highvolumeKnob.setBounds(((getWidth() / 7) * 2) - (100 / 2) + 25, (getHeight() / 2) - ((100 / 2) + 25), 100, 100);
    driveKnob.setBounds(((getWidth() / 7) * 4) - (100 / 2) - 25, (getHeight() / 2) + 15, 100, 100);
    cutoffKnob.setBounds(((getWidth() / 7) * 1.5) - (100 / 2) + 25, (getHeight() / 2) + 15, 100, 100);
    blendKnob.setBounds(((getWidth() / 7) * 5) - (100 / 2) - 25, 170, 100, 100);
    gainKnob.setBounds(((getWidth() / 7) * 6) - (100 / 2) - 25, (getHeight() / 2) - ((100 / 2) + 25), 100, 100);
    disChoice.setBounds(25, 25, 100, 25);
} 

void SpectralDistortionAudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    processor.menuChoice = comboBoxThatHasChanged->getSelectedId();

}