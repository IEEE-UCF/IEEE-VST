/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IEEEVSTAudioProcessorEditor::IEEEVSTAudioProcessorEditor (IEEEVSTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 400);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(-48.0, 0.0);
    gainSlider.setValue(-1.0);
    gainSlider.addListener(this);

    addAndMakeVisible(gainSlider);
}

IEEEVSTAudioProcessorEditor::~IEEEVSTAudioProcessorEditor()
{
}

//==============================================================================
void IEEEVSTAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void IEEEVSTAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    gainSlider.setBounds(getLocalBounds());
}

void IEEEVSTAudioProcessorEditor::sliderValueChanged(juce::Slider * slider)
{
    if (slider == &gainSlider) 
    {
        audioProcessor.rawVolume = pow(10, gainSlider.getValue() / 20);
    }
}