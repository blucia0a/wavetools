ShYnth - A shell synth 
======================
#### Brandon Lucia 2016

A 16-bit, command-line, Unix-style, modular synthesizer.

Generate Audio!

`./wave.pl -wave tri -freq 440 -amp 0.5`

Generate Control signals!

`./wave.pl -wave tri -freq 10 -freqmod <(./wave -wave tri -freq 1)`

The output of each module is a stream of sample values between 0 and 65536 (16-bit INTMAX).
When a stream of samples is used as a modulation input, the module being modulated
uses the stream of samples as a scale factor between 0.0 and 1.0.

Use `sox` to make noise!  `play.sh` is a fixed command line for 16-bit, mono,
44100Hz audio. (Different bit-width, stereo, and variable audio rate coming soon).

`./wave.pl -wave tri -freq 440 -amp 0.5 | ./play.sh`


The main mechanism for patching modules is process redirection `<( ... )`, like

```./mix.pl -in1 <(./wave.pl -wave sin -freq 440 -amp 0.5) 
            -in2 <(./wave.pl -wave sin -freq 450 -amp 0.5)```

The main mechanism for mult-out support (i.e., for a sync'd clock) is a named pipe.

```bash

sync1=/tmp/sync1
sync2=/tmp/sync2

mkfifo $sync1
mkfifo $sync2

#Set up the mod mult -- this clock runs to sync1 and sync2
./wave.pl -wave tri -freq 90 | tee /tmp/sync1 > /tmp/sync2 &
sync=$!

#Prepare to cleanup the sync wave and pipes when Ctrl+c ends the mix below
trap "kill $sync; rm /tmp/sync1 /tmp/sync2"

#Route the mult outs to these two waves via sync1 and sync2
./mix.pl -in1 <(./wave.pl -wave sin -freq 655 -amp 0.6 -freqmod /tmp/sync1) 
         -in2 <(./wave.pl -wave sin -freq 660 -amp 0.6 -freqmod /tmp/sync2) | play.sh

```

Module List and Parameters
--------------------------
* `./mix.pl -in1 <(stream) -in2 <(stream)`
* `./wave.pl -wave [sin | tri] -freq <Hz> -amp (0.0 - 1.0) -freqmod <(stream) -ampmod <(stream)`
* `./lpf.pl -in <(stream) -cutoff <Hz> -resonance (0.4ish - 2.0ish) -cutoffmod <(stream)`
* `./amp.pl -in <(stream) -amp (0.0 - 1.0)`

TODO
----
* Add modulation to resonance 
* Add envelope generator 
* Add modulation depth parameter and center modulation on specified value
* Better support for modmult?
