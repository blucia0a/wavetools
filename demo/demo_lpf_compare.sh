#!/bin/bash

mix.pl \
    -in1 <(mix.pl \
              -in1 <(wave.pl -wave sin -freq 1260  -amp 0.5) \
              -in2 <(wave.pl -wave sin -freq 1100 -amp 0.5))  \
    -in2 <(mix.pl \
              -in1 <(wave.pl -wave sin -freq 120 -amp 0.5) \
              -in2 <(wave.pl -wave sin -freq 100 -amp 0.5))  \
| play.sh

