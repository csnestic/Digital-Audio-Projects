/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Assignment1AudioProcessorEditor::Assignment1AudioProcessorEditor (Assignment1AudioProcessor& p)
    :	AudioProcessorEditor (&p), 
		processor (p)
{
	addAndMakeVisible(arpSlider);
	addAndMakeVisible(label);
	addAndMakeVisible(comOrder);
	addAndMakeVisible(octSlider);
	addAndMakeVisible(octLabel);
	addAndMakeVisible(versionLabel);
	addAndMakeVisible(arpHint);
	addAndMakeVisible(octHint);
	addAndMakeVisible(repeat);
	addAndMakeVisible(orderLabel);
	addAndMakeVisible(orderHint);
	addAndMakeVisible(durHint);
	addAndMakeVisible(durIndexSlider);
	addAndMakeVisible(durLabel);
	addAndMakeVisible(durSlider);
	addAndMakeVisible(durSliderLabel);
	addAndMakeVisible(repeatedHint);
	addAndMakeVisible(repeatIndexLabel);
	addAndMakeVisible(repeatIndexSlider);

	arpSlider.setRange(0.0, 1.0);
	arpSlider.setValue(0.5);
	arpSlider.setSliderStyle(Slider::Rotary);
	arpSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
	label.setText("Arpeggiator Speed:", dontSendNotification);
	orderLabel.setText("Arpeggiator Order:", dontSendNotification);
	
	comOrder.addItem("Ascending", 1);
	comOrder.addItem("Descending", 2);
	comOrder.addItem("Non-Ordered", 3);
	comOrder.setSelectedId(1);

	octSlider.setRange(1, 11, 1);
	octSlider.setSliderStyle(Slider::IncDecButtons);
	octSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 30, 25);
	octLabel.setText("Number of Octaves to Play:", dontSendNotification);

	repeatIndexSlider.setRange(1, 10, 1);
	repeatIndexSlider.setSliderStyle(Slider::IncDecButtons);
	repeatIndexSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 30, 25);
	repeatIndexLabel.setText("Select index of a repeated note:", dontSendNotification);

	durIndexSlider.setRange(1, 10, 1);
	durIndexSlider.setSliderStyle(Slider::IncDecButtons);
	durIndexSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 30, 25);
	durLabel.setText("Select index of a note:", dontSendNotification);

	durSlider.setRange(1.0, 10.0,0.5);
	durSlider.setValue(1);
	durSlider.setSliderStyle(Slider::Rotary);
	durSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 15);
	durSliderLabel.setText("Duration of the selected note:", dontSendNotification);

	arpHint.setButtonText("?");
	octHint.setButtonText("?");
	orderHint.setButtonText("?");
	durHint.setButtonText("?");
	repeatedHint.setButtonText("?");

	repeat.setButtonText("Allow Repeated Notes");

	arpSlider.addListener(this);
	comOrder.addListener(this);
	octSlider.addListener(this);
	arpHint.addListener(this);
	octHint.addListener(this);
	repeat.addListener(this);
	orderHint.addListener(this);
	repeatedHint.addListener(this);
	repeatIndexSlider.addListener(this);
	durIndexSlider.addListener(this);
	durSlider.addListener(this);
	durHint.addListener(this);

	versionLabel.setText(String("{version}  made by Haider Al-Tahan")
		.replace("{version}", SystemStats::getJUCEVersion()),
		dontSendNotification);

	setSize(500, 500);


}

Assignment1AudioProcessorEditor::~Assignment1AudioProcessorEditor()
{
}

//==============================================================================
void Assignment1AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

	int borderWidth = getLocalBounds().getWidth() / 2;
	int borderHeight = getLocalBounds().getHeight() / 2;
	
	auto bounds = getLocalBounds();
	bounds.setWidth(borderWidth);
	bounds.setHeight(borderHeight);
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 2; x++) {
			bounds.setPosition(borderWidth*x,borderHeight*y);
			auto centralArea = bounds.toFloat().reduced(10.0f);
			g.drawRoundedRectangle(centralArea, 5.0f, 3.0f);
		}
	}
    /*g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("main!", getLocalBounds(), Justification::centred, 1);*/
}

