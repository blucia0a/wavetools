#!/bin/bash

env_p=/tmp/envgen
mkfifo $env_p

ectrl_p=/tmp/ectrl
mkfifo $ectrl_p

basspad_p=/tmp/basspad
mkfifo $basspad_p

lead_p=/tmp/lead
mkfifo $lead_p




echo "bass pad"
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
  -cutoff 400.0 -resonance 1.4 -cutoffmod <(wave.pl -wave tri -freq 0.15) > $basspad_p &
basspad=$!

echo "lead pad"
lpf.pl -in \
  <(mix.pl \
 \
 \
    -in1 <(mix.pl \
              -in1 <(wave.pl -wave sin  -freqmod <(wave.pl -wave sin  -freq 0.1) -freq 640 -amp 0.35) \
              -in2 <(wave.pl -wave sin  -ampmod <(wave.pl -wave sin  -freq 0.19) -freq 620 -amp 0.35))  \
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
                             -freq 420 \
                             -amp 0.35) \
                                        \
              -in2 <(wave.pl -wave sin  \
                             -ampmod <(wave.pl -wave sin \
                                               -freq 0.23) \
                             -freq 410 \
                             -amp 0.35)\
         )  \
  ) \
 \
 \
 \
  -cutoff 700.0 -resonance 1.4 -cutoffmod <(wave.pl -wave tri -freq 0.15) > $lead_p  &
lead=$!

synth.pl -amp 1.0 -in $basspad_p | play.sh &
syn1=$!

synth.pl -amp 1.0 -ampmod $env_p -in $lead_p | play.sh &
syn2=$!


trap "echo \"Shutting down. basspad $basspad\"; \
      kill $basspad $syn1 $syn2 $lead; \
      echo \"Removing pipes\"; \
      rm /tmp/envgen; rm /tmp/basspad; rm /tmp/ectrl; rm /tmp/lead; reset; exit"\
      SIGINT SIGHUP SIGTERM

sleep 5;

echo "env 1"
env.pl -oneshot -amp 1.0 -sus 0.7 -attack 0.1 -decay 2.0 -sustain 1.0 -release 0.1 > $env_p 
echo "waiting for env 1"

sleep 5;

echo "env 2"
env.pl -oneshot -amp 1.0 -sus 0.35 -attack 1.0 -decay 2.0 -sustain 1.0 -release 1.0 > $env_p 
echo "waiting for env 2"

#echo "starting keytrig"
#keytrig.pl > $ectrl_p
#echo "finished keytrig"

kill $syn1
wait $syn1

kill $syn2
wait $syn2

kill $basspad
wait $basspad

kill $lead
wait $lead

rm $ectrl_p
rm $env_p
rm $basspad_p
rm $lead_p
