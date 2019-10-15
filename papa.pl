#!/usr/bin/perl -s
#*************************************************************************
#
#   Program:    papa
#   File:       papa.pl
#   
#   Version:    V1.3
#   Date:       15.10.19
#   Function:   Predict interface packing angle
#   
#   Copyright:  (c) Dr. Andrew C. R. Martin, UCL, 2016-2019
#   Author:     Dr. Andrew C. R. Martin
#   Address:    Institute of Structural and Molecular Biology
#               Division of Biosciences
#               University College
#               Gower Street
#               London
#               WC1E 6BT
#   EMail:      andrew@bioinf.org.uk
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
#   Predict the VH/VL packing angle from a .seq file
#   This is a rewrite of Abhi's code for doing this and uses his neural
#   network
#
#*************************************************************************
#
#   Usage:
#   ======
#
#   papa.pl file.seq
#
#*************************************************************************
#
#   Revision History:
#   =================
#
#   V1.0    07.10.16  Original   By: ACRM
#   V1.1    14.10.16  Now uses custom C program rather than batchman
#                     No need to install SNNS any more
#   V1.2              Skipped
#   V1.3    15.10.19  Correctly multiplies the angle by -1 !!!
#
#*************************************************************************
#  Globals
#  =======
$::minimumInterfaceAngle         = 30.951270;
$::maximumInterfaceAngle         = 60.754947;
$::numberOfEncodingsPerAminoAcid = 4;
#*************************************************************************
use strict;
# Find where the library files are
use FindBin;
use Cwd qw(abs_path);
$::papalib = abs_path("$FindBin::Bin/share/papa");
$::papanet = "$::papalib/papanet";

if((scalar(@ARGV) != 1) || ($ARGV[0] eq "-h"))
{
    UsageDie();
}

my $numberingFile = shift(@ARGV);
my $packingAngle  = RunPrediction($numberingFile);
$packingAngle     = -1.0 * $packingAngle;

# Print the packing angle.
if(defined($::q))
{
    print "$packingAngle\n";
}
else
{
    print "Predicted packing angle: $packingAngle\n";
}


#*************************************************************************
# RunPrediction($numberingFile)
# -----------------------------
sub RunPrediction
{
    my($numberingFile) = @_;

    my $criticalPositionsFile = "$::papalib/new_best_positions.txt";
    my $aminoAcidsFile        = "$::papalib/residue_properties.mat";
    my $tempDir               = "/tmp/papa$$" . time(); 

    `mkdir $tempDir`;
    if(! -d $tempDir)
    {
        MyDie("Unable to create temporary directory $tempDir");
    }

    # Files used by SNNS
    my $inputPatternsFile  = "$tempDir/input.pat";

    my @criticalPositions  = ();
    my %aminoAcidsEncoding = ();
    my %numberingHash      = ();
    my $packingAngle       = -1;

    # Read the numbered sequence file
    ReadNumberingFile($numberingFile, \%numberingHash);

    # Read the list of critical positions.
    ReadCriticalPositions($criticalPositionsFile, \@criticalPositions);

    # Read encoding for the amino acids.
    ReadAminoAcidEncoding($aminoAcidsFile, \%aminoAcidsEncoding);

    # Write the encoding to a pattern file.
    WritePatternEncodingFile($inputPatternsFile,
                             \@criticalPositions,
                             \%numberingHash,
                             \%aminoAcidsEncoding);

    # Write a script file for SNNS to calculate the packing angle.
    $packingAngle = RunSNNS($::papanet, $inputPatternsFile);

    # Calculate the packing angle.
    $packingAngle = ScalePackingAngle($packingAngle,
                                      $::minimumInterfaceAngle,
                                      $::maximumInterfaceAngle);

    # Adjust precision.
    $packingAngle = sprintf("%3.4f", $packingAngle);

    # Clear all the temporary files created.
    if(defined($::debug))
    {
        print STDERR "Intermediary files are in $tempDir\n";
    }
    else
    {
        `\\rm -rf $tempDir`;
    }

    return($packingAngle);
}


