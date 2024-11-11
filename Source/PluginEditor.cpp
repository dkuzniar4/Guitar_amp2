/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Guitar_ampAudioProcessorEditor::Guitar_ampAudioProcessorEditor (Guitar_ampAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    myKnobLook.setLookAndFeelSliderRotary(juce::ImageCache::getFromMemory(BinaryData::knobRelease_png, BinaryData::knobRelease_pngSize));

    addAndMakeVisible(InputVolume_knob);
    InputVolume_knob.setLookAndFeel(&myKnobLook);
    InputVolume_knob.setSliderStyle(juce::Slider::Rotary);
    InputVolume_knob.setRotaryParameters(3.92, 8.63, true);
    InputVolume_knob.setRange(0.0, 2.0, 0.01);
    InputVolume_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    InputVolume_knob.setPopupDisplayEnabled(true, false, this);
    InputVolume_knob.setTextValueSuffix(" Input volume");
    InputVolume_knob.setValue(audioProcessor.ampSim.getInputVolume());
    InputVolume_knob.addListener(this);

    addAndMakeVisible(Bass_knob);
    Bass_knob.setLookAndFeel(&myKnobLook);
    Bass_knob.setSliderStyle(juce::Slider::Rotary);
    Bass_knob.setRotaryParameters(3.92, 8.63, true);
    Bass_knob.setRange(0.00, 20.0, 0.01);
    Bass_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    Bass_knob.setPopupDisplayEnabled(true, false, this);
    Bass_knob.setTextValueSuffix(" Bass");
    Bass_knob.setValue(audioProcessor.ampSim.getBassVolume());
    Bass_knob.addListener(this);

    addAndMakeVisible(Mid_knob);
    Mid_knob.setLookAndFeel(&myKnobLook);
    Mid_knob.setSliderStyle(juce::Slider::Rotary);
    Mid_knob.setRotaryParameters(3.92, 8.63, true);
    Mid_knob.setRange(0.00, 20.0, 0.01);
    Mid_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    Mid_knob.setPopupDisplayEnabled(true, false, this);
    Mid_knob.setTextValueSuffix(" Mid");
    Mid_knob.setValue(audioProcessor.ampSim.getMidVolume());
    Mid_knob.addListener(this);

    addAndMakeVisible(Treble_knob);
    Treble_knob.setLookAndFeel(&myKnobLook);
    Treble_knob.setSliderStyle(juce::Slider::Rotary);
    Treble_knob.setRotaryParameters(3.92, 8.63, true);
    Treble_knob.setRange(0.00, 20.0, 0.01);
    Treble_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    Treble_knob.setPopupDisplayEnabled(true, false, this);
    Treble_knob.setTextValueSuffix(" Treble");
    Treble_knob.setValue(audioProcessor.ampSim.getTrebleVolume());
    Treble_knob.addListener(this);

    addAndMakeVisible(Threshold_knob);
    Threshold_knob.setLookAndFeel(&myKnobLook);
    Threshold_knob.setSliderStyle(juce::Slider::Rotary);
    Threshold_knob.setRotaryParameters(3.92, 8.63, true);
    Threshold_knob.setRange(0.01, 1.0, 0.01);
    Threshold_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    Threshold_knob.setPopupDisplayEnabled(true, false, this);
    Threshold_knob.setTextValueSuffix(" Threshold");
    Threshold_knob.setValue(audioProcessor.ampSim.getThreshold());
    Threshold_knob.addListener(this);

    addAndMakeVisible(Comp_knob);
    Comp_knob.setLookAndFeel(&myKnobLook);
    Comp_knob.setSliderStyle(juce::Slider::Rotary);
    Comp_knob.setRotaryParameters(3.92, 8.63, true);
    Comp_knob.setRange(0.01, 1.0, 0.01);
    Comp_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    Comp_knob.setPopupDisplayEnabled(true, false, this);
    Comp_knob.setTextValueSuffix(" Comp");
    Comp_knob.setValue(audioProcessor.ampSim.getGainAbove());
    Comp_knob.addListener(this);

    addAndMakeVisible(MasterVolume_knob);
    MasterVolume_knob.setLookAndFeel(&myKnobLook);
    MasterVolume_knob.setSliderStyle(juce::Slider::Rotary);
    MasterVolume_knob.setRotaryParameters(3.92, 8.63, true);
    MasterVolume_knob.setRange(0.00, 2.0, 0.01);
    MasterVolume_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    MasterVolume_knob.setPopupDisplayEnabled(true, false, this);
    MasterVolume_knob.setTextValueSuffix(" Master volume");
    MasterVolume_knob.setValue(audioProcessor.ampSim.getMasterVolume());
    MasterVolume_knob.addListener(this);

    Power_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::power_ON_png, BinaryData::power_ON_pngSize), 1.0,
        juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
        juce::ImageCache::getFromMemory(BinaryData::power_ON_png, BinaryData::power_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    addAndMakeVisible(Power_button);
    Power_button.addListener(this);

    Cab_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::cab_ON_png, BinaryData::cab_ON_pngSize), 1.0,
        juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
        juce::ImageCache::getFromMemory(BinaryData::cab_ON_png, BinaryData::cab_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    addAndMakeVisible(Cab_button);
    Cab_button.addListener(this);

    Plus_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::plus_ON_png, BinaryData::plus_ON_pngSize), 1.0,
        juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
        juce::ImageCache::getFromMemory(BinaryData::plus_ON_png, BinaryData::plus_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    addAndMakeVisible(Plus_button);
    Plus_button.addListener(this);

    Minus_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::minus_ON_png, BinaryData::minus_ON_pngSize), 1.0,
        juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
        juce::ImageCache::getFromMemory(BinaryData::minus_ON_png, BinaryData::minus_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    addAndMakeVisible(Minus_button);
    Minus_button.addListener(this);

    setSize(700, 250);
}

