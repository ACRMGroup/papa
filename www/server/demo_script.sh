# Step 1: Setup the required environment variables.

export SNNS_PATH=/acrm/usr/local/bin/
export TRAINEDNET=/home/bsm2/abhi/VH-VL-INTERFACE/KABAT_NUMBERING/PROFILE_BASED_APPROACH/SLIDING_WINDOW_PROTOCOL/NEW_VH-VL_PACKING/WEB_SERVER/final_trained.net

# Step 2: Setup required variables.

export inputPIRFilename=/home/bsm2/abhi/VH-VL-INTERFACE/KABAT_NUMBERING/PROFILE_BASED_APPROACH/SLIDING_WINDOW_PROTOCOL/NEW_VH-VL_PACKING/PDB_SEQUENCES/WITHOUT_ANTIGENS_AND_REDUNDANCY/12e8.pir

export criticalPositionsFilename=/home/bsm2/abhi/VH-VL-INTERFACE/KABAT_NUMBERING/PROFILE_BASED_APPROACH/SLIDING_WINDOW_PROTOCOL/NEW_VH-VL_PACKING/new_best_positions.txt

export aminoAcidEncodingFilename=/home/bsm2/abhi/DATA/ABNUM/residue_properties.mat

# Step 3: Call the shell script.

sh predict_interface_angle.sh  $inputPIRFilename $criticalPositionsFilename $aminoAcidEncodingFilename