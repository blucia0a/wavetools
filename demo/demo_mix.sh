#!/bin/bash

mix.pl \
  -in1 <(mix.pl    \
            -in1 <(mix.pl \
                      -in1 <(wave.pl -wave sin  -freq 100 -amp 0.5) \
                      -in2 <(wave.pl -wave sin  -freq 190 -amp 0.5))     \
            -in2 <(mix.pl    \
                      -in1 <(wave.pl -wave sin  -freq 280 -amp 0.5) \
                      -in2 <(wave.pl -wave sin  -freq 370 -amp 0.5))) \
  -in2 <(mix.pl \
            -in1 <(wave.pl -wave sin  -freq 460 -amp 0.5) \
            -in2 <(wave.pl -wave sin  -freq 550 -amp 0.5))  \
| play.sh

