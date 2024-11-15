#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    // Decay Slider and label
    decaySlider.setSliderStyle (juce::Slider::SliderStyle::Rotary);
    addAndMakeVisible (decaySlider);
    decayLabel.setText ("Decay", juce::dontSendNotification);
    addAndMakeVisible (decayLabel);
    decayLabel.setColour (juce::Label::textColourId, juce::Colours::azure);

    // Gain Slider and label
    gainSlider.setSliderStyle (juce::Slider::SliderStyle::Rotary);
    addAndMakeVisible (gainSlider);
    gainLabel.setText ("Gain", juce::dontSendNotification);
    addAndMakeVisible (gainLabel);

    // Wet/Dry Slider and label
    wetDrySlider.setSliderStyle (juce::Slider::SliderStyle::Rotary);
    wetDrySlider.setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::blue);
    addAndMakeVisible (wetDrySlider);
    wetDryLabel.setText ("Wet/Dry", juce::dontSendNotification);
    addAndMakeVisible (wetDryLabel);

    // Low cut Slider and label
    lowCutSlider.setSliderStyle (juce::Slider::SliderStyle::Rotary);
    addAndMakeVisible (lowCutSlider);
    lowCutLabel.setText ("Low Cut Frequency", juce::dontSendNotification);
    addAndMakeVisible (lowCutLabel);

    // high cut slider and label
    highCutSlider.setSliderSnapsToMousePosition (juce::Slider::SliderStyle::Rotary);
    addAndMakeVisible (highCutSlider);
    highCutLabel.setText ("High Cut Frequency", juce::dontSendNotification);
    addAndMakeVisible (highCutLabel);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 400);
}

PluginEditor::~PluginEditor()
{
}

void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::purple);

    auto area = getLocalBounds();
    g.setColour (juce::Colours::black);
    g.setFont (16.0f);
}

void PluginEditor::resized()
{
    // layout the positions of your child components here
    auto area = getLocalBounds();
    

    decaySlider.setBounds (JUCE_LIVE_CONSTANT (150), JUCE_LIVE_CONSTANT (200), JUCE_LIVE_CONSTANT (100), JUCE_LIVE_CONSTANT (100));
    decayLabel.setBounds (JUCE_LIVE_CONSTANT (150), JUCE_LIVE_CONSTANT (300), JUCE_LIVE_CONSTANT (100), JUCE_LIVE_CONSTANT (30));
}
