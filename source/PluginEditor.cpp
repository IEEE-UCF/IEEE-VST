#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processorRef (p), valueTreeState(vts)
{
    
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colour (0xff444137));
    getLookAndFeel().setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff444137));
    getLookAndFeel().setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff9f937d));
    getLookAndFeel().setColour (juce::Slider::textBoxTextColourId, juce::Colour (0xff444137));
    getLookAndFeel().setColour (juce::Label::textColourId, juce::Colour (0xff444137));
    getLookAndFeel().setColour (juce::ToggleButton::textColourId, juce::Colour (0xff444137));
    getLookAndFeel().setColour (juce::ToggleButton::tickColourId, juce::Colour (0xff444137));
    getLookAndFeel().setColour (juce::ToggleButton::tickDisabledColourId, juce::Colour (0xff444137));
    getLookAndFeel().setColour (juce::TextButton::buttonColourId, juce::Colour (0xff444137));
    getLookAndFeel().setColour (juce::TextButton::textColourOnId, juce::Colour (0xffE0D7C6));
    
    // Gain Slider and Label
    gainSlider.setSliderStyle (juce::Slider::SliderStyle::Rotary);
    gainAttachment.reset (new SliderAttachment (valueTreeState, "gain", gainSlider));
    addAndMakeVisible (gainSlider);

    gainLabel.setText ("Gain", juce::dontSendNotification);
    addAndMakeVisible (gainLabel);

    // Cutoff low frequency slider and label + attachment
    addAndMakeVisible (cutoffFrequencySliderLow);
    cutoffFrequencySliderLow.setSliderStyle (juce::Slider::SliderStyle::Rotary);
    cutoffFrequencyAttachmentLow.reset (new SliderAttachment (vts, "cutoff_frequency_low", cutoffFrequencySliderLow));

    addAndMakeVisible (cutoffFrequencyLabelLow);
    cutoffFrequencyLabelLow.setText ("Cutoff Frequency Low", juce::dontSendNotification);

    // Cutoff high frequency slider and label + attachment
    addAndMakeVisible (cutoffFrequencySliderHigh);
    cutoffFrequencySliderHigh.setSliderStyle (juce::Slider::SliderStyle::Rotary);
    cutoffFrequencyAttachmentHigh.reset (new SliderAttachment (vts, "cutoff_frequency_high", cutoffFrequencySliderHigh));

    addAndMakeVisible (cutoffFrequencyLabelHigh);
    cutoffFrequencyLabelHigh.setText ("Cutoff Frequency High", juce::dontSendNotification);

    openButton.setButtonText ("Open IR File");
    openButton.onClick = [this] { openButtonClicked(); };

    processorRef.root = juce::File::getSpecialLocation (juce::File::userDesktopDirectory);
    //formatManager.registerBasicFormats();

    addAndMakeVisible (irName);

    juce::ignoreUnused (processorRef);


    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
}

PluginEditor::~PluginEditor()
{
}

void PluginEditor::openButtonClicked()
{
    chooser = std::make_unique<juce::FileChooser> ("Choose a WAV/AIFF/MP3", processorRef.root, "*.wav;*.aiff;*.mp3", true, false, nullptr);

    chooser->launchAsync (juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
        [this] (const juce::FileChooser& fc) {
            auto file = fc.getResult();
            if (file.existsAsFile())
            {
                processorRef.savedFile = file;
                processorRef.root = file.getParentDirectory().getFullPathName();

                processorRef.convolution.reset();
                processorRef.convolution.loadImpulseResponse (file, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
                irName.setText (file.getFileName(), juce::dontSendNotification);
            }
        });
}


void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colour (0xffE0D7C6));

    g.setFont (16.0f);
}

void PluginEditor::resized()
{
    // layout the positions of your child components here
    auto r = getLocalBounds();
    
    const auto openButtonX = getWidth() * JUCE_LIVE_CONSTANT (0.075);
    const auto openButtonY = getHeight() * JUCE_LIVE_CONSTANT (0.34);
    const auto openButtonWidth = getWidth() * JUCE_LIVE_CONSTANT (0.2);
    const auto openButtonHeight = getHeight() * JUCE_LIVE_CONSTANT (0.3);

    const auto irNameYOffset = JUCE_LIVE_CONSTANT (30);

    openButton.setBounds (openButtonX, openButtonY, openButtonWidth, openButtonHeight);
    irName.setBounds (openButtonX, openButtonY + irNameYOffset, openButtonWidth, openButtonHeight + irNameYOffset + 50);

    auto knobRect = r;

    auto gainRect = knobRect.removeFromRight (paramWidth);
    gainSlider.setBounds (gainRect);
    gainLabel.setBounds (gainRect.removeFromBottom (buttonHeight));

    auto highFilterRect = knobRect.removeFromRight (paramWidth);
    cutoffFrequencySliderHigh.setBounds (highFilterRect);
    cutoffFrequencyLabelHigh.setBounds (highFilterRect.removeFromBottom (buttonHeight));

    auto lowFilterRect = knobRect.removeFromRight (paramWidth);
    cutoffFrequencySliderLow.setBounds (lowFilterRect);
    cutoffFrequencyLabelLow.setBounds (lowFilterRect.removeFromBottom (buttonHeight));

}
