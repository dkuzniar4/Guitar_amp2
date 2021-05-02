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

    addAndMakeVisible(InputVolume_knob);
    InputVolume_knob.setSliderStyle(juce::Slider::Rotary);
    InputVolume_knob.setRotaryParameters(3.92, 8.63, true);
    InputVolume_knob.setRange(0.0, 2.0, 0.01);
    InputVolume_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    InputVolume_knob.setPopupDisplayEnabled(true, false, this);
    InputVolume_knob.setTextValueSuffix(" Input volume");
    InputVolume_knob.setValue(audioProcessor.inputVolume);
    InputVolume_knob.addListener(this);

    addAndMakeVisible(Bass_knob);
    Bass_knob.setSliderStyle(juce::Slider::Rotary);
    Bass_knob.setRotaryParameters(3.92, 8.63, true);
    Bass_knob.setRange(0.00, 20.0, 0.01);
    Bass_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Bass_knob.setPopupDisplayEnabled(true, false, this);
    Bass_knob.setTextValueSuffix(" Bass");
    Bass_knob.setValue(audioProcessor.bass_filter.getVolume());
    Bass_knob.addListener(this);

    addAndMakeVisible(Mid_knob);
    Mid_knob.setSliderStyle(juce::Slider::Rotary);
    Mid_knob.setRotaryParameters(3.92, 8.63, true);
    Mid_knob.setRange(0.00, 20.0, 0.01);
    Mid_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Mid_knob.setPopupDisplayEnabled(true, false, this);
    Mid_knob.setTextValueSuffix(" Mid");
    Mid_knob.setValue(audioProcessor.mid_filter.getVolume());
    Mid_knob.addListener(this);

    addAndMakeVisible(Treble_knob);
    Treble_knob.setSliderStyle(juce::Slider::Rotary);
    Treble_knob.setRotaryParameters(3.92, 8.63, true);
    Treble_knob.setRange(0.00, 20.0, 0.01);
    Treble_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Treble_knob.setPopupDisplayEnabled(true, false, this);
    Treble_knob.setTextValueSuffix(" Treble");
    Treble_knob.setValue(audioProcessor.treble_filter.getVolume());
    Treble_knob.addListener(this);

    addAndMakeVisible(Threshold_knob);
    Threshold_knob.setSliderStyle(juce::Slider::Rotary);
    Threshold_knob.setRotaryParameters(3.92, 8.63, true);
    Threshold_knob.setRange(0.01, 1.0, 0.01);
    Threshold_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Threshold_knob.setPopupDisplayEnabled(true, false, this);
    Threshold_knob.setTextValueSuffix(" Threshold");
    Threshold_knob.setValue(audioProcessor.sat.getThreshold());
    Threshold_knob.addListener(this);

    addAndMakeVisible(Comp_knob);
    Comp_knob.setSliderStyle(juce::Slider::Rotary);
    Comp_knob.setRotaryParameters(3.92, 8.63, true);
    Comp_knob.setRange(0.01, 1.0, 0.01);
    Comp_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    Comp_knob.setPopupDisplayEnabled(true, false, this);
    Comp_knob.setTextValueSuffix(" Comp");
    Comp_knob.setValue(audioProcessor.sat.getGainAbove());
    Comp_knob.addListener(this);

    addAndMakeVisible(MasterVolume_knob);
    MasterVolume_knob.setSliderStyle(juce::Slider::Rotary);
    MasterVolume_knob.setRotaryParameters(3.92, 8.63, true);
    MasterVolume_knob.setRange(0.00, 2.0, 0.01);
    MasterVolume_knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    MasterVolume_knob.setPopupDisplayEnabled(true, false, this);
    MasterVolume_knob.setTextValueSuffix(" Master volume");
    MasterVolume_knob.setValue(audioProcessor.masterVolume);
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

    setSize(1400, 500);
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

    if (audioProcessor.amp_state == 0)
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

    if (audioProcessor.cab_state == 0)
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

    if (audioProcessor.sat.getPlus() == 0)
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

    if (audioProcessor.sat.getMinus() == 0)
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
    InputVolume_knob.setBounds(107, 247, 127, 127);

    Bass_knob.setBounds(355, 311, 81, 81);
    Mid_knob.setBounds(460, 311, 81, 81);
    Treble_knob.setBounds(567, 311, 81, 81);
    
    Threshold_knob.setBounds(777, 300, 100, 100);
    Comp_knob.setBounds(892, 300, 100, 100);

    Plus_button.setBounds(840, 216, 49, 49);
    Minus_button.setBounds(888, 254, 49, 49);

    Power_button.setBounds(1298, 51, 49, 49);
    Cab_button.setBounds(1188, 51, 49, 49);
 
    MasterVolume_knob.setBounds(1155, 247, 127, 127);
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
        audioProcessor.inputVolume = slider->getValue();
    }
    else if (slider == &Bass_knob)
    {
        audioProcessor.bass_filter.setVolume(slider->getValue());
    }
    else if (slider == &Mid_knob)
    {
        audioProcessor.mid_filter.setVolume(slider->getValue());
    }
    else if (slider == &Treble_knob)
    {
        audioProcessor.treble_filter.setVolume(slider->getValue());
    }
    else if (slider == &Threshold_knob)
    {
        audioProcessor.sat.setThreshold(slider->getValue());
    }
    else if (slider == &Comp_knob)
    {
        audioProcessor.sat.setGainAbove(slider->getValue());
    }
    else if (slider == &MasterVolume_knob)
    {
        audioProcessor.masterVolume = slider->getValue();
    }
}

void Guitar_ampAudioProcessorEditor::Cab_buttonClicked()
{
    if (audioProcessor.cab_state == 0)
    {
        audioProcessor.cab_state = 1;
    }
    else
    {
        audioProcessor.cab_state = 0;
    }
    repaint();
}

void Guitar_ampAudioProcessorEditor::Power_buttonClicked()
{
    if (audioProcessor.amp_state == 0)
    {
        audioProcessor.amp_state = 1;
    }
    else
    {
        audioProcessor.amp_state = 0;
    }
    repaint();
}

void Guitar_ampAudioProcessorEditor::Plus_buttonClicked()
{
    if (audioProcessor.sat.getPlus() == 0)
    {
        audioProcessor.sat.setPlus(1);
    }
    else
    {
        audioProcessor.sat.setPlus(0);
    }
    repaint();
}

void Guitar_ampAudioProcessorEditor::Minus_buttonClicked()
{
    if (audioProcessor.sat.getMinus() == 0)
    {
        audioProcessor.sat.setMinus(1);
    }
    else
    {
        audioProcessor.sat.setMinus(0);
    }
    repaint();
}
