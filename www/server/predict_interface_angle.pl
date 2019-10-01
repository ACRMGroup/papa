#!/usr/bin/perl

use strict 'vars';
use DBI;
use Env;

# ----------- DECLARATION OF GLOBAL VARIABLES ----------

   my $SNNS_PATH = $ENV{"SNNS_PATH"};
   my $trainedNetwork = $ENV{"TRAINEDNET"};
   my $temporaryDirectory = "/tmp/"; # NEEDS trailing slash!

   my $criticalPositionsFilename = "";
   my $numberingFilename = "";
   my $aminoAcidsFilename = "";

   # Set variable names for files used by SNNS.

   my $scriptFilename = $temporaryDirectory.$$."_predict.cmd";
   my $inputPatternsFilename = $temporaryDirectory.$$."_input.pat";
   my $outputPatternsFilename = $temporaryDirectory.$$."_output.pat";

   my @criticalPositions = ();
   my %aminoAcidsEncoding = ();
   my %numberingHash = ();
   my $packingAngle = -1;
   my $maximumInterfaceAngle = -1;
   my $minimumInterfaceAngle = -1;

# ---- END OF GLOBAL VARIABLES DECLARATION SECTION -----


# Main code of the program starts here.
#
# perl predict_interface_angle.pl $criticalPositionsFilename $numberingOutputFilename $aminoAcidsFilename

# Check for the command line parameters.

