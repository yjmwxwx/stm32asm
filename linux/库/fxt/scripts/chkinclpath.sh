#!/usr/bin/env bash

# supplied from environment:
# FXTSRCDIRS

H=''
for f in ${FXTSRCDIRS}; do  H="$H "$(echo $f/*.h);  done;
#echo "H=[[$H]]"
S=$H
shopt -s nullglob # allow dirs without any *.h
for f in ${FXTSRCDIRS}; do  S="$S "$(echo $f/*.cc);  done;
shopt -u nullglob
#echo "S=[[$S]]"

B=''
for f in ${H}; do  B="$B "$(basename $f);  done;
#echo "B=[[$B]]"

##################

echo 'Checking whether every header is included with correct path:'
for b in $B; do
#    echo -n '.'  ## show progress

    i=$(grep '^#include ''"'$b'"'  $S)
    test -z "$i" || { echo "wrong include(s) for [$b]:";  echo "[[$i]]";  exit 1; }
done;

#echo;
echo 'OK.'

exit 0;
##########################################
