#! /usr/bin/env bash

type -p mgdiff >/dev/null || { echo "we need mgdiff."; exit 1; }
A=$1;
B=$2;
if [ -d $1 ]; then
    A=$A/$(basename $2);
fi;
if [ -d $2 ]; then
    B=$B/$(basename $1);
fi;

#mgdiff -g 1200x1000+0+0 -args "-dbwB" $A $B
mgdiff -g 1200x1000+0+0 -args "-dw" $A $B

exit 0;
############################
