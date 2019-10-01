#! /bin/sh


####################### Sub-routines section #################

do_check_files ()
{
   # Check for the input PIR file.

   if [ ! -e $inputPIRFilename ]
   then
      echo
      echo "Unable to find file \"$inputPIRFilename\""
      echo
      return 0
   fi

   # Check for file with the list of critical positions.

   if [ ! -e $criticalPositionsFilename ]
   then
      echo
      echo "Unable to find file \"$criticalPositionsFilename\""
      echo
      return 0
   fi

   # Check for file with the list of critical positions.

   if [ ! -e $aminoAcidsFilename ]
   then
      echo
      echo "Unable to find file \"$aminoAcidsFilename\""
      echo
      return 0
   fi

} # End of sub-routine "do_check_files".


#################### End of sub-routines section #############


# Check for command line paramters.

if [ $# -lt 3 ]
then
   echo
   echo "Usage: $0 <Arguments>"
   echo
   echo "1. PIR format file (with light and heavy chain."
   echo "2. File with the list of critical positions."
   echo "3. File encoding amino acids."
   echo
   exit 0
fi

inputPIRFilename=$1
criticalPositionsFilename=$2
aminoAcidsFilename=$3

# Set the minimum and maximum interface angles.

minimumInterfaceAngle=30.951270
maximumInterfaceAngle=60.754947

# Check if the file names fed in via command line are present.

if [ ! do_check_files ]
then
   exit 0
fi

# Assign the required variable names.

numberingOutputFilename="/acrm/home/abhi/tmp/SNNS/$$.num"
inputPatternsFilename="/acrm/home/abhi/tmp/SNNS/input.pat"
outputPatternsFilename="/acrm/home/abhi/tmp/SNNS/output.pat"

# Apply numbering to the PIR format file.
#
# Usage: /home/bsm/martin/abnum/installed/numbering/kabnum_wrapper.pl <Arguments>
#
# 1. Input PIR file
# 2. -k/-c/-a (Kabat, Chothia or Abhi numbering) - Default: -k>

/home/bsm/martin/abnum/installed/numbering/kabnum_wrapper.pl $inputPIRFilename -c > $numberingOutputFilename

# Invoke the program that predicts the packing angle using the neural network.
#
# Usage: predict_interface_angle.pl <Arguments>
#
# Arguments are:
#
# 1. File with list of critical positions to predict packing angle.
# 2. File with numbering output for the sequence files.
# 3. File encoding amino acids.
# 4. Minimum interface angle.
# 5. Maximum interface angle.
#
# Please note that the following environment variables must be setup:
#
# a) SNNS_PATH: Pointing to the directory containing the program "batchman".
# b) TRAINEDNET: Pointing to the file containing the trained neural network.

$SERVER_PATH/predict_interface_angle.pl $criticalPositionsFilename $numberingOutputFilename $aminoAcidsFilename $minimumInterfaceAngle $maximumInterfaceAngle

# End of script.
