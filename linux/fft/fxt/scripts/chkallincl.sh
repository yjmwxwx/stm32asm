#!/usr/bin/env bash

#
# check which headers are included by *-all.h
#

# supplied from environment:
# FXTSRCDIRS
# NONSRCDIRS
#echo "FXTSRCDIRS=${FXTSRCDIRS}"
#echo "NONSRCDIRS=${NONSRCDIRS}"

IDIR=./src
#DIRS=$*
AHDRS=$(echo ${IDIR}/*-all.h)
#echo "$0: [[$AHDRS]]";


#################
echo '(1) every f in FXTSRCDIRS must have a corresponding src/$f-all.h:'
for f in ${FXTSRCDIRS}; do
#    echo -n '.';  ## show progress

    a=$f-all.h
    test -f $a || { echo "no file [$a]";  exit 1; }
done;
echo;
echo 'ok(1).'

#################
echo '(2) checking files actually included in *-all.h (existence and correct place):'
for a in ${AHDRS}; do
#     echo  "--- $a:"
#    echo -n '.';  ## show progress

    b=$(basename $a)
    ## headers actually included:
    ii=$(grep -E '^#include "' $a | cut -d'"' -f2);
    for i in $ii; do
#        echo "+[$i]+"

        ## "foo.h" is "./include/foo.h"
        test -f ${IDIR}/$i  &&  continue;

        ## "bar/foo.h": exists:
        test -f $i || { echo; echo " *** cannot find file [$i] included in $a"; exit 1; }

        ## "bar/foo.h" must only be included by bar-all.h:
        d=$(dirname $i);
#        echo "+[$d]+"
        test "$d-all.h" != "$b" && { echo; echo " *** wrong include: [$i] is included by $a"; exit 2; }
    done;
done;
echo;
echo 'ok(2).'

#################
echo '(3) every header from any FXTSRCDIRS must be included in some include/*-all.h:'
H=''
H=$(cd src && find . -mindepth 2 -maxdepth 2 -name \*.h)
#echo "H=[[$H]]"
for f in $H; do
#    echo -n '.';  ## show progress

    x=${f#./}
    i=$(grep '^#include ''"'$x'"'  ${AHDRS})
    if test -z "$i" ; then
        x1=${x%/*}
#        if  grep '^//jjnoxchk' $x >/dev/null ; then
#            : ; ## OK
#        else
            echo
            echo "no include for [$x] in src/${x1}-all.h";
            exit 1;
#        fi;
    fi;
done;
echo;
echo 'ok(3).'


echo 'OK.'

exit 0;
##########################################
