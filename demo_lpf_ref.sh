#!/bin/bash

  ./mix.pl \
    -in1 <(./mix.pl \
              -in1 <(./wave.pl -freq 840 -amp 0.5) \
              -in2 <(./wave.pl -freq 830 -amp 0.5))  \
    -in2 <(./mix.pl \
              -in1 <(./wave.pl -freq 520 -amp 0.5) \
              -in2 <(./wave.pl -freq 500 -amp 0.5))  \
| ./play.sh

