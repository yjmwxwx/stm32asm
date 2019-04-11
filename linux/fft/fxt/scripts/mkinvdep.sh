#!/usr/bin/env bash

## we need replace:
REPLACE='./scripts/replace'
#test -x $REPLACE || { echo "Need replace script!  (exiting)" 1>&2; exit 1; }

## we need this file:
INP=tmp-depend-h.mk
test -f $INP || { echo "Need file $INP as input!  (exiting)" 1>&2; exit 1; }

## output:
INVDEP=depend.inv
## temporaries:
NNDEP=tmp-depend.nn
LEFT=tmp-dep-left

################################


## create dependency file without linebreaks:
cp $INP $NNDEP
${REPLACE} -f -q '\\\\\\n' '' $NNDEP > /dev/null # connect lines
${REPLACE} -f -q '[ ][ ]+' ' ' $NNDEP > /dev/null # normalize blanks
#cp $NNDEP tmp-xxx
${REPLACE} -f -q 'src/[^/]+-all\.h:.*$' '' $NNDEP > /dev/null # omit src/*-all.h

################################


cut -d: -f1 $NNDEP > $LEFT
#cut -d: -f1 $NNDEP | grep -Ev 'src/[^/]+-all\.h\b' > $LEFT # omit src/*-all.h

rm -f $INVDEP

for F in $(cat $LEFT); do

    X=$(grep -E "\b$F\b" $NNDEP | cut -d':' -f1);

    if test "${F/%\.cc/}" \!= "$F" ; then
        # *not* pure self-dependence?
        test "$X" \!= "$F" && { echo "$F depends in [$X]" 1>&2; exit 1; };
        continue;
    fi

#    test "$X" = "$F" && continue;  # skip pure self-dependence

    echo -n "$F: " >> $INVDEP;

#    echo $X >> $INVDEP; # including self-dependence
    PT=${F//\//\\/}; # filename (self) as pattern for sed
    echo $X | sed -r "s/$PT[ ]?//;" >> $INVDEP; # drop self-dependence

done

sort $INVDEP -o $INVDEP


exit 0;
################################
################################

## find files nothing from src/** depends on:
grep -E ': $' depend.inv

## put those into ND:
ND=$(echo $(grep -E ': $' depend.inv) | tr -d : | sed 's/src\///g;') 

## check whether demos depend on them:
for F in ${ND}; do echo -n "$F: "; echo $(grep -l $F demo/*/*cc) ; done
