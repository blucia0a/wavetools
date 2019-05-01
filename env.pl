#!/usr/bin/perl

use warnings;
use strict;
use Getopt::Long;

my $SampRate = 44100;
my $SampSize = 2;

my $attack = 1.0;
my $decay = 1.0;
my $sustain = 1.0;
my $release = 1.0;
my $amp = 1.0;
my $sus = 1.0;
my $attackS = $SampRate;
my $decayS = $SampRate;
my $sustainS = $SampRate;
my $releaseS = $SampRate;

GetOptions ("srate=i"  => \$SampRate,
            "ssize=i"  => \$SampSize,
            "amp=f"    => \$amp,
            "sus=f"    => \$sus,
            "attack=f"    => \$attack,
            "decay=f"    => \$decay,
            "sustain=f"    => \$sustain,
            "release=f"    => \$release)
or die("Error in command line arguments\n");

binmode(STDOUT,":raw") || die "cannot binmode STDOUT";

$attackS = $attack * $SampRate;
$decayS = $decay * $SampRate;
$sustainS = $sustain * $SampRate;
$releaseS = $release * $SampRate;

my $maxA = $amp * 65536;
my $susA = $sus * 65536;
my $samp = 0;
for(my $i = 0; $i < $attackS; $i++){
  $samp = $i / $attackS * $maxA; 
  print pack 'S', ($samp); 
}
for(my $i = 0; $i < $decayS; $i++){
  $samp = $maxA - ($i / $decayS) * ($maxA - $susA);
  print pack 'S', ($samp); 
}
for(my $i = 0; $i < $sustainS; $i++){
  $samp = $susA;
  print pack 'S', ($samp); 
}
for(my $i = 0; $i < $releaseS; $i++){
  $samp = $susA - (($i / $releaseS) * $susA);
  print pack 'S', ($samp); 
}





