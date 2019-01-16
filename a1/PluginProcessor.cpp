/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Assignment1AudioProcessor::Assignment1AudioProcessor()
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
	addParameter(speed = new AudioParameterFloat("speed", "Arpeggiator Speed", 0.0, 1.0, 0.5));
	addParameter(order = new AudioParameterFloat("order", "Arpeggiator Pattern", 0, 2, 0));
	addParameter(octaves = new AudioParameterFloat("octaves", "Arpeggiator Octaves", 1, 11, 1));
	addParameter(repeatIndex = new AudioParameterFloat("repeati", "Arpeggiator Repeated Note", 0, 9, 0));
	addParameter(durationIndex = new AudioParameterFloat("durationi", "Arpeggiator Expanded Note", 0, 9, 0));
	addParameter(duration = new AudioParameterFloat("duration", "Arpeggiator Duration of Expanded Note", 1.0, 10.0, 1.0));
	addParameter(repeat = new AudioParameterBool("repeat", "Repeat Notes",false));
}

Assignment1AudioProcessor::~Assignment1AudioProcessor()
{
}

//==============================================================================
const String Assignment1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Assignment1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Assignment1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Assignment1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Assignment1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Assignment1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Assignment1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Assignment1AudioProcessor::setCurrentProgram (int index)
{
}

const String Assignment1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Assignment1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Assignment1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	notes.clear();
	currentNote = 0;
	lastNoteValue = -1;
	time = 0.0;
	rate = static_cast<float> (sampleRate);
}

void Assignment1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Assignment1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Assignment1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midi)
{
	// the audio buffer in a midi effect will have zero channels!
	jassert(buffer.getNumChannels() == 0);

	// however we use the buffer to get timing information
	auto numSamples = buffer.getNumSamples();

	MidiMessage msg;
	int ignore;



	for (MidiBuffer::Iterator it(midi); it.getNextEvent(msg, ignore);)
	{
		
			if (msg.isNoteOn())
			{
				for (int i = 0; i < floor(*octaves); i++)
				{
					if (notes.indexOf((msg.getNoteNumber() + (12 * i)) % 128) == -1)
					{
						notes.add((msg.getNoteNumber() + (12 * i)) % 128);
						if (*repeat && !notes.isEmpty() && *order == 2 && repeatedNote > 0)
						{
							if (repeatedNote != (msg.getNoteNumber() + (12 * i)) % 128)
							{
								notes.add(repeatedNote);
							}
						}
					}
				}
			}
			else if (msg.isNoteOff())
			{
				for (int i = 0; i < floor(*octaves); i++)
				{
					notes.remove(notes.indexOf((msg.getNoteNumber() + (12 * i)) % 128));
					if (*repeat && !notes.isEmpty() && *order == 2 )
					{
						if (repeatedNote != (msg.getNoteNumber() + (12 * i)) % 128)
						{
							notes.remove(notes.indexOf(repeatedNote));
							notes.remove(notes.indexOf(repeatedNote));
							notes.remove(notes.indexOf(repeatedNote));
						}
					}
				}
			}
	}

	repeatedNote = -1;

	if (floor(*order) <= 1)
	{
		notes.sort();
	}

	
	

	midi.clear();
	if (floor(*repeatIndex) < notes.size())
	{
		repeatedNote = notes[floor(*repeatIndex)];
			
	}

	// get note duration
	auto noteDuration = static_cast<int> (std::ceil(rate * 0.25f * (0.1f + (1.0f - (*speed)))));
	if (floor(*durationIndex) < notes.size())
	{
		if (notes.size() > 0 && currentNote == floor(*durationIndex))
		{
			noteDuration = static_cast<int> (std::ceil(rate * 0.25f * (0.1f + (1.0f - (*speed))))) * *duration;
		}
	}

	if ((time + numSamples) >= noteDuration)
	{

		
		auto offset = jmax(0, jmin((int)(noteDuration - time), numSamples - 1));

		if (lastNoteValue > 0)
		{
			midi.addEvent(MidiMessage::noteOff(1, lastNoteValue), offset);
			lastNoteValue = -1;
		}

		if (notes.size() > 0)
		{
			if (floor(*order) == 0 || floor(*order) == 2)
			{
				currentNote = (currentNote + 1) % notes.size();
			}
			else if (floor(*order) == 1)
			{
				currentNote = (((currentNote - 1) % notes.size()) + notes.size()) % notes.size(); 
			}
	
			lastNoteValue = notes[currentNote];
			midi.addEvent(MidiMessage::noteOn(1, lastNoteValue, (uint8)127), offset);
			if (notes.size() >= 0)
			{
				for(int n: notes){
					DBG(n);
				}
				DBG(*duration);
				DBG("Done!!!!---------------------------------------------------");
			}
		}

	}

	time = (time + numSamples) % noteDuration;
}

//==============================================================================
bool Assignment1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Assignment1AudioProcessor::createEditor()
{
    return new Assignment1AudioProcessorEditor (*this);
}

//==============================================================================
void Assignment1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Assignment1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Assignment1AudioProcessor();
}
