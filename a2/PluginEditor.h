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
class A2AudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    A2AudioProcessorEditor (A2AudioProcessor&);
    ~A2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void sliderValueChanged(Slider*) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    A2AudioProcessor& processor;

	Slider delSlider;
	Slider drySlider;
	Slider wetSlider;
	Slider feedSlider;

	Label delayLabel;
	Label dryLabel;
	Label wetLabel;
	Label feedLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (A2AudioProcessorEditor)
};
