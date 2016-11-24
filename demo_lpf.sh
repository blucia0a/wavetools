#!/bin/bash

./lpf.pl -in \
  <(./mix.pl \
    -in1 <(./mix.pl \
              -in1 <(./wave.pl -freq 840 -amp 0.5) \
              -in2 <(./wave.pl -freq 830 -amp 0.5))  \
    -in2 <(./mix.pl \
              -in1 <(./wave.pl -freq 520 -amp 0.5) \
              -in2 <(./wave.pl -freq 500 -amp 0.5))  \
  ) \
  -cutoff 840.0 -resonance 1.1 \
| ./play.sh

