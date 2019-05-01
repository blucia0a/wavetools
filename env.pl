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
my $CTRLFile = "";

GetOptions ("ctrl=s"   => \$CTRLFile, 
            "amp=f"    => \$amp,
            "sus=f"    => \$sus,
            "attack=f"    => \$attack,
            "decay=f"    => \$decay,
            "sustain=f"    => \$sustain,
            "release=f"    => \$release)
or die("Error in command line arguments\n");

my $CTRL;
if($CTRLFile ne ""){
  #Does it make sense to have an env without a ctrl port?
  #Maybe for one-shot env gen?
  open($CTRL,'<', $CTRLFile) or die "cannot open env CTRL port";
}else{
  die "env requires a -ctrl argument";
}

binmode(STDOUT,":raw") || die "cannot binmode STDOUT";

$attackS = $attack * $SampRate;
$decayS = $decay * $SampRate;
$sustainS = $sustain * $SampRate;
$releaseS = $release * $SampRate;
my $maxA = $amp * 65536;
my $susA = $sus * 65536;
my $mode = 0;#0: send zeros; 1: send env, transition to 0

my $buff;

while(1){

  print STDERR "trying to read chars\n";
  my $in = read $CTRL, $buff, 1;
  print STDERR "tried to read chars\n";
  if( defined $in && $in != 0){
    print STDERR "successfully read chars\n";
    $mode = 1;
    $buff = undef;
  }else{
  
    print STDERR "did not read chars\n";
  }

  if( $mode == 1 ){
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
    $mode = 0;
  }else{

    print pack 'S', 0; 

  }

}