void Assignment1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	
	//Center Text
	auto area = getLocalBounds();
	area.setWidth(getLocalBounds().getWidth());
	area.setHeight(20);
	area.setPosition(getLocalBounds().getWidth()/2-125, getLocalBounds().getHeight() / 2 - 10);
	versionLabel.setBounds(area);

	//Top Left
	label.setBounds(10,10, getLocalBounds().getWidth() / 2, 30);
	arpHint.setBounds(getLocalBounds().getWidth() / 2 - 35,15,20,20);
	arpSlider.setBounds(10, label.getBounds().getBottom(), getLocalBounds().getWidth() / 2, 180);

	//Top Right
	auto topRight = getLocalBounds().getWidth() / 2 + 20;
	octLabel.setBounds(topRight, 10, getLocalBounds().getWidth() / 2, 30);
	octHint.setBounds(getLocalBounds().getWidth() -35, 15, 20, 20);
	octSlider.setBounds(topRight, octLabel.getBounds().getBottom()+5, getLocalBounds().getWidth() / 2 - 35, 25);
	orderLabel.setBounds(topRight, octSlider.getBounds().getBottom() + 10, getLocalBounds().getWidth() / 2 - 37, 30);
	orderHint.setBounds(getLocalBounds().getWidth() - 35, octSlider.getBounds().getBottom() + 15, 20,20);
	comOrder.setBounds(topRight, orderLabel.getBounds().getBottom(), getLocalBounds().getWidth() / 2 - 37, 30);

	//Botton Left
	auto buttomLeft = 10;
	durLabel.setBounds(buttomLeft, getLocalBounds().getHeight() / 2+10, getLocalBounds().getWidth() / 2 - 35, 30);
	durHint.setBounds(getLocalBounds().getWidth() / 2 - 35, getLocalBounds().getHeight() / 2+15, 20, 20);
	durIndexSlider.setBounds(buttomLeft+5, durLabel.getBounds().getBottom()+5, getLocalBounds().getWidth() / 2 - 30, 25);
	durSliderLabel.setBounds(buttomLeft, durIndexSlider.getBounds().getBottom()+5, getLocalBounds().getWidth() / 2 - 35, 30);
	durSlider.setBounds(buttomLeft,durSliderLabel.getBounds().getBottom(), getLocalBounds().getWidth() / 2, 125);

	//Bottom Right
	auto bottomRight = getLocalBounds().getWidth() / 2 + 10;
	repeat.setBounds(bottomRight, getLocalBounds().getHeight() / 2 + 10, getLocalBounds().getWidth() / 2 - 37, 30);
	repeatedHint.setBounds(getLocalBounds().getWidth() - 35, getLocalBounds().getHeight() / 2 + 15, 20,20);
	repeatIndexLabel.setBounds(bottomRight, repeat.getBounds().getBottom()+10, getLocalBounds().getWidth() / 2 - 35, 30);
	repeatIndexSlider.setBounds(bottomRight+5, repeatIndexLabel.getBounds().getBottom() + 5, getLocalBounds().getWidth() / 2 - 30, 25);
}

void Assignment1AudioProcessorEditor::comboBoxChanged(ComboBox* order)
{
	auto& params = processor.getParameters();
	for (auto p : params)
	{
		if (auto* param =
			dynamic_cast<AudioParameterFloat*> (p))
		{
			if (param->paramID == "order" && order == &comOrder) {
				param->setValueNotifyingHost
					((float)(order->getSelectedId()) / 3.00);
				if (order->getSelectedId() != 3)
				{
					repeat.setToggleState(false, dontSendNotification);
				}
			}
		}
	}
}

