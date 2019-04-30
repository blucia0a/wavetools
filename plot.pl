#!/usr/bin/perl

use warnings;
use strict;
use Getopt::Long;

my $SampRate = 44100;
my $SampSize = 2;
my $IN1File = "";
my $amp = 1.0;
my $numsamps = 0;
my $subsamp = 0;

GetOptions ("srate=i"  => \$SampRate,
            "ssize=i"  => \$SampSize,
            "amp=f"    => \$amp,
            "numsamps=n"    => \$numsamps,
            "subsamp=n"    => \$subsamp,
            "in=s"     => \$IN1File)
or die("Error in command line arguments\n");

my $IN1;
open($IN1,'<', $IN1File);
binmode($IN1,":raw") || die "cannot binmode IN1";


#binmode(STDOUT,":raw") || die "cannot binmode STDOUT";

my $subsamp_cur = 0;
if($numsamps == 0){

  while(1){
  
    my $samp1raw;
    read($IN1, $samp1raw, $SampSize); #TODO
    my $samp1 = unpack "S", $samp1raw;

    $subsamp_cur++;
    if($subsamp_cur >= $subsamp){
  
      print "".$samp1."\n"; 
      $subsamp_cur = 0;

    }
  
  }

}else{

  while($numsamps > 0){
  
    my $samp1raw;
    read($IN1, $samp1raw, $SampSize); #TODO
    my $samp1 = unpack "S", $samp1raw;
  
    $numsamps--;
    $subsamp_cur++;
    if($subsamp_cur >= $subsamp){
  
      print "".$samp1."\n"; 
      $subsamp_cur = 0;

    }
  
  }

}
