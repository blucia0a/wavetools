sync1=/tmp/sync1
sync2=/tmp/sync2
sync3=/tmp/sync3
lpfg=/tmp/lpfgen

mkfifo $sync1; 
mkfifo $sync2; 
mkfifo $sync3; 
mkfifo $lpfg; 

wave.pl -wave sin -freq 1 | tee /tmp/sync1 | tee /tmp/sync2 > /tmp/sync3 &
sync=$!


lpf.pl -cutoff 800 \
                -cutoffmod /tmp/sync3 \
                -in <(mix.pl \
                        -in1 <(wave.pl -wave sin -freq 655 -amp 0.6 -freqmod /tmp/sync1 -freqmoddepth 0.75) \
                        -in2 <(wave.pl -wave sin -freq 660 -amp 0.6 -freqmod /tmp/sync2) \
                     ) > /tmp/lpfgen &
lpfgen=$!
        


trap "echo \"Shutting down sync wave $sync\"; \
      kill $sync; echo \"Removing sync pipe\"; \
      kill $lpfgen; echo \"Removing lpfgenpipe\"; \
      rm /tmp/sync1; rm /tmp/sync2; rm /tmp/sync3; rm /tmp/lpfgen;"\
      SIGINT SIGHUP SIGTERM

echo "Sync wave is $sync"

synth.pl -in <(
mix.pl \
  -in1 <(wave.pl -wave sin -freq 630 -amp 0.6 -freqmod <(wave.pl -wave sin -freq 2) -freqmoddepth 0.5) \
  -in2 /tmp/lpfgen  \
)\
| play.sh

