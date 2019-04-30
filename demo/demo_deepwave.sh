#!/bin/bash

wave1=/tmp/wave1
wave2=/tmp/wave2
wave3=/tmp/wave3
wave4=/tmp/wave4


mkfifo $wave1;
mkfifo $wave2;
mkfifo $wave3;
mkfifo $wave4;

wave.pl -wave sin -freq 220 > $wave1 & 
wavep1=$!
wave.pl -wave sin -freq 440 > $wave2 &
wavep2=$!
wave.pl -wave sin -freq 660 > $wave3 &
wavep3=$!
wave.pl -wave sin -freq 880 > $wave4 &
wavep4=$!

trap "echo \"Shutting down. basspad $waves\"; \
      kill $wavep1; \
      kill $wavep2; \
      kill $wavep3; \
      kill $wavep4; \
      echo \"Removing pipes\"; \
      rm /tmp/wave*;"\
      SIGINT SIGHUP SIGTERM

echo "syncs" 
echo "waves: $wavep1"
echo "waves: $wavep2"
echo "waves: $wavep3"
echo "waves: $wavep4"

synth.pl -in <(mix.pl -in1 <(mix.pl -in1 $wave1 -in2 $wave2) -in2 <(mix.pl -in1 $wave3 -in2 $wave4) ) | play.sh
