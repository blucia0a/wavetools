#!/usr/bin/perl

use warnings;
use strict;
use Getopt::Long;

my $SampRate = 44100;
my $SampSize = 2;
my $IN1File = "";
my $amp = 1.0;
my $out = 1.0;

my $sampleSize = 100.0;
my $sampleWeight= 1.0/$sampleSize;
my $numSamps = 0;
my @sample;

GetOptions ("srate=i"  => \$SampRate,
            "ssize=i"  => \$SampSize,
            "amp=f"    => \$amp,
            "in=s"     => \$IN1File)
or die("Error in command line arguments\n");

my $IN1;
open($IN1,'<', $IN1File);
binmode($IN1,":raw") || die "cannot binmode IN1";


binmode(STDOUT,":raw") || die "cannot binmode STDOUT";

my $i = 0;
for(my $i = 0; $i < 100; $i++){
  $sample[$i] = 0.0;
}
while(1){

  my $samp1raw;
  read($IN1, $samp1raw, $SampSize); #TODO
  my $samp1 = unpack "S", $samp1raw;

  &addSamp($samp1);
 
  $out = 0.0; 
  #FIR filter with coefficients [1/3, 1, 1/2] and 8-bit resolution for coeffs
  for(my $i = 0; $i < $sampleSize; $i++){
    $out = $out + $sample[$i] * $sampleWeight;
  }  

  print pack 'S', $out; 
  #print "".$out."\n"; 

}

sub addSamp{

  #Move samples up by one in the buffer
  for($i = 0; $i < $sampleSize-1; $i++){
    $sample[$i + 1] = $sample[$i];
  }
  $sample[0] = $_[0];

}
