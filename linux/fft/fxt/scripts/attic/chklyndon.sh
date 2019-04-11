#! /bin/bash

#set -vx

make 1demo DSRC=demo/lyndongray-demo.cc

for c in 0 1 2 3; do
    echo $c;
    ./bin 17 1 $c | grep -v arg > tt$c;
done

for c1 in 0 1 2 3; do
    for c2 in 0 1 2 3; do
        test $c1 -ge $c2 && continue;
        diff -q tt$c1 tt$c2 && echo " $c1, $c2:  equal";
#        diff tt$c1 tt$c2;
    done;
done;


#grep -E '^[0-9A-Z]{100}' tt?
