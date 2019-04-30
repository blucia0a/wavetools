#!/bin/bash

plot.pl -numsamps 1000 \
-in <(lpfSimp.pl -in \
        <(mix.pl \
            -in1 <(wave.pl -wave sin -freq 860  -amp 0.5) \
            -in2 <(wave.pl -wave sin -freq 120 -amp 0.5))  \
     ) \
| plot.sh

