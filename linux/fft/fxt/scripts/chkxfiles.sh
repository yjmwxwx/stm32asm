#! /usr/bin/env bash


ret=0;

TT=$(ls -1 | sort)

FF=$(ls -1 ${OKFILES} | sort)
DD=$(ls -1d ${OKDIRS} | sort)

#echo "FF=$FF"
#echo "DD=$DD"
#echo "TT=$TT"

#set -vx

for f in ${FF}; do  ## remove known files from list
#    echo "FF: checking [$f]"
    test -f $f || { echo " *** no file [$f] (as listed in OKFILES)" 1>&2; ret=1; }
    TT=${TT/$f/};  # unsafe: can remove part of names, e.g., autodoc.log --> auto.log
done

for d in ${DD}; do  ## remove known dirs from list
#    echo "DD: checking [$d]"
    test -d $d || { echo " *** no dir [$d] (as listed in OKDIRS)" 1>&2; ret=1; }
    TT=${TT/$d/};
done

#echo "TT=$TT"
for t in ${TT}; do ## what remains should not be there
#    echo "TT: [$t]"
    echo " *** SPURIOUS FILE/DIR: [$t]" 1>&2;
    ret=1;
done

if [ $ret != 0 ]; then
    echo " *** remove file(s) or edit OKFILES OKDIRS in makefile!" 1>&2;
fi

exit $ret;
##########################
