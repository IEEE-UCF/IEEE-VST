/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JuceHeader.h"

//==============================================================================
IEEEVSTAudioProcessorEditor::IEEEVSTAudioProcessorEditor (IEEEVSTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    setVisible(true);
    enableResizeability();
}

/**
 Enables the gui editor to be resizeable with resize limits to not throw an error when the size is accidentally resized to 0
 */
void IEEEVSTAudioProcessorEditor::enableResizeability() {
    // get an instance of the desktop
    juce::Desktop& desktop = juce::Desktop::getInstance();
    // get an instance of the displays
    juce::Displays displays = desktop.getDisplays();
    // get the main display
    const juce::Displays::Display* display = displays.getPrimaryDisplay();
    // get the max and min widths and heights
    int maxScreenHeight = display->totalArea.getHeight();
    int maxScreenWidth = display->totalArea.getWidth();
    int minScreenHeight = maxScreenHeight / 32;
    int minScreenWidth = maxScreenWidth / 32;
    //std::cout << "height " << maxScreenHeight << std::endl << "width " << maxScreenWidth << std::endl;
    // set the resize limits using the values above
    setResizeLimits(minScreenWidth, minScreenHeight, maxScreenWidth, maxScreenHeight);
    //std::cout << "scale factor" << display->scale << std::endl;
    // enable resizeability
    setResizable(true, true);

}

IEEEVSTAudioProcessorEditor::~IEEEVSTAudioProcessorEditor()
{
}

//==============================================================================
void IEEEVSTAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void IEEEVSTAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
