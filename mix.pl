#!/usr/bin/perl

use warnings;
use strict;
use Getopt::Long;
use Fcntl;

my $SampRate = 44100;
my $SampSize = 2;
my $MMFile = "";
my $IN1File = "";
my $IN2File = "";

GetOptions ("srate=i"  => \$SampRate,
            "ssize=i"  => \$SampSize,
            "mixmod=s" => \$MMFile,
            "in1=s"     => \$IN1File,
            "in2=s"     => \$IN2File)    
or die("Error in command line arguments\n");

my $IN1;
open($IN1,'<', $IN1File);
binmode($IN1,":raw") || die "cannot binmode IN1";

my $IN2;
open($IN2,'<',$IN2File);
binmode($IN2,":raw") || die "cannot binmode IN2";

my $MM;
if($MMFile ne ""){
  sysopen($MM,$MMFile,O_RDONLY);
  binmode($MM,":raw") || die "cannot open mixmod";
}

my $MixFactor = 0.5; #Amount of in1, 1.0 - amount of in2

binmode(STDOUT,":raw") || die "cannot binmode STDOUT";

my $i = 0;
while(1){

  my $samp1raw;
  read($IN1, $samp1raw, $SampSize); #TODO
  my $samp1 = unpack "S", $samp1raw;

  my $samp2raw;
  read($IN2, $samp2raw, $SampSize);
  my $samp2 = unpack "S", $samp2raw;

  if( $MMFile ne "" ){

    if(eof($MM)){
      close($MM);
      sysopen($MM,$MMFile,O_RDONLY);
      binmode($MM,":raw") || die "cannot reinit MM pipe $!";
    }

    my $mmraw;
    read($MM, $mmraw, $SampSize); 
    my $mmval = unpack "S", $mmraw;
    $mmval = 0 if !defined $mmval;
    $MixFactor = $mmval / 65535;
  }

  print pack 'S', ($samp1*$MixFactor + $samp2*(1.0 - $MixFactor)); #linear mix

}
