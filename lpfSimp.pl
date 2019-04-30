#!/usr/bin/perl

use warnings;
use strict;
use Getopt::Long;

my $SampRate = 44100;
my $SampSize = 2;
my $IN1File = "";
my $amp = 1.0;

my $numsamples = 40;
my @filter = (0.5,0.2,0.1,0.1,0.1);
my @sample;
my @conv;

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


  #print "S: [ ";
  #for(my $i = 0; $i < $#sample+1; $i++){
  #  print "".$sample[$i]." "
  #}
  #print "]\n";


  #|--------$slen + 2*($flen-1)--------|
  #|--$flen--|                           
  #|0|0|0|0|*|  0                            
  #  |0|0|0|*|*|  1                           
  #    |0|0|*|*|*|  2                         
  #      |0|*|*|*|*|  3                       
  #        |*|*|*|*|*|  4  
  #          |*|*|*|*|*|  5
  #            |*|*|*|*|*|  6
  #              |*|*|*|*|*|  7
  #                |*|*|*|*|*|  8
  #                  |*|*|*|*|*|  9
  #                    |*|*|*|*|0| 10
  #                      |*|*|*|0|0| 11
  #                        |*|*|0|0|0|  12
  #                          |*|0|0|0|0|  13
  #        |0|1|2|3|4|5|6|7|8|9|
  #        |------$slen--------|
  #        |old ----------> new| 
  #
  #|$flen-1|-------------------|$flen-1|
  my @filtered = (); # |@filtered| = $slen + $flen - 1
  for(my $fpos = 0 - $#filter; $fpos <= $#sample; $fpos++){

      my $elemout = 0;

      for(my $i = 0; $i < $#filter+1; $i++){

        if($fpos + $i >= 0 &&  
           $fpos + $i < $#sample){

          $elemout = $elemout + $sample[$fpos + $i] * $filter[$i];

        }

      }

      push @filtered, $elemout; 

  } 

  my $out = $filtered[$#filter];
  #print "F: [ ";
  #for(my $i = 0; $i < $#filtered+1; $i++){
  #  print "".$filtered[$i]." "
  #}
  #print "]\n";

  print pack 'S', $out; 

}
