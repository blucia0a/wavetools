#!/bin/bash

env_p=/tmp/envgen
mkfifo $env_p

basspad_p=/tmp/basspad
mkfifo $basspad_p;

wave.pl -wave sin -freq 420 -amp 0.35 -ampmod /tmp/envgen  > $basspad_p &
basspad=$!

trap "echo \"Shutting down. basspad $basspad\"; \
      kill $basspad; \
      echo \"Removing pipes\"; \
      rm /tmp/envgen; rm /tmp/basspad;"\
      SIGINT SIGHUP SIGTERM

echo "syncs" 
echo "bass: $basspad"
echo "high: $highpad"


synth.pl -in /tmp/basspad | play.sh &
syn=$!

echo "a1d.2s.8r.1"
env.pl -amp 1.0 -sus 0.5 -attack 1.0 -decay 0.2 -sustain 0.8 -release 0.1 > $env_p &
e=$!
wait $e

kill $syn
wait $syn

kill $basspad
wait $basspad

rm $env_p
rm $basspad_p
