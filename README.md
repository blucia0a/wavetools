ShYnth - A shell synth 
======================
#### Brandon Lucia 2016

A 16-bit, command-line, Unix-style, modular synthesizer.

Generate Audio!

`./wave.pl -wave tri -freq 440 -amp 0.5`

Generate Control signals!

`./wave.pl -wave tri -freq 10 -freqmod <(./wave -wave tri -freq 1)`

The output of each module is a stream of sample values between 0 and 65536 (16-bit INTMAX).

Use `sox` to make noise!  `play.sh` is a fixed command line for 16-bit, mono,
44100Hz audio. (Different bit-width, stereo, and variable audio rate coming soon).

`./wave.pl -wave tri -freq 440 -amp 0.5 | ./play.sh`


The main mechanism for patching modules is process redirection `<( ... )`, like

```./mix.pl -in1 <(./wave.pl -wave sin -freq 440 -amp 0.5) 
            -in2 <(./wave.pl -wave sin -freq 450 -amp 0.5)```

Module List and Parameters
--------------------------
* `./mix.pl -in1 <(stream) -in2 <(stream)`
* `./wave.pl -wave [sin | tri] -freq <Hz> -amp (0.0 - 1.0) -freqmod <(stream) -ampmod <(stream)`
* `./lpf.pl -in <(stream) -cutoff <Hz> -resonance (0.4ish - 2.0ish) -cutoffmod <(stream)`
* `./amp.pl -in <(stream) -amp (0.0 - 1.0)`
