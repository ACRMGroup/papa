#!/usr/bin/perl -s
use strict;

UsageDie() if(defined($::h) || !(scalar(@ARGV)));

my $dest = shift(@ARGV);

`mkdir -p $dest` if(! -d $dest);
`cp *.* $dest`;
`cp Makefile $dest`;
`cp htaccess $dest/.htaccess`;

`(cd ../papanet; make)`;
`(cd ..; ./install.sh $dest/bin`;






    sub UsageDie
{
    exit 0;
}
