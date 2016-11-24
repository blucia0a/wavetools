#!/bin/bash

./lpf.pl -in \
  <(./mix.pl \
    -in1 <(./mix.pl \
              -in1 <(./wave.pl -lfo <(./wave.pl -freq 1) -freq 840 -amp 0.5) \
              -in2 <(./wave.pl -lfo <(./wave.pl -freq 10) -freq 830 -amp 0.5))  \
    -in2 <(./mix.pl \
              -in1 <(./wave.pl -lfo <(./wave.pl -freq 6) -freq 520 -amp 0.5) \
              -in2 <(./wave.pl -lfo <(./wave.pl -freq 7) -freq 500 -amp 0.5))  \
  ) \
  -cutoff 840.0 -resonance 1.2 \
| ./play.sh &

pid=$i

./lpf.pl -in \
  <(./mix.pl \
    -in1 <(./mix.pl \
              -in1 <(./wave.pl -lfo <(./wave.pl -freq 1) -freq 840 -amp 0.5) \
              -in2 <(./wave.pl -lfo <(./wave.pl -freq 10) -freq 830 -amp 0.5))  \
    -in2 <(./mix.pl \
              -in1 <(./wave.pl -lfo <(./wave.pl -freq 6) -freq 520 -amp 0.5) \
              -in2 <(./wave.pl -lfo <(./wave.pl -freq 7) -freq 500 -amp 0.5))  \
  ) \
  -cutoff 840.0 -resonance 1.2 \
| ./play.sh 

kill $pid;

