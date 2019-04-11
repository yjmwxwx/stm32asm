#!/usr/bin/env bash

#
echo 'Checking that header files have canonical #ifdefs against multiple inclusion:'

#echo '*** XXX FIXME: temporarily disabled ***';  exit 0;


#
# For example, a header file foo.h should have:
#
# #if !defined HAVE_FOO_H__
# #if define HAVE_FOO_H__
# [-- code --]
# #endif  // !defined HAVE_FOO_H__


KEEPGOING=0;
while getopts :k OPT; do
    case $OPT in
        k|+k) KEEPGOING=1;
            ;;
#        *)
#            usage;
#            exit 2
    esac
done
shift $[ $OPTIND - 1 ]


HDRS=$*
if [ "$HDRS" = "" ]; then
    HDRS=$(find . -name \*.h)
fi

for f in $HDRS; do
#    echo -n '.'  ## show progress

    export b=$(basename $f .h | tr 'a-z\-' 'A-Z_' );

    CAN="HAVE_${b}_H__";

    L1="#if !defined  $CAN";
    L2="#define       $CAN";
    L3="#endif // !defined $CAN";

    CT=$(grep -E "\b$CAN\$" $f | wc -l);
    if [ $CT -lt 3 ];  then  # test should be sharpened

#    OK="jawoll";
#    T=$(grep  "^${L1}\$" $f);    test "${L1}" = "$T"  || OK="";
#    T=$(grep  "^${L2}\$" $f);    test "${L2}" = "$T"  || OK="";
#    T=$(grep  "^${L3}\$" $f);    test "${L3}" = "$T"  || OK="";
#    if [ -z ${OK} ];  then

        echo
        echo " *** OOPS, $f doesn't seem to have the canonical #ifdefs:"
        echo " *** should be: "
        echo "LINE  1 & 2 & -1:"
        echo "${L1}"
        echo "${L2}"
        echo "${L3}"
        echo "first two lines are:"
        head -2 $f;
        echo "last line is:"
        tail -1 $f;
        echo "--- error in HDR = [$f]";

#        replace "^(#.+) [A-Z0-9_]+_H\$" "\$1 HAVE_${b}_H__" $f;
#        replace "^(#.+) HAVE_.+_H__\$" "\$1 HAVE_${b}_H__" $f;
        if [ $KEEPGOING -ne 1 ]; then
            exit 1;  ## fail
        fi

    fi
done

echo;  echo 'OK.'
exit 0

############################
#
#    replace "^(#.+) [A-Z0-9_]+_H\$" "\$1 HAVE_${b}_H__" $f;
#
#    echo "b=[$b]";
#    echo "\$1 HAVE_${b}_H__"
#    replace '^(#.*defin.+) __[A-Z0-9_]+$' "\$1 HAVE_${b}_H__" $f;
#
#XX=$(for f in $(find . -name \*.h); do \
#    if [ "3" != $(grep -E 'HAVE_[A-Z0-9_]+_H__' $f | wc -l) ]; then echo $f; fi; \
#done)
#echo "$XX"
#
#for f in $XX; do
#  echo "-------- $f: --------";
#  grep -E -C3 'HAVE_[A-Z0-9_]+_H__' $f;
#done
#
#ee $XX
#
