#!/usr/bin/perl

use warnings;
use strict;
use Getopt::Long;
use Fcntl;
$|=1;

my $SampRate = 44100;
my $SampSize = 2;
my $amp = 1.0;
my $AMFile= "";
my $AmpModDepth= 1.0;
my $numsamps = 0;

GetOptions ("srate=i"  => \$SampRate,
            "ssize=i"  => \$SampSize,
            "amp=f"    => \$amp,
            "ampmod=s"  =>   \$AMFile,
            "ampmoddepth=f"  =>   \$AmpModDepth,
            "numsamps=n"    => \$numsamps)
or die("Error in command line arguments\n");


my $AM;
if($AMFile ne ""){
  sysopen($AM,$AMFile,O_RDONLY);
  binmode($AM,":raw") || die "cannot binmode AM";
}

binmode(STDOUT,":raw") || die "cannot binmode STDOUT";

my $AMScaleFactor = 1.0;

while(1){

  if( $AMFile ne "" ){

    if(eof($AM)){
      close($AM);
      sysopen($AM,$AMFile,O_RDONLY);
      binmode($AM,":raw") || die "cannot reinit AM pipe $!";
    }

    my $amraw;
    read($AM, $amraw, $SampSize); 
    my $amval = unpack "S", $amraw;
    $amval = 0 if !defined $amval;
    $AMScaleFactor = $amval / 65536;
  }

  $AMScaleFactor *= $AmpModDepth;
  my $samp = rand(65536);

  print pack 'S', ($samp * $AMScaleFactor); 

}
