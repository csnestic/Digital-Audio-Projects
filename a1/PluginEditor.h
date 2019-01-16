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
class Assignment1AudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, public ComboBox::Listener, public Button::Listener
{
public:
    Assignment1AudioProcessorEditor (Assignment1AudioProcessor&);
    ~Assignment1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void comboBoxChanged(ComboBox*) override;
	void sliderValueChanged(Slider*) override;
	void buttonClicked(Button*) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Assignment1AudioProcessor& processor;

	Slider arpSlider;
	Slider octSlider;
	Slider durSlider;
	Slider durIndexSlider;
	Slider repeatIndexSlider;

	ComboBox comOrder;
	
	Label label;
	Label octLabel;
	Label versionLabel;
	Label orderLabel;
	Label durLabel;
	Label durSliderLabel;
	Label repeatIndexLabel;

	TextButton arpHint;
	TextButton octHint;
	TextButton orderHint;
	TextButton durHint;
	TextButton repeatedHint;

	ToggleButton repeat;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Assignment1AudioProcessorEditor)
};