#*************************************************************************
# ReadCriticalPositions($criticalPositionsFile, \@criticalPositions)
# ------------------------------------------------------------------
# Read the list of critical positions.
sub ReadCriticalPositions
{
   my ($criticalPositionsFile, $aCriticalPositions) = @_;

   # Open the file in read mode.
   if(open(HD, $criticalPositionsFile))
   {
       while(my $position = <HD>)
       {
           chomp($position);
           push(@$aCriticalPositions, $position);
       }

       close(HD);
   }
   else
   {
       MyDie("Unable to read critical residues file: " .
             $criticalPositionsFile);
   }
}


#*************************************************************************
# ReadAminoAcidEncoding($aminoAcidsFile, \%aminoAcidsEncoding)
# ------------------------------------------------------------
# Read encoding for the amino acids.
sub ReadAminoAcidEncoding
{
   my ($aminoAcidsFile, $hAminoAcidsEncoding) = @_;

   my $line     = "";
   my @parts    = ();
   my $residue  = "";
   my $encoding = "";

   if(open(HD, $aminoAcidsFile))
   {
       # Read through the contents and add them to the hash.
       while($line = <HD>)
       {
           chomp($line);

           # If the line does not start with a residue or a 
           # gap, skip to the next line.
           next if($line !~ /^[A-Z|\-]/);
           
           # Split the line into the constituent fields.
           # The file looks like this:
           #
           # E       5       4       -0.62   -1
           @parts    = split(/\t/, $line);
           $residue  = $parts[0];
           $encoding = $parts[1].":".$parts[2].":".
                       $parts[3].":".$parts[4];
           
           # Store the encoding for the amino acid
           $$hAminoAcidsEncoding{$residue} = $encoding;
       }

       close(HD);
   }
   else
   {
       MyDie("Unable to read amino acid encoding file: $aminoAcidsFile");
   }
}


#*************************************************************************
# ReadNumberingFile($numberingFile, \%numberingHash)
# --------------------------------------------------
# Read the numbering file.
sub ReadNumberingFile
{
   my ($numberingFile, $hNumberingHash) = @_;
   my $line     = "";
   my $position = "";
   my $residue  = "";

   # Open the file in read mode.
   if(open(HD, $numberingFile))
   {
       while($line = <HD>)
       {
           chomp($line);

           # If the line does not match the pattern of a line 
           # containing numbering, skip to the next line.
           next if($line !~ /^[LH][0-9]/);

           # Split the line into position and residue.
           ($position, $residue) = split(/\s+/, $line);

           # Store residue type by position
           $$hNumberingHash{$position} = throne($residue);
       }
       close(HD);
   }
   else
   {
       MyDie("Unable to read numbering file: $numberingFile");
   }
}


#*************************************************************************
# WritePatternEncodingFile($inputPatternsFile, \@criticalPositions,
#                          \%numberingHash, \%aminoAcidsEncoding)
# -----------------------------------------------------------------
# Write the encoding to a pattern file.
sub WritePatternEncodingFile
{
   my ($inputPatternsFile, $aCriticalPositions,
       $hNumberingHash, $hAminoAcidsEncoding) = @_;

   my $numberOfCriticalPositions     = scalar(@$aCriticalPositions);
   my $numberOfInputUnits = ($numberOfCriticalPositions * 
                             $::numberOfEncodingsPerAminoAcid);

   # Open the patterns file in write mode.
   if(open(WHD, ">$inputPatternsFile"))
   {
       # Write the pattern file header.
       print WHD "SNNS pattern definition file V3.2\n";
       print WHD "generated at Wed Oct 14 11:46:48 2009\n\n\n\n";

       # Write information regarding number of patterns.
       print WHD "No. of patterns : 1\n";
       print WHD "No. of input units : ", $numberOfInputUnits, "\n";
       print WHD "No. of output units : 1\n\n";

       # Write the input units (i.e. encoding for amino acids at the 
       # critical positions).
       for(my $i=0; $i<scalar(@$aCriticalPositions); $i++)
       {
           my $position = $$aCriticalPositions[$i];
           my $residueAtPosition = $$hNumberingHash{$position};
           
           my($encoding1, $encoding2, $encoding3, $encoding4) = 
               split(/:/, $$hAminoAcidsEncoding{$residueAtPosition});

           print WHD "$encoding1 $encoding2 $encoding3 $encoding4\n";
       }

       # At the end of the file, write a dummy output value.
       print WHD "# Dummy output value\n0\n";

       close(WHD);
   }
   else
   {
       MyDie("Unable to write temporary pattern file: " .
             $inputPatternsFile);
   }
}


