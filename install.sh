#!/bin/bash

if [ "X$1" == "X-h" ]; then
   echo ""
   echo "Usage: ./install.sh [destination [force]]"
   echo ""
   echo "- Run with no parameters to install in ~/bin"
   echo "- Alternatively specify the destination after ./install.sh"
   echo "- If you specify the destination, you may also add the 'force'"
   echo "  keyword to force use of a new trained network."
   echo "  You must have SNNS installed to do this!"
   echo ""
   exit 0
fi

if [ "X$1" == "X" ]; then
   dest=$HOME/bin
else
   dest=$1
fi

if [ "X$2" == "X" ]; then
   touch src/papanet.*
else
   touch src/*.net
fi

echo "Building the code..."
(cd src; make clean; make)

echo -n "Installing the software in $dest ..."
mkdir -p $dest/share/papa
cp -R share/papa/* $dest/share/papa
cp papa.pl  $dest
(cd $dest; ln -sf papa.pl papa)
echo "done"
