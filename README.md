# Digital-Audio-Projects
Various projects to produce sample audio plugins utilizing JUCE as well as a simple text game with audio added via OpenAL 

### A1 
The JUCE arpeggiator tutorial located at [Tutorial](https://docs.juce.com/master/tutorial_plugin_examples.html#tutorial_plugin_examples_arpeggiator).

Using the original tutorial with only the speed parameter, this version adds multiple patterns, options to span multiple octaves, repeating notes, and optional increased note durations.

### A2
A plugin to create audio delay setup in a similar way to the arpeggiator, when MIDI notes are entered the plugin has settings for the delay time, volume of the initial sound (dry setting), volume of each repeated delay (wet setting), as well as a feedback setting (how much the repeated signals will drop after each repeat).

### A3

A3 requires OpenAL and various audio files that are not uploaded. The intent of A3 was to take an existing simple text-based game and add audio to it using OpenAL. Original code is sourced from [Source](https://www.daniweb.com/programming/software-development/code/234254/neat-text-based-rpg-c-console#).
