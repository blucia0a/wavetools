 lpf.pl -cutoff 400 -cutoffmod <(wave.pl -wave tri -freq 10 -freqmod <(wave.pl -wave sin -freq 2) ) -resonance 2.0 -in <(mix.pl -in1 <( wave.pl -wave sin -freq 610 -amp 1.0 -freqmod <(wave.pl -wave tri -freq 100) ) -in2 <(wave.pl -wave tri -freq 600 -amp 1.0) )  | play.sh