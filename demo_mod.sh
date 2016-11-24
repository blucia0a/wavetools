./lpf.pl -cutoff 300 -resonance 1.8 -in \
         <( ./wave.pl -wave tri -freq 640 -amp 1.0 \
                      -freqmod <(./wave.pl -wave tri -freq 30 \
                                           -freqmod <(./wave.pl -wave tri -freq 10) ) \
                      -ampmod <(./wave.pl -wave tri -freq 9) ) \
| ./play.sh
