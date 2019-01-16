/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
A2AudioProcessorEditor::A2AudioProcessorEditor (A2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	addAndMakeVisible(delSlider);
	addAndMakeVisible(drySlider);
	addAndMakeVisible(wetSlider);
	addAndMakeVisible(feedSlider);
	addAndMakeVisible(delayLabel);
	addAndMakeVisible(dryLabel);
	addAndMakeVisible(wetLabel);
	addAndMakeVisible(feedLabel);

	delSlider.setRange(0.0, 2.0, 0.001);
	delSlider.setValue(0.5);
	delSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
	delayLabel.setText("Delay Time", dontSendNotification);

	drySlider.setRange(0.0, 1.0, 0.001);
	drySlider.setValue(0.5);
	drySlider.setSliderStyle(Slider::LinearVertical);
	drySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100,25);
	dryLabel.setText("Dry", dontSendNotification);

	wetSlider.setRange(0.0, 1.0, 0.001);
	wetSlider.setValue(0.5);
	wetSlider.setSliderStyle(Slider::LinearVertical);
	wetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
	wetLabel.setText("Wet", dontSendNotification);

	feedSlider.setRange(0.0, 1.0, 0.001);
	feedSlider.setValue(0.5);
	feedSlider.setSliderStyle(Slider::Rotary);
	feedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
	feedLabel.setText("Feedback %", dontSendNotification);

	delSlider.addListener(this);
	drySlider.addListener(this);
	wetSlider.addListener(this);
	feedSlider.addListener(this);


    setSize(400, 500);
}

A2AudioProcessorEditor::~A2AudioProcessorEditor()
{
}

//==============================================================================
void A2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	
	g.setColour(Colours::white);
	g.setFont(20.0f);
}

void A2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..


	delSlider.setBounds(10, 30, getBounds().getWidth() - 20, 40);
	delayLabel.setBounds(getBounds().getWidth() / 2 - 40, 75, 100, 20);
	
	drySlider.setBounds(getBounds().getWidth() - 150, 120, 50, getBounds().getHeight() / 1.5);
	dryLabel.setBounds(getBounds().getWidth() - 145, getBounds().getHeight() / 1.5 + 120, 100, 20);
	
	wetSlider.setBounds(getBounds().getWidth() - 100, 120, 50, getBounds().getHeight() / 1.5);
	wetLabel.setBounds(getBounds().getWidth() - 95, getBounds().getHeight() / 1.5 + 120, 100, 20);
	
	feedSlider.setBounds(10, getBounds().getHeight() / 2, 200, 200);
	feedLabel.setBounds(60, getBounds().getHeight() / 2 + 200, 100, 20);
}

void A2AudioProcessorEditor::sliderValueChanged(Slider* slider) {
	auto& params = processor.getParameters();
	for (auto p : params) {
		if (auto* param = dynamic_cast<AudioParameterFloat*> (p)) {
			if (param->paramID == "delayLn" && slider == &delSlider) {
				param->setValueNotifyingHost(slider->getValue()/2);
			}
			else if (param->paramID == "wetVol" && slider == &wetSlider) {
				param->setValueNotifyingHost(slider->getValue());
			}
			else if (param->paramID == "dryVol" && slider == &drySlider) {
				param->setValueNotifyingHost(slider->getValue());
			}
			else if (param->paramID == "feedback" && slider == &feedSlider) {
				param->setValueNotifyingHost(slider->getValue());
			}
		}
	}
}