if($#ARGV < 4)
{
   print "\nUsage: $0 <Arguments>\n";
   print "\nArguments are:\n";
   print "\n1. File with list of critical positions to predict packing angle.";
   print "\n2. File with numbering output for the sequence files.";
   print "\n3. File encoding amino acids.";
   print "\n4. Minimum interface angle.";
   print "\n5. Maximum interface angle.";
   print "\n\nPlease note that the following environment variables must be setup:\n";
   print "\na) SNNS_PATH: Pointing to the directory containing the program \"batchman\".";
   print "\nb) TRAINEDNET: Pointing to the file containing the trained neural network.";
   print "\n\n";
   exit(0);
}

$criticalPositionsFilename = $ARGV[0];
$numberingFilename = $ARGV[1];
$aminoAcidsFilename = $ARGV[2];
$minimumInterfaceAngle = $ARGV[3];
$maximumInterfaceAngle = $ARGV[4];

# Check for the input files.

if(! &check_files($criticalPositionsFilename,
                  $numberingFilename,
                  $aminoAcidsFilename) )
{
   print STDERR "\nAborting program.\n\n";
   exit(0);
}

# Check the required environment variables.
#
# 1. SNNS_PATH: Pointing to the directory containing the program batchman.
# 2. TRAINEDNET: Pointing to the file containing the trained neural network.

if(! &check_environment_variables() )
{
   exit(0);
}

# Read the list of critical positions.

&read_critical_positions($criticalPositionsFilename, \@criticalPositions);

# Read encoding for the amino acids.

&read_amino_acid_encoding($aminoAcidsFilename, \%aminoAcidsEncoding);

# Read the numbering file.

&read_numbering_file($numberingFilename, \%numberingHash);

# Write the encoding to a pattern file.

&write_pattern_encoding_file($inputPatternsFilename,
                             \@criticalPositions,
                             \%numberingHash,
                             \%aminoAcidsEncoding);

# Write a script file for SNNS to calculate the packing angle.

&run_script($trainedNetwork,
            $inputPatternsFilename,
            $outputPatternsFilename,
            $scriptFilename);

# Calculate the packing angle.

$packingAngle = &extract_packing_angle($outputPatternsFilename,
                                       $minimumInterfaceAngle,
                                       $maximumInterfaceAngle);

# Adjust precision.

$packingAngle = sprintf("%3.4f", $packingAngle);

# Print the packing angle.

print "\nPredicted packing angle: $packingAngle\n\n";

# Clear all the temporary files created.

unlink($inputPatternsFilename);
unlink($outputPatternsFilename);
unlink($scriptFilename);

# End of program.


# --------------- SUB - ROUTINES SECTION ---------------

sub check_files
{
   # if(! &check_files($criticalPositionsFilename,
   #                   $numberingFilename,
   #                   $aminoAcidsFilename) )

   my ($criticalPositionsFilename,
       $numberingFilename,
       $aminoAcidsFilename) = @_;

   # Check for $criticalPositionsFilename.

   if(! -e $criticalPositionsFilename)
   {
      print STDERR "\nUnable to open file \"$criticalPositionsFilename\" in read mode.";
      return 0;
   }

   # Check for $numberingFilename.

   if(! -e $numberingFilename)
   {
      print STDERR "\nUnable to open file \"$numberingFilename\" in read mode.";
      return 0;
   }

   # Check for $aminoAcidsFilename.

   if(! -e $aminoAcidsFilename)
   {
      print STDERR "\nUnable to open file \"$aminoAcidsFilename\" in read mode.";
      return 0;
   }

   # Return 1 to indicate successful completion of the function.

   return 1;

} # End of sub-routine "check_files".


# Check the required environment variables.
#
# 1. SNNS_PATH: Pointing to the directory containing the program batchman.
# 2. TRAINEDNET: Pointing to the file containing the trained neural network.

sub check_environment_variables
{
   # SNNS_PATH.

   if(! $ENV{"SNNS_PATH"} )
   {
      print STDERR "\nPlease set \"SNNS_PATH\" to point to the directory containing the program \"batchman\".\n\n";
      return 0;
   }

   # TRAINEDNET.

   if(! $ENV{"TRAINEDNET"} )
   {
      print STDERR "\nPlease set \"TRAINEDNET\" to point to the file containing the trained neural network.\n\n";
      return 0;
   }

   # Return 1 to indicate successful completion of the function.

   return 1;

} # End of sub-routine "check_environment_variables".


# Read the list of critical positions.

sub read_critical_positions
{
   # &read_critical_positions($criticalPositionsFilename, \@criticalPositions);

   my ($criticalPositionsFilename, $criticalPositions) = @_;
   my $position = ();

   # Open the file in read mode.

   open(HD, $criticalPositionsFilename);

   # Read all the contents.

   while($position = <HD>)
   {
      chomp($position);

      # Push the position into an array.

      push(@$criticalPositions, $position);
   }

   # Close the file handle.

   close(HD);

} # End of sub-routine "read_critical_positions".



# Read encoding for the amino acids.

sub read_amino_acid_encoding
{
   # &read_amino_acid_encoding($aminoAcidsFilename, \%aminoAcidsEncoding);

   my ($aminoAcidsFilename, $aminoAcidsEncoding) = @_;
   my $line = "";
   my @parts = ();
   my $residue = "";
   my $encoding = "";

   # Open the file in read mode.

   open(HD, $aminoAcidsFilename);

   # Read through the contents and add them to the hash.

   while($line = <HD>)
   {
      # If the line does not start with a residue or a gap, skip to the next line.

      if($line !~ /^[A-Z|\-]/)
      {
         next;
      }

      # Remove newlines at the end.

      chomp($line);

      # Split the line into the constituent fields.
      # The file looks like this:
      #
      # E       5       4       -0.62   -1

      @parts = split(/\t/, $line);

      $residue = $parts[0];
      $encoding = $parts[1].":".$parts[2].":".$parts[3].":".$parts[4];

      # Assign the residue and the encoding to the hash.

      $$aminoAcidsEncoding{$residue} = $encoding;
   }

   # Close the file handle.

   close(HD);

} # End of sub-routine "read_amino_acid_encoding".


# Read the numbering file.

sub read_numbering_file
{
   # &read_numbering_file($numberingFilename, \%numberingHash);

   my ($numberingFilename, $numberingHash) = @_;
   my $line = "";
   my $position = "";
   my $residue = "";

   # Open the file in read mode.

   open(HD, $numberingFilename);

   # Read through the contents and store the numbering in a hash.

   while($line = <HD>)
   {
      chomp($line);

      # If the line does not match the pattern of a line containing numbering,
      # skip to the next line.

      if($line !~ /^[LH][0-9]/)
      {
         next;
      }

      # Split the line into position and residue.

      ($position, $residue) = split(/ /, $line);

      # Assign the position and the residue to a hash.

      $$numberingHash{$position} = $residue;
   }

   # Close the file handle.

   close(HD);

} # End of sub-routine "read_numbering_file".

# Write the encoding to a pattern file.


sub write_pattern_encoding_file
{
   # &write_pattern_encoding_file($inputPatternsFilename,
   #                              \@criticalPositions,
   #                              \%numberingHash,
   #                              \%aminoAcidsEncoding);

   my ($inputPatternsFilename,
       $criticalPositions,
       $numberingHash,
       $aminoAcidsEncoding) = @_;

   my $position = "";
   my $residueAtPosition = "";
   my $numberOfEncodingsPerAminoAcid = 4;
   my $i = 0;
   my $numberOfCriticalPositions = $#$criticalPositions + 1;
   my $numberOfInputUnits = ($numberOfCriticalPositions * $numberOfEncodingsPerAminoAcid);
   my $encoding1 = -1;
   my $encoding2 = -1;
   my $encoding3 = -1;
   my $encoding4 = -1;

   # Open the patterns file in write mode.

   open(WHD, ">$inputPatternsFilename");

   # Write the pattern file header.

   print WHD "SNNS pattern definition file V3.2\n";
   print WHD "generated at Wed Oct 14 11:46:48 2009\n\n\n\n";

   # Write information regarding number of patterns.

   print WHD "No. of patterns : 1\n";
   print WHD "No. of input units : ", $numberOfInputUnits, "\n";
   print WHD "No. of output units : 1\n\n";

   # Write the input units (i.e. encoding for amino acids at the critical positions).

   for($i = 0 ; $i <= $#$criticalPositions ; $i++)
   {
      $position = $$criticalPositions[$i];
      $residueAtPosition = $$numberingHash{$position};

      ($encoding1, $encoding2, $encoding3, $encoding4) = split(/:/, $$aminoAcidsEncoding{$residueAtPosition});

      print WHD $encoding1, " ",
                $encoding2, " ",
                $encoding3, " ",
                $encoding4;

      # Write a new line.

      print WHD "\n";
   }

   # At the end of the file, write a dummy output value.

   print WHD "# Dummy output value\n",
             "0";

   # Close the write handle.

   close(WHD);

} # End of sub-routine "write_pattern_encoding_file".


# Write a script file for SNNS to calculate the packing angle.

sub run_script
{
   # &run_script($trainedNetwork,
   #             $inputPatternsFilename,
   #             $outputPatternsFilename);
   #             $scriptFilename);

   my ($trainedNetworkFilename,
       $inputPatternsFilename,
       $outputPatternsFilename,
       $scriptFilename) = @_;

   my $command;

   # Open the script file in output mode.

   open(WHD, ">$scriptFilename");

   # Write lines to perform the following steps:
   #
   # 1. Load the neural network. 
   # 2. Load the input patterns file.
   # 3. Test the network (i.e. do the prediction).
   # 4. Write the results of the prediction to the output patterns file.

   # Step 1: Load the trained neural network.

   print WHD "loadNet(\"$trainedNetwork\")\n";

   # Step 2: Load the input patterns file.

   print WHD "loadPattern(\"$inputPatternsFilename\")\n";

   # Step 3: Test the network (i.e. do the prediction).

   print WHD "testNet()\n";

   # Step 4: Write the results of the prediction to the output patterns file.

   print WHD "saveResult(\"$outputPatternsFilename\")";

   # Close the output file handle.

   close(WHD);

   # Run the script.

   $command = "$SNNS_PATH/batchman -q < $scriptFilename";

   `$command`;

} # End of sub-routine "run_script".



# Calculate the packing angle.

sub extract_packing_angle
{
   # $packingAngle = &extract_packing_angle($outputPatternsFilename,
   #                                        $minimumInterfaceAngle,
   #                                        $maximumInterfaceAngle);

   my ($outputPatternsFilename,
       $minimumInterfaceAngle,
       $maximumInterfaceAngle) = @_;

   my $line = "";
   my $lastNumbersLine = "";
   my @parts = ();
   my $predictedInterfaceAngleFraction = -1;
   my $predictedInterfaceAngle = -1;
   my $angleDifference = $maximumInterfaceAngle - $minimumInterfaceAngle;

   # Open the output patterns file (output of the neural network) in read mode.

   open(HD, $outputPatternsFilename);

   # Read through the contents.

   while($line = <HD>)
   {
      chomp($line);

      # If the line starts with a number, store it.

      if($line =~ /^[0-9]/)
      {
         $lastNumbersLine = $line;
      }
   }

   # Extract the last number from the last line containing numbers (i.e. $lastNumbersLine).

   @parts = split(/ /, $lastNumbersLine);
   $predictedInterfaceAngleFraction = $parts[$#parts];

   # Convert the interface angle fraction into an actual angle. The interface angle fraction
   # is calculated in the following way:
   #
   # interfaceAngleFraction = (Interface angle - Min. interface angle)/(Max. interface angle - Min. interface angle).
   #
   # It follows that the interface angle is calculated in the following way:
   #
   # Interface angle =  Min. interface angle + Interface angle fraction * (Max interface angle - Min. Interface angle)

   $predictedInterfaceAngle = $minimumInterfaceAngle + ($predictedInterfaceAngleFraction * $angleDifference);

   # Close the input patterns file handle.

   close(HD);

   # Return the predicted interface angle to the calling function.

   return $predictedInterfaceAngle;

} # End of sub-routine "extract_packing_angle".
