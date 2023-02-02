#csvdata=~veronica/VHVLPack/ninetenths_july_nonred/ninetenths_july_nonred_NR2_13res.csv

origcsvdata=ninetenths_july_nonred_NR2_13res.csv
scaledcsvdata=ninetenths_july_nonred_NR2_13res_scaled.csv
inputs=in13res.dat

# Scale the angles from 0 to 1
./scale.pl $origcsvdata >$scaledcsvdata 2>minmax.txt

# Convert csv to arff
csv2arff -ni $inputs angle $scaledcsvdata > final.arff

# And arff to .pat
arff2snns final.arff > final.pat

# Train the NN
batchman -f final_training.cmd