Guitar_ampAudioProcessorEditor::~Guitar_ampAudioProcessorEditor()
{
}

//==============================================================================
void Guitar_ampAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
    background = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    g.drawImageAt(background, 0, 0);

    if (audioProcessor.ampSim.getAmpState() == 0)
    {
        Power_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::power_OFF_png, BinaryData::power_OFF_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::power_OFF_png, BinaryData::power_OFF_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    }
    else
    {
        Power_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::power_ON_png, BinaryData::power_ON_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::power_ON_png, BinaryData::power_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    }

    if (audioProcessor.ampSim.getCabState() == 0)
    {
        Cab_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::cab_OFF_png, BinaryData::cab_OFF_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::cab_OFF_png, BinaryData::cab_OFF_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    }
    else
    {
        Cab_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::cab_ON_png, BinaryData::cab_ON_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::cab_ON_png, BinaryData::cab_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    }

    if (audioProcessor.ampSim.getPlus() == 0)
    {
        Plus_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::plus_OFF_png, BinaryData::plus_OFF_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::plus_OFF_png, BinaryData::plus_OFF_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    }
    else
    {
        Plus_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::plus_ON_png, BinaryData::plus_ON_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::plus_ON_png, BinaryData::plus_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    }

    if (audioProcessor.ampSim.getMinus() == 0)
    {
        Minus_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::minus_OFF_png, BinaryData::minus_OFF_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::minus_OFF_png, BinaryData::minus_OFF_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    }
    else
    {
        Minus_button.setImages(true, true, true, juce::ImageCache::getFromMemory(BinaryData::minus_ON_png, BinaryData::minus_ON_pngSize), 1.0,
            juce::Colours::transparentWhite, juce::Image(), 1.0, juce::Colours::transparentWhite,
            juce::ImageCache::getFromMemory(BinaryData::minus_ON_png, BinaryData::minus_ON_pngSize), 1.0, juce::Colours::transparentWhite, 0.0);
    }
}

void Guitar_ampAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    InputVolume_knob.setBounds(58, 131, 50, 50);

    Bass_knob.setBounds(171, 147, 50, 50);
    Mid_knob.setBounds(228, 147, 50, 50);
    Treble_knob.setBounds(285, 147, 50, 50);
    
    Threshold_knob.setBounds(374, 147, 50, 50);
    Comp_knob.setBounds(435, 147, 50, 50);

    Plus_button.setBounds(488, 112, 21, 16);
    Minus_button.setBounds(509, 129, 21, 16);

    Power_button.setBounds(649, 25, 25, 25);
    Cab_button.setBounds(593, 25, 25, 25);
 
    MasterVolume_knob.setBounds(583, 131, 50, 50);
}

void Guitar_ampAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &Cab_button) 
    {
        Cab_buttonClicked();
    }
    else if(button == &Power_button)
    {
        Power_buttonClicked();
    }
    else if (button == &Plus_button)
    {
        Plus_buttonClicked();
    }
    else if (button == &Minus_button)
    {
        Minus_buttonClicked();
    }
}

void Guitar_ampAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &InputVolume_knob)
    {
        audioProcessor.ampSim.setInputVolume(slider->getValue());
    }
    else if (slider == &Bass_knob)
    {
        audioProcessor.ampSim.setBassVolume(slider->getValue());
    }
    else if (slider == &Mid_knob)
    {
        audioProcessor.ampSim.setMidVolume(slider->getValue());
    }
    else if (slider == &Treble_knob)
    {
        audioProcessor.ampSim.setTrebleVolume(slider->getValue());
    }
    else if (slider == &Threshold_knob)
    {
        audioProcessor.ampSim.setThreshold(slider->getValue());
    }
    else if (slider == &Comp_knob)
    {
        audioProcessor.ampSim.setGainAbove(slider->getValue());
    }
    else if (slider == &MasterVolume_knob)
    {
        audioProcessor.ampSim.setMasterVolume(slider->getValue());
    }
}

void Guitar_ampAudioProcessorEditor::Cab_buttonClicked()
{
    if (audioProcessor.ampSim.getCabState() == 0)
    {
        audioProcessor.ampSim.setCabState(1);
    }
    else
    {
        audioProcessor.ampSim.setCabState(0);
    }
    repaint();
}

void Guitar_ampAudioProcessorEditor::Power_buttonClicked()
{
    if (audioProcessor.ampSim.getAmpState() == 0)
    {
        audioProcessor.ampSim.setAmpState(1);
    }
    else
    {
        audioProcessor.ampSim.setAmpState(0);
    }
    repaint();
}

void Guitar_ampAudioProcessorEditor::Plus_buttonClicked()
{
    if (audioProcessor.ampSim.getPlus() == 0)
    {
        audioProcessor.ampSim.setPlus(1);
    }
    else
    {
        audioProcessor.ampSim.setPlus(0);
    }
    repaint();
}

void Guitar_ampAudioProcessorEditor::Minus_buttonClicked()
{
    if (audioProcessor.ampSim.getMinus() == 0)
    {
        audioProcessor.ampSim.setMinus(1);
    }
    else
    {
        audioProcessor.ampSim.setMinus(0);
    }
    repaint();
}
