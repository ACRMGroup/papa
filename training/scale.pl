#!/usr/bin/perl
use strict;

$::minReject = -65;
$::maxReject = -30;

my $file = shift(@ARGV);

# Find the min and max angle
my($min, $max) = FindMinMax($file);
ScaleFile($file, $min, $max);

printf (STDERR "# Min: $min Max: $max\n");

sub ScaleFile
{
    my($file, $minAngle, $maxAngle) = @_;
    if(open(my $fp, '<', $file))
    {
        $_=<$fp>;
        print("$_");
        while(<$fp>)
        {
            chomp;
            my @fields = split(/,/, $_);
            my $nFields = scalar(@fields);
            my $angle = $fields[$nFields-1];
            if(($angle >= $::minReject) && ($angle <= $::maxReject))
            {
                $angle = ($angle - $minAngle) / ($maxAngle - $minAngle);
                $fields[$nFields-1] = $angle;
                print join(',',@fields);
                print "\n";
            }
        }
    }
    else
    {
        die "Can't open $file";
    }
}

sub FindMinMax
{
    my($file) = @_;
    my $min = 360;
    my $max = -180;
    if(open(my $fp, '<', $file))
    {
        <$fp>;
        while(<$fp>)
        {
            chomp;
            my @fields = split(/,/, $_);
            my $angle = $fields[scalar(@fields)-1];
            $min = $angle if(($angle < $min) && ($angle > $::minReject));
            $max = $angle if(($angle > $max) && ($angle < $::maxReject));
        }
    }
    else
    {
        die "Can't open $file";
    }
    return($min, $max);
}
    
