#! /usr/bin/env bash


r=0;
for f in src/*/*.h; do
#    echo -n '.';  ## show progress

    z=0;
    perl scripts/chksrc.pl < $f  ||  { r=1; z=1; }
    if [ $z = 1 ]; then echo; echo "   ^-- src-file = $f"; fi;
done;

echo;
exit $r;


######################