void Assignment1AudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	auto& params = processor.getParameters();
	for (auto p : params)
	{
		if (auto* param =
			dynamic_cast<AudioParameterFloat*> (p))
		{
			if (param->paramID == "speed" && slider == &arpSlider) {
				param->setValueNotifyingHost
				(slider->getValue());
			} else if (param->paramID == "octaves" && slider == &octSlider) {
				param->setValueNotifyingHost
				(slider->getValue() / 11);
			}else if (param->paramID == "repeati" && slider == &repeatIndexSlider) {
				param->setValueNotifyingHost
				(slider->getValue() / 10);
			}else if (param->paramID == "durationi" && slider == &durIndexSlider) {
				param->setValueNotifyingHost
				(slider->getValue() / 10);
			}else if (param->paramID == "duration" && slider == &durSlider) {
				param->setValueNotifyingHost
				(slider->getValue()/10);
			}
		}
	}
}

void Assignment1AudioProcessorEditor::buttonClicked(Button * button)
{
	if (button == &arpHint)                                                  
	{
		AlertWindow::AlertIconType icon = AlertWindow::NoIcon;
		icon = AlertWindow::InfoIcon;       
		AlertWindow::showMessageBoxAsync(icon, "Arpeggiator",
			"An arpeggiator is a very basic real-time sequencer designed to take a chord as an input and turn it into an arpeggio.\nYou can Adjust the speed of arpeggiator with the slider below.",
			"OK");
	}
	else if (button == &orderHint)
	{
		AlertWindow::AlertIconType icon = AlertWindow::NoIcon;
		icon = AlertWindow::InfoIcon;
		AlertWindow::showMessageBoxAsync(icon, "Arpeggiator Order",
			"The ascending option play the notes in an ascending order.\n\nThe decending option play the notes in an decending order.\n\nThe 'Non-ordered' option plays the notes in the order they are played.",
			"OK");
	}
	else if (button == &octHint)
	{
		AlertWindow::AlertIconType icon = AlertWindow::NoIcon;
		icon = AlertWindow::InfoIcon;
		AlertWindow::showMessageBoxAsync(icon, "Octaves",
			"An Octave is the interval between one musical pitch and another with half or double its frequency.\nYou can choose the number of octaves to play on top of the selected node with the adjuster below.\nThere are approximitly 11 octaves in total, hence, the maximum you can go up to before repeating the same note is 11.",
			"OK");
	}else if (button == &repeatedHint)
	{
		AlertWindow::AlertIconType icon = AlertWindow::NoIcon;
		icon = AlertWindow::InfoIcon;
		AlertWindow::showMessageBoxAsync(icon, "Repeated Notes",
			"This feature allows you to repeat a single note. For instance, A,B,C would produce A,B,A,C,A.\n\nYou can also select which note you would like to repeat based on it's index. For instance, if you wanted to repeat B in A,B,C then you would select index 2, hence, producing A,B,B,C,B.\n\nThis feature is enabled by checking the box 'Allow Repeated Notes'",
			"OK");
	}else if (button == &durHint)
	{
		AlertWindow::AlertIconType icon = AlertWindow::NoIcon;
		icon = AlertWindow::InfoIcon;
		AlertWindow::showMessageBoxAsync(icon, "Extending Note Duration",
			"This feature extends the duration of a selected note.\n\nFirst you need to select the node index, that is, if you would like to use extend A in A,B,C then the index of A is 1.\n\nAfter selecting the index, you can adjust the duration of the note. The adjusted value is multiplied by the typical note duration. For instance, A,B,C is a note sequence with A and B have similar note duration `d`. If we wanted to expand the duration of C by double of `d` then we just adjust the slider to 2.0.\n\n Hence, it is calculated by `d` x Slider Value.",
			"OK");
	}
	else if (button == &repeat)
	{
		auto& params = processor.getParameters();
		for (auto p : params)
		{
			if (auto* param =
				dynamic_cast<AudioParameterBool*> (p))
			{
				if (param->paramID == "repeat") {
					param->setValueNotifyingHost(button->getToggleState());
					if (button->getToggleState())
					{
						comOrder.setSelectedId(3);
					}
				}
			}
		}
	}
}

