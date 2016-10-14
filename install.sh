#!/usr/bin/bash

if [ "X$1" == "X" ]; then
   scripts=$HOME/scripts
else
   scripts=$1
fi

echo "Installing the software in $scripts"

mkdir -p $scripts
cp -R papalib $scripts
cp papa.pl    $scripts
(cd $scripts; ln -sf papa.pl papa)

