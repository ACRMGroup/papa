# papa

## Predict Antibody Packing Angle

`papa` uses Abhi Raghavan's method and neural networks to predict the
VH/VL packing angle for an antibody.

Input is a numbered antibody sequence file in the form:

        L1 Q
        L2 V
        L3 E
        ... etc ...

Output is a line containing the packing angle. If run with `-q`, the
output is just the predicted packing angle with no text.

## Installation

This program no longer needs SNNS to be installed.

Build the software by typing

        make

Install the software by typing

        ./install.sh

By default, it will be installed in `$HOME/bin` - you can install
elsewhere by typing (for example)

        ./install.sh /usr/local/bin
