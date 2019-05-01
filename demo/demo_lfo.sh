#!/bin/bash

basspad_p=/tmp/basspad
mkfifo $basspad_p;

highpad_p=/tmp/highpad
mkfifo $highpad_p;

lpf.pl -in \
  <(mix.pl \
 \
 \
    -in1 <(mix.pl \
              -in1 <(wave.pl -wave sin  -freqmod <(wave.pl -wave sin  -freq 0.1) -freq 440 -amp 0.35) \
              -in2 <(wave.pl -wave sin  -ampmod <(wave.pl -wave sin  -freq 0.19) -freq 420 -amp 0.35))  \
 \
 \
 \
    -in2 <(mix.pl \
              -in1 <(wave.pl -wave sin  \
                             -freqmod <(wave.pl -wave sin  \
                                                -freq 0.2 \
                                                -freqmod <(wave.pl -wave tri \
                                                                   -freq 0.05)\
                                       ) \
                             -freq 220 \
                             -amp 0.35) \
                                        \
              -in2 <(wave.pl -wave sin  \
                             -ampmod <(wave.pl -wave sin \
                                               -freq 0.23) \
                             -freq 210 \
                             -amp 0.35)\
         )  \
  ) \
 \
 \
 \
  -cutoff 400.0 -resonance 1.4 -cutoffmod <(wave.pl -wave tri -freq 0.15) > /tmp/basspad &
basspad=$!

mix.pl -in1 <(lpf.pl -in <(wave.pl -wave sin -freq 440 -amp 0.4 -freqmoddepth 1.0 -freqmod <(wave.pl -wave sin -freq 0.01 -freqmod <(wave.pl -wave tri -freq 0.1 ) -freqmoddepth 1.0 )) -cutoff 300 -resonance 1.4 ) \
-in2 <(wave.pl -wave sin -freq 600 -amp 0.35 -freqmoddepth 1.0 -freqmod <(wave.pl -wave sin -freq 0.007 -freqmod <(wave.pl -wave tri -freq 0.05 ) -freqmoddepth 1.0 )) > /tmp/highpad &
highpad=$!

trap "echo \"Shutting down. basspad $basspad highpad $highpad\"; \
      kill $basspad; \
      kill $highpad; echo \"Removing pipes\"; \
      rm /tmp/highpad; rm /tmp/basspad;"\
      SIGINT SIGHUP SIGTERM

echo "syncs" 
echo "bass: $basspad"
echo "high: $highpad"

synth.pl -in <(mix.pl -in1 /tmp/basspad -in2 /tmp/highpad) | play.sh
