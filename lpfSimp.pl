#!/usr/bin/perl

use warnings;
use strict;
use Getopt::Long;

my $SampRate = 44100;
my $SampSize = 2;
my $IN1File = "";
my $amp = 1.0;

my @filter = (-0.00116417, -0.00139094, 0.00195951, 0.00293134, -0.00437535,
	      -0.00637313, 0.00902803, 0.01248116, -0.0169409, -0.02273977,
	       0.03045372, 0.04118039, -0.05729369, -0.08500841, 0.14720004,
	       0.45005217, 0.45005217, 0.14720004, -0.08500841, -0.05729369,
	       0.04118039, 0.03045372, -0.02273977, -0.0169409, 0.01248116,
	       0.00902803, -0.00637313, -0.00437535, 0.00293134, 0.00195951,
	      -0.00139094, -0.00116417);

my $numsamples = 32;
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

for(my $i = 0; $i < $numsamples; $i++){
  $sample[$i] = 0.0;
}
while(1){

  my $samp1raw;
  read($IN1, $samp1raw, $SampSize); #TODO
  my $samp1 = unpack "S", $samp1raw;

  #Move samples up by one in the buffer
  for(my $i = 0; $i < $numsamples-1; $i++){
    $sample[$i + 1] = $sample[$i];
  }
  $sample[0] = $samp1;
 
  my $out = 0.0; 
  for(my $i = 0; $i < $numsamples; $i++){
    $out += $sample[$i] * $filter[$i];
  }  

  print pack 'S', $out; 

}
