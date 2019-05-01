#!/bin/bash

env_p=/tmp/envgen
mkfifo $env_p

ectrl_p=/tmp/ectrl
mkfifo $ectrl_p

basspad_p=/tmp/basspad
mkfifo $basspad_p


wave.pl -wave sin -freq 420 -amp 0.75 -ampmod $env_p  > $basspad_p &
basspad=$!

synth.pl -in /tmp/basspad | play.sh &
syn=$!

echo "a1d.2s.8r.1"
env.pl -ctrl $ectrl_p -amp 1.0 -sus 0.5 -attack 1.0 -decay 0.2 -sustain 0.8 -release 0.1 > $env_p &
en=$!
echo "setup env a1d.2s.8r.1"

trap "echo \"Shutting down. basspad $basspad\"; \
      kill $basspad $en $syn; \
      echo \"Removing pipes\"; \
      rm /tmp/envgen; rm /tmp/basspad; rm /tmp/ectrl; reset; exit"\
      SIGINT SIGHUP SIGTERM

echo "starting keytrig"
keytrig.pl > $ectrl_p
echo "finished keytrig"

kill $en
wait $en

kill $syn
wait $syn

kill $basspad
wait $basspad

rm $ectrl_p
rm $env_p
rm $basspad_p
