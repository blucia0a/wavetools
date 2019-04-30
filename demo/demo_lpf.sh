#!/bin/bash

synth.pl -in \
  <(lpf.pl -cutoffmod <(wave.pl -wave sin -freq 1 -amp 0.3) -cutoff 840 -in \
    <(mix.pl \
      -in1 <(wave.pl -wave sin -freq 1200  -amp 0.5) \
      -in2 <(wave.pl -wave sin -freq 120 -amp 0.5) \
     )  \
   ) \
| play.sh
