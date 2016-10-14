papa
====

papalib
-------

This directory contains library files for papa

- `final_trained.net` This is the trained SNNS network file. It is not used
  directly by the papa software when being run, but is used to build the
  papanet.c source file

- `new_best_positions.txt` The residue positions used for prediction

- `residue_properties.mat` The residue encoding matrix

- `papanet` This is the executable for the neural network built from the
  `final_trained.net` network file using snns2c
