#!/bin/bash

if [ "X$1" == "X" ]; then
   dest=$HOME/bin
else
   dest=$1
fi

echo "Building the code..."
touch src/papanet.*
(cd src; make clean; make)

echo -n "Installing the software in $dest ..."
mkdir -p $dest/share/papa
cp -R share/papa/* $dest/share/papa
cp papa.pl  $dest
(cd $dest; ln -sf papa.pl papa)
echo "done"
