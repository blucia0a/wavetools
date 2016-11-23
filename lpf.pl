#!/usr/bin/perl

use warnings;
use strict;
use Math::Trig;
use Getopt::Long;
my $pi = 3.1415926535897;

my $SampRate = 44100;
my $SampSize = 2;
my $IN1File = "";

my $cutoff = 440;

#Resonance varies from 0.1 to 1.4 (i.e., sqrt(2))
my $resonance = 1.4;

GetOptions ("cutoff=f" => \$cutoff,    
            "resonance=f" => \$resonance,
            "srate=i"  => \$SampRate,
            "ssize=i" => \$SampSize,
            "in=s" => \$IN1File) 
or die("Error in command line arguments\n");

my $IN1;
open($IN1,'<', $IN1File);
binmode($IN1,":raw") || die "cannot binmode IN1";


binmode(STDOUT,":raw") || die "cannot binmode STDOUT";

my @prevIn = (0,0);
my @prevOut = (0,0);
my $a1;
my $a2;
my $a3;
my $b1;
my $b2;

my $c = 1.0 / tan($pi * $cutoff / $SampRate);

$a1 = 1.0 / ( 1.0 + $resonance * $c + $c * $c);
$a2 = 2* $a1;
$a3 = $a1;
$b1 = 2.0 * ( 1.0 - $c * $c) * $a1;
$b2 = ( 1.0 - $resonance * $c + $c * $c) * $a1;


my $i = 0;
while(1){

  my $samp1raw;
  read($IN1, $samp1raw, $SampSize); #TODO
  my $in = unpack "S", $samp1raw;

  my $out = $a1 * $in + $a2 * $prevIn[0] + $a3 * $prevIn[1] - $b1 * $prevOut[0] - $b2 * $prevOut[1];

  $prevOut[1] = $prevOut[0];
  $prevOut[0] = $out;

  $prevIn[1] = $prevIn[0];
  $prevIn[0] = $in;

  print pack 'S', $out; 

}