#*************************************************************************
# RunSNNS($papanet, $inputPatternsFile)
# --------------------------------------------------------
# Runs the SNNS papanet standalone program
#
sub RunSNNS
{
    my ($papanet, $inputPatternsFile) = @_;

    if(!(-x $papanet))
    {
        MyDie("papanet executable not found: $papanet");
    }

    my $command = "$papanet $inputPatternsFile";
    return(`$command`);
}


#*************************************************************************
# $aaOne = throne($aaThree)
# -------------------------
# Convert three letter code to one-letter code. Input can be one-letter
# code already and mixed case.
sub throne
{
    my($aa) = @_;

    my %throneHash = (
        'ALA' => 'A',
        'CYS' => 'C',
        'ASP' => 'D',
        'GLU' => 'E',
        'PHE' => 'F',
        'GLY' => 'G',
        'HIS' => 'H',
        'ILE' => 'I',
        'LYS' => 'K',
        'LEU' => 'L',
        'MET' => 'M',
        'ASN' => 'N',
        'PRO' => 'P',
        'GLN' => 'Q',
        'ARG' => 'R',
        'SER' => 'S',
        'THR' => 'T',
        'VAL' => 'V',
        'TRP' => 'W',
        'TYR' => 'Y'
        );


    $aa = "\U$aa";
    return($aa)              if(length($aa) == 1);
    return($throneHash{$aa}) if(defined($throneHash{$aa}));
    return('X');
}


#*************************************************************************
# $packingAngle = ScalePackingAngle($packingAngle,
#                                   $minimumInterfaceAngle,
#                                   $maximumInterfaceAngle)
# ---------------------------------------------------------
# Scale the packing angle
sub ScalePackingAngle
{

   my ($predictedInterfaceAngleFraction,
       $minimumInterfaceAngle,
       $maximumInterfaceAngle) = @_;

   my $angleDifference = $maximumInterfaceAngle - $minimumInterfaceAngle;

   # Convert the interface angle fraction into an actual angle 
   # calculated as:
   #
   #                           (InterfaceAngle - MinInterfaceAngle)
   # interfaceAngleFraction = ---------------------------------------
   #                          (MaxInterfaceAngle - MinInterfaceAngle)
   #
   # It follows that the interface angle is calculated in the following 
   # way:
   #
   # interfaceAngle = MinInterfaceAngle + 
   #                  (InterfaceAngleFraction * 
   #                              (MaxInterfaceAngle - MinInterfaceAngle))
   my $predictedInterfaceAngle = $minimumInterfaceAngle + 
                                 ($predictedInterfaceAngleFraction * 
                                  $angleDifference);

   # Return the predicted interface angle
   return $predictedInterfaceAngle;
}


#*************************************************************************
sub MyDie
{
    my($message) = @_;

    print STDERR "$message\n";
    exit(1);
}


#*************************************************************************
sub UsageDie
{
    print <<__EOF;

papa V1.3 (c) UCL, Dr. Andrew C.R. Martin, 2016-2019

Usage: papa [-q] file.seq
       -q Quiet - simply outputs the angle with no other text

Uses Abhinandan Raghavan's trained neural network to predict the VH/VL
packing angle. Input is a .seq file, i.e. a numbered file of the form

   L1 D
   L2 I
   L3 Q
   L4 M
   ...

Output is the predicted packing angle

__EOF
}


