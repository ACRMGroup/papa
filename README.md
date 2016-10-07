# papa

## Predict Antibody Packing Angle

`papa` uses Abhi Raghavan's method and neural networks to predict the VH/VL packing angle for an antibody. 

Input is a numbered antibody sequence file in the form:

        L1 Q
        L2 V
        L3 E
        ... etc ...

Output is a line containing the packing angle.

## NOTE!

This program relies on having SNNS installed. By default, it is
assumed that the `batchman` program is available in the path. A path
can be specified near the top of the papa.pl script,
