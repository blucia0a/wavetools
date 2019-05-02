#!/bin/bash

#deep bass thrum
s1=/tmp/s1
mkfifo $s1

synth.pl \
-in <(mix.pl \
  -in1 <(noise.pl) \
  -in2 <(wave.pl -wave sin -freq 100 -freqmod <(wave.pl -wave sin -freq 110)) \
  -mixmod <(wave.pl -wave sin -freq 50) \
) > $s1 &

#high 
hi=/tmp/hi
mkfifo $hi

synth.pl \
-in <(mix.pl \
  -mixmod <(wave.pl -wave sin -freq 8) \
  -in1 <(noise.pl) \
  -in2 <(mix.pl \
    -in1 <(wave.pl -wave sin -freq 400 -freqmod <(wave.pl -wave sin -freq 410)) \
    -in2 <(wave.pl -wave sin -freq 600 -freqmod <(wave.pl -wave sin -freq 610)) \
  )
) > $hi &

#high sin with some noise, slow freqmod
#tril=/tmp/tril
#mkfifo $tril

#synth.pl -in <(wave.pl \
#    -wave sin -freq 600 \
#    -freqmod <(wave.pl -wave tri -freq 0.1) \
#    -freqmoddepth 1.0 \
#) > $tril &

#slow on/off as freq fluctuates on tril ("tril beat")
trilb=/tmp/trilb
mkfifo $trilb

synth.pl \
  -ampmod <(wave.pl -wave sqr -amp 1.0 -freq 0.5) \
  -in <(wave.pl \
    -wave sin -freq 600 \
    -freqmod <(wave.pl -wave tri -freq 0.1) \
    -freqmoddepth 1.0 \
) > $trilb &


#noise vs. s1 slow square swap
s2=/tmp/s2
mkfifo $s2

synth.pl \
-in <(lpf.pl -cutoff 300 -resonance 1.4 \
  -in <(mix.pl \
    -in1 <(noise.pl -amp 0.75) \
    -in2 $s1 \
    -mixmod <(wave.pl -wave sqr -freq 0.4) \
  ) \
) > $s2 &


#noise vs. hi faster square swap
s3=/tmp/s3
mkfifo $s3

synth.pl \
-in <(lpf.pl -cutoff 500 -resonance 1.4 \
  -in <(mix.pl \
    -in1 <(noise.pl -amp 0.5) \
    -in2 $hi \
    -mixmod <(wave.pl -wave sqr -freq 0.8) \
  ) \
) > $s3 &

synth.pl -in <(mix.pl -in1 $s2 -in2 $s3) | play.sh
#synth.pl -in <(mix.pl \
#  -in1 <(mix.pl -in1 $s2 -in2 $s3 ) \
#  -in2 $trilb \
#) | play.sh

killall perl
rm $s1
rm $s2
rm $s3
rm $hi
#rm $tril
rm $trilb
