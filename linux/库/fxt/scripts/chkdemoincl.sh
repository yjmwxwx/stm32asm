#! /usr/bin/env bash

XDSRC=demo/*/*-demo.cc
#XDSRC="*/*.cc */*.h"

Q=0
for f in $XDSRC; do
#    echo " ---- $f: -------";
#    echo -n ".";
    if grep -F 'demo-is-self-contained' $f >/dev/null ; then
        : # nothing
    else
        HDRS=$(perl -w scripts/firsthdrs.pl < $f);
        if ! test -n "$HDRS"; then
            echo
            echo " *** [$f] firsthdrs.pl failed (?)" 1>&2;
            Q=1;
        else
            for h in $HDRS; do
                if  test -f $h; then
                    : # ok
                else
                    if test -f src/$h ; then
                        : # ok
                    else
                        echo
                        echo " *** [$f] includes [$h] which does not exist.";
                        Q=1;
                    fi
                fi
            done
        fi
    fi
done
#echo
echo 'OK.'

exit $Q;
################################
