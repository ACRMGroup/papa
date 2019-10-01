#!/usr/bin/perl
#*************************************************************************
#
#   Program:    paps (Packing Angle Prediction Server)
#   File:       paps.pl
#   
#   Version:    V1.1
#   Date:       26.01.10
#   Function:   Wrapper to Abhi's prediction neural network
#   
#   Copyright:  (c) UCL / Dr. Andrew C. R. Martin 2010
#   Author:     Dr. Andrew C. R. Martin
#   Address:    Biomolecular Structure & Modelling Unit,
#               Department of Biochemistry & Molecular Biology,
#               University College,
#               Gower Street,
#               London.
#               WC1E 6BT.
#   EMail:      andrew@bioinf.org.uk
#   Web:        http://www.bioinf.org.uk/
#               
#               
#*************************************************************************
#
#   This program is not in the public domain, but it may be copied
#   according to the conditions laid out in the accompanying file
#   COPYING.DOC
#
#   The code may be modified as required, but any modifications must be
#   documented so that the person responsible can be identified. If 
#   someone else breaks this code, I don't want to be blamed for code 
#   that does not work! 
#
#   The code may not be sold commercially or included as part of a 
#   commercial product except as described in the file COPYING.DOC.
#
#*************************************************************************
#
#   Description:
#   ============
#
#*************************************************************************
#
#   Usage:
#   ======
#
#*************************************************************************
#
#   Revision History:
#   =================
#   V1.0  14.01.10  Original   By: ACRM
#   V1.1  26.01.10  Checks for return value which indiactes numbering 
#                   failed
#*************************************************************************
use strict;

#*************************************************************************
my $snns_path = "/acrm/usr/local/bin/";
my $server_url = "/abs/paps/server";
my $server_path = "/var/www/html/${server_url}";

#*************************************************************************
# Step 1: Setup the environment variables.
$ENV{"SNNS_PATH"}=$snns_path;
$ENV{"SERVER_PATH"}=$server_path;
$ENV{"TRAINEDNET"}="$server_path/final_trained.net";

# Step 2: Setup required variables.
my $seq1 = shift(@ARGV);
my $seq2 = shift(@ARGV);
my $inputPIRFilename=WritePIR($seq1, $seq2);
my $criticalPositionsFilename = "$server_path/new_best_positions.txt";
my $aminoAcidEncodingFilename = "$server_path/residue_properties.mat";
my $torsionlist               = "$server_path/torsion_angles.dat";


# Step 3: Call the shell script.
my $result=`$server_path/predict_interface_angle.sh $inputPIRFilename $criticalPositionsFilename $aminoAcidEncodingFilename`;

my ($text,$rawnumber) = split(/:/, $result);

$rawnumber = -1 * $rawnumber;
my ($bestpdb, $besttorsion) = FindClosestPDB($rawnumber, $torsionlist);
my $number = int($rawnumber*10)/10;

# 26.01.10 - Checks for this value which indicates the numbering failed
if($number == -30.9)
{
    print <<__EOF;
<p>Sorry, we were unable to apply standard numbering to your antibody
    sequence. Please <a href='/contact.html'>contact us</a> and we
    will try to fix the problem.
</p>
__EOF
}
else
{
    print <<__EOF;
<p>
$text: <span class='paps_result'>$number</span>
</p>
__EOF

    if($bestpdb ne "")
    {
        my $pdburl = "${server_url}/pdb/${bestpdb}_reg.pdb";

        print <<__EOF;

<p> The closest packing angle in a set of 568 structures from the PDB
is for PDB code <span class='paps_pdb'>$bestpdb</span> with torsion
angle <span class='paps_pdb_angle'>$besttorsion</span> </p>

<p>Download a Kabat-numbered <span class='paps_pdb_file'><a
href='$pdburl'>PDB file</a></span> with vectors drawn through the
conserved strands that define the packing angle. The vectors are
represented by additional 'X' and 'Y' chains of closely spaced atoms
such that display using RasMol will give 2 straight lines.</p>

__EOF
    }
}

unlink($inputPIRFilename);

#*************************************************************************
sub FindClosestPDB
{
    my($torsion, $list) = @_;
    my $mindiff = 180.0;
    my $bestpdb = "";
    my $besttorsion = 180.0;

    if(open(FILE, $list))
    {
        while(<FILE>)
        {
            chomp;
            my($angle, $pdb) = split;
            my $diff = abs($torsion - $angle);
            if($diff < $mindiff)
            {
                $mindiff = $diff;
                $bestpdb = $pdb;
                $besttorsion = int($angle*10)/10.0;
            }
            else
            {
                last;
            }
        }
        close(FILE);
    }
    return($bestpdb, $besttorsion);
}

#*************************************************************************
sub WritePIR
{
    my($light, $heavy) = @_;

    my $filename = "/tmp/paps_$$.pir";
    if(open(FILE, ">$filename"))
    {
        print FILE ">P1;paps\n";
        print FILE "paps input file\n";
        print FILE "${light}*\n";
        print FILE "${heavy}*\n";
        close FILE;
    }
    else
    {
        print "Unable to open temporary file \"$filename\" for writing\n";
        exit 1;
    }
    return($filename);
}
