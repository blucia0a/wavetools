sync1=/tmp/sync1
sync2=/tmp/sync2

mkfifo $sync1; 
mkfifo $sync2; 

wave.pl -wave tri -freq 90 | tee /tmp/sync1 > /tmp/sync2 &

sync=$!

trap "echo \"Shutting down sync wave $sync\"; \
      kill $sync; echo \"Removing sync pipe\"; \
      rm /tmp/sync1; rm /tmp/sync2"\
      SIGINT SIGHUP SIGTERM

echo "Sync wave is $sync"

lpf.pl -cutoff 500 -resonance 1.5 -cutoffmod <(wave.pl -freq 1 -wave tri) -in <(mix.pl -in1 <(wave.pl -wave sin -freq 655 -amp 0.6 -freqmod /tmp/sync1) \
         -in2 <(wave.pl -wave sin -freq 660 -amp 0.6 -freqmod /tmp/sync2) )  | play.sh

