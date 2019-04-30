#!/bin/bash

lpf.pl -in \
  <(mix.pl \
    -in1 <(mix.pl \
              -in1 <(wave.pl -wave sin  -freqmod <(wave.pl -wave sin  -freq 0.1) -freq 440 -amp 0.35) \
              -in2 <(wave.pl -wave sin  -ampmod <(wave.pl -wave sin  -freq 0.19) -freq 420 -amp 0.35))  \
    -in2 <(mix.pl \
              -in1 <(wave.pl -wave sin  -freqmod <(wave.pl -wave sin  -freq 0.1 -freqmod <(wave.pl -wave tri -freq 0.05)) -freq 220 -amp 0.35) \
              -in2 <(wave.pl -wave sin  -ampmod <(wave.pl -wave sin  -freq 0.23) -freq 210 -amp 0.35))  \
  ) \
  -cutoff 400.0 -resonance 1.4 -cutoffmod <(wave.pl -wave tri -freq 0.15) \
| play.sh

