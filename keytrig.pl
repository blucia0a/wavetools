#!/usr/bin/perl
use warnings;
use strict;
use Term::ReadKey;
use Getopt::Long; 

$| = 1;
my $key;
ReadMode 3; # Turn off controls keys
while(1){
  while (not defined ($key = ReadKey(-1))) {
     # No key yet
  }
  print "$key";
  last if $key eq 'q';
  $key = undef;
}
ReadMode 0; # Reset tty mode before exiting
