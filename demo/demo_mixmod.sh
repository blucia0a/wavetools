#!/bin/bash

eg_p=/tmp/eg
mkfifo $eg_p

ctrl_p=/tmp/ctrl
mkfifo $ctrl_p


synth.pl -ampmod $eg_p -in <(lpf.pl -in <(mix.pl -mixmod <(wave.pl -amp 1.0 -freq 600 -wave sin) -in1 <(noise.pl -amp 0.2) -in2 <(wave.pl -wave sin -freq 220 -amp 0.50 -freqmod <(wave.pl -wave tri -amp 0.9 -freq 0.01) -freqmoddepth 0.9)) -cutoff 100 -resonance 1.4) | play.sh &
syn=$!


env.pl -amp 1.0 -sus 0.4 -attack 0.2 -decay 0.1 -sustain 0.5 -release 0.75 -ctrl $ctrl_p > $eg_p &
en=$!


trap "echo \"Shutting down.\"; \
      kill $en $syn ; \
      echo \"Removing pipes\"; \
      rm /tmp/ctrl; rm /tmp/eg; reset; exit"\
      SIGINT SIGHUP SIGTERM

keytrig.pl > $ctrl_p

kill $syn
kill $en

wait $syn
wait $en
