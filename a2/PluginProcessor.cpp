/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
A2AudioProcessor::A2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	addParameter(delayLn = new AudioParameterFloat("delayLn", "Delay Length", 0.0, 2.0, 0.5));
	addParameter(dryVol = new AudioParameterFloat("dryVol", "Dryness", 0.0, 1.0, 0.5));
	addParameter(wetVol = new AudioParameterFloat("wetVol", "Wetness", 0.0, 1.0, 0.5));
	addParameter(feedback = new AudioParameterFloat("feedback", "Feedback", 0.0, 1.0, 0.5));

}

A2AudioProcessor::~A2AudioProcessor()
{
}

//==============================================================================
const String A2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool A2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool A2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool A2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double A2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int A2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int A2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void A2AudioProcessor::setCurrentProgram (int index)
{
}

const String A2AudioProcessor::getProgramName (int index)
{
    return {};
}

void A2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void A2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	delayBufferLn = (int)(sampleRate*2.0);
	delayBuffer.setSize(2, delayBufferLn);
	delayBuffer.clear();

	// Set length to at least 1 in case of 0 input
	if (delayBufferLn < 1)
		delayBufferLn = 1;

	*delayLn = 0.5;
	globalDelayWriteIn = 0;

}

void A2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool A2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void A2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();
	int numSamples = buffer.getNumSamples();

	// Keeping track in the loop
	int localDelayReadIn = 0;
	int localDelayWriteIn = 0;

	int channel;
	// for each channel process the delay
	for (channel = 0; channel < totalNumInputChannels; ++channel) {
		// Get write pointers for circular delay buffer and main buffer
		float* delayData = delayBuffer.getWritePointer(channel);
		float* channelData = buffer.getWritePointer(channel);

		// New Read from end of old write
		float delayInSamples = (*delayLn) * (delayBufferLn / 2.0);
		globalDelayReadIn = fmodf(((float)globalDelayWriteIn - delayInSamples + (float)delayBufferLn), delayBufferLn);

		// Copying globals for local use
		localDelayReadIn = globalDelayReadIn;
		localDelayWriteIn = globalDelayWriteIn;

		int i;
		// Determine the output
		for (i = 0; i < numSamples; ++i) {
			const float input = channelData[i];
			float output = 0.0;


			output = ((*dryVol) * input + (*wetVol) * delayData[localDelayReadIn]);

			// Update the delay with the feedback
			delayData[localDelayWriteIn] = input + (delayData[localDelayReadIn] * (*feedback));

			if (++localDelayReadIn >= delayBufferLn)
				localDelayReadIn = 0;
			if (++localDelayWriteIn >= delayBufferLn)
				localDelayWriteIn = 0;

			channelData[i] = output;
		}

	}
	globalDelayReadIn = localDelayReadIn;
	globalDelayWriteIn = localDelayWriteIn;
}

//==============================================================================
bool A2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* A2AudioProcessor::createEditor()
{
    return new A2AudioProcessorEditor (*this);
}

//==============================================================================
void A2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void A2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new A2AudioProcessor();
}
