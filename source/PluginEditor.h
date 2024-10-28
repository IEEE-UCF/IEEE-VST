#pragma once

#include "PluginProcessor.h"
#include "BinaryData.h"
#include "melatonin_inspector/melatonin_inspector.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor (PluginProcessor&);
    PluginEditor (PluginProcessor& p, juce::AudioProcessorValueTreeState& vts);
    ~PluginEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    enum {
        paramWidth = 200,
        paramHeight = 300,
        buttonHeight = 150
    };

private:

    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Slider gainSlider;
    juce::Label gainLabel;
    std::unique_ptr<SliderAttachment> gainAttachment;

    juce::Slider cutoffFrequencySliderLow;
    std::unique_ptr<SliderAttachment> cutoffFrequencyAttachmentLow;
    juce::Label cutoffFrequencyLabelLow;

    juce::Slider cutoffFrequencySliderHigh;
    std::unique_ptr<SliderAttachment> cutoffFrequencyAttachmentHigh;
    juce::Label cutoffFrequencyLabelHigh;

    juce::TextButton openButton;
    void openButtonClicked();

    juce::AudioPluginFormatManager formatManager;
    std::unique_ptr<juce::FileChooser> chooser;

    juce::Label irName;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor& processorRef;
    std::unique_ptr<melatonin::Inspector> inspector;
    juce::TextButton inspectButton { "Inspect the UI" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
