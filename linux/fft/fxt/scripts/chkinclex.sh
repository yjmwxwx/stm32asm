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
#set -vx
echo 'Checking whether included header files exists:'
for f in $H $S; do
#    echo -n '.';  ## show progress

    f=$f
#    echo "f=[$f]" # including file
    i=$(grep -E '^#include[ ]+"'  $f | cut -d\" -f2 )
    for j in $i; do
        if test -n $j; then
#            echo "    $j"  # included file
            if ! test -f $j; then
                j=src/$j;
                if ! test -f $j; then
                    echo
                    echo "file [$j] included by [$f] does not exist.";
                    exit 1;
                fi
            fi
        fi
    done
done;

#echo;
echo 'OK.'

exit 0;
##########################################
