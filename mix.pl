#!/usr/bin/perl

use warnings;
use strict;
use Getopt::Long;

my $SampRate = 44100;
my $SampSize = 2;

GetOptions ("srate=i"  => \$SampRate,
            "ssize=i"  => \$SampSize)    
or die("Error in command line arguments\n");

my $IN1File = $ARGV[0];
my $IN1;
open($IN1,'<', $IN1File);
binmode($IN1,":raw") || die "cannot binmode IN1";

my $IN2File = $ARGV[1];
my $IN2;
open($IN2,'<',$IN2File);
binmode($IN2,":raw") || die "cannot binmode IN2";

binmode(STDOUT,":raw") || die "cannot binmode STDOUT";

my $i = 0;
while(1){

  my $samp1raw;
  read($IN1, $samp1raw, $SampSize); #TODO
  my $samp1 = unpack "S", $samp1raw;

  my $samp2raw;
  read($IN2, $samp2raw, $SampSize);
  my $samp2 = unpack "S", $samp2raw;

  print pack 'S', (($samp1 + $samp2)/2); #linear mix

}
