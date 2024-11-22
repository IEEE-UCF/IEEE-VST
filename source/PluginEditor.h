#pragma once

#include "PluginProcessor.h"
//#include "BinaryData.h"
#include "melatonin_inspector/melatonin_inspector.h"

//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor (PluginProcessor&);
    ~PluginEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:


    juce::Slider decaySlider;
    juce::Label decayLabel;

    juce::Slider gainSlider;
    juce::Label gainLabel;
    
    juce::Slider wetDrySlider;
    juce::Label wetDryLabel;

    juce::Slider lowCutSlider;
    juce::Label lowCutLabel;

    juce::Slider highCutSlider;
    juce::Label highCutLabel;

    juce::Image IEEELogo;
    juce::ImageComponent IEEELogoComponent;

    juce::Label vapoverbLabel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor& processorRef;
    std::unique_ptr<melatonin::Inspector> inspector;
    juce::TextButton inspectButton { "Inspect the UI" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
