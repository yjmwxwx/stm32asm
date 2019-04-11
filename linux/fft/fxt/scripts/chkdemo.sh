#! /usr/bin/env bash

export LC_ALL=C

OUT=$(echo demo/*/*-out.txt)
rm -f tmp-out
for f in ${OUT}; do
    echo $(dirname $f)/$(basename $f -out.txt) >> tmp-out;
done
sort tmp-out -o tmp-out

SRC=$(echo demo/*/*-demo.cc)
rm -f tmp-src
for f in ${SRC}; do
    echo $(dirname $f)/$(basename $f -demo.cc) >> tmp-src;
done
sort tmp-src -o tmp-src



#exit 1; ######################

######### (-1) ########
## make sure demo source exists for all outputs:

for f in $(< tmp-out); do
    S=$f-demo.cc;
    O=$f-out.txt;
    if test -f $S; then
        : ;  # OK
    else
        echo "Have file $O but no $S (remove $O?) !" 2>&1;
        exit 1;
    fi
done


######### (0) ########
echo '(0) every demo/*-demo.cc must have a description //% bla:';

NDS=''
for f in $(< tmp-src); do
    S=$f-demo.cc;
    if ! grep '^//%' $S >/dev/null; then
        NDS="$NDS $S";
    fi
done

if test -n "${NDS}"; then
    echo "files lacking a description:" 2>&1
    echo "${NDS}" 2>&1
    echo 'Add a description! (0)' 2>&1
    exit 1;
fi
echo 'ok(0)'


######### (1) ########
echo '(1): check whether the sets of files *-out.txt and *-demo.cc differ:';


DIFF=$(diff tmp-out tmp-src)
if test -n "${DIFF}"; then
    echo "${DIFF}" 2>&1
    echo 'Do a "make ntdemo" ! (1)' 2>&1
    exit 1;
fi
echo 'ok(1)'


######### (2) ########
echo '(2): check whether any xyz-out.txt is older than xyz-demo.cc:';

NT=''
for f in $(< tmp-src); do
    S=$f-demo.cc;
    O=$f-out.txt;
    if test $S -nt $O; then
        NT="$NT $S";
    fi
done

if test -n "${NT}"; then
    echo "${NT}" 2>&1
    echo 'Do a "make ntdemo" ! (2)' 2>&1
    exit 1;
fi
echo 'ok(2)'


###### cleanup and OK:
rm -r tmp-out tmp-src

echo 'OK.'

exit 0;
#####################
