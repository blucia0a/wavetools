Synsh - A synth shell
======================
#### Brandon Lucia 2016-2019

A minimalist modular synthesizer and audio processing sandbox. 

## Use
For now, synsh lacks end-user usability features and is primarily a library of
modules that can be stitched together to make fixed, compiled synthesis
pipelines.  The feature roadmap below outlines the plan for these usability
features.

The current system supports wavetable synthesis and has support for generating,
mixing, low-pass filtering, and outputting 16-bit PCM audio data. 

## Module List

#### Wave - wavetable synthesis module

#### Mix - two-input signal mixer

#### Mixn - (experimental) n-input signal mixer

#### Out - flexible buffering output module

#### LPFSimp - a simple low-pass filtering module

#### wavloader - not a module, but a RIFF WAV file loader to get wavetables for wave modules

## Developer Guide
The goal of this project is to build a flexible synthesizer from scratch with no library dependences.

The project has a generic module interface that supports reference to a derived module type and a generic `next()` function that returns the module's next sample.

Each module has a constructor that takes a module container pointer and a
specific module type pointer and returns a fully-formed module that can be used
by downstream code.  Constructors are specific to each module type and have names that end in \_new.



## Feature Roadmap
* control signal interfaces
* Trigger vs. continuous
* LFO module / Waves at <1Hz
* REPL support 
* PulseAudio output backend
* MIDI input handling
