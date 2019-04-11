#! /usr/bin/env zsh

DEMOBIN=./bin
#RUNDEMO=$DEMOBIN
TMPDIR=/tmp
DTMP=$TMPDIR/tmp-demo-out
DEMODIR=./demo

## we need GNU make:
#echo "MAKE=$MAKE";
#MAKE=gmake
## Debian (jessie): no gmake
MAKE=make


#echo "MAKEFLAGS=[$MAKEFLAGS]";
## MAKEFLAGS=[ --jobserver-fds=3,4 -j]
## Warning: MAKEFLAGS is unset below
export MAKEFLAGS='';
# make[1]: warning: -jN forced in submake: disabling jobserver mode.


test -n "$WHICH" || WHICH=all

#set -vx

#rm -f $DTMP;
#if [ "$WHICH" = "oout" ]; then # sorted Oldest OUTput first
#    ls -tr $DEMODIR/ds/*-out.txt >  $DTMP;
#    sed -i s/-out.txt$/-demo.cc/ $DTMP;
#    WHICH="all";
#else
    find $DEMODIR -name '*-demo.cc' >  $DTMP;
#fi;

#### do all demos:
if [ "$WHICH" = "all" ]; then
    DSRC=$(<$DTMP);
fi;

#### do all, oldest first:
if [ "$WHICH" = "old" ]; then
    DSRC=$(ls -1tr $(<$DTMP));
fi;

#### do all, run with valgrind:
if [ "$WHICH" = "vg" ];  then # valgrind

    if [ "$DSRC" = "" ]; then DSRC=$(<$DTMP); fi;

    VGBIN='valgrind';
#    VGBIN='/opt/valgrind/bin/valgrind';

#    test -x =valgrind || { echo 'ERROR: install valgrind!';  exit 1; }
    test -x =${VGBIN} || { echo 'ERROR: install valgrind!';  exit 1; }

    VGOPT='--tool=memcheck --leak-check=full --show-reachable=yes --error-exitcode=1';
#    VGOPT='--tool=exp-sgcheck --error-exitcode=1';
    ## NOTE: with sgcheck turn optimization OFF and debugging ON!
#    echo "VGBIN=${VGBIN}";
#    echo "VGOPT=${VGOPT}";
fi;

#### do demos where included header matches the pattern PAT:
if [ "$WHICH" = "header" ]; then
    if [ -z "$PAT" ]; then echo "Empty pattern"; exit 1; fi;
    DSRC=$(grep -lE -- "\#include[ ]+.*$PAT" $DEMODIR/*/*-demo.cc);
    if [ -z "$DSRC" ]; then echo "Pattern did not match"; fi;
fi;

#### do demos where the source contains the pattern PAT:
if [ "$WHICH" = "grep" ]; then
    if [ -z "$PAT" ]; then echo "Empty pattern"; exit 1; fi;
    DSRC=$(grep -i -lE -- "$PAT" $DEMODIR/*/*-demo.cc);
    if [ -z "$DSRC" ]; then echo "Pattern did not match"; fi;
fi;

#### do demos whose filesnames contain the pattern PAT:
if [ "$WHICH" = "files" ]; then
    if [ -z "$PAT" ]; then echo "Empty pattern"; exit 1; fi;
    DSRC=$(grep -E -- ".*$PAT" $DTMP);
    if [ -z "$DSRC" ]; then echo "Pattern did not match"; fi;
fi;

#### do demos that are newer than their output:
if [ "$WHICH" = "nt" ]; then
    DSRC='';
    for f in $(<$DTMP); do
#        OUT=$DEMODIR/$(basename $f -demo.cc)-out.txt;
        OUT=$(dirname $f)/$(basename $f -demo.cc)-out.txt;
        if test -f $OUT; then test $f -nt $OUT  ||  continue; fi;
        DSRC="$DSRC $f";
    done;
fi;



#echo "DSRC=[[$DSRC]]"; exit
if [ -z "$DSRC" ]; then
    echo "Nothing to do.  (?)";
    exit 0;
fi;


if [ "$WHICH" = "old" ]; then
    true; # file-list (oldest first, or by pattern) already done above
else
    DSRC=$(\ls -1t ${=DSRC}); # file-list (newest first)
fi;




XCT=0 # count changed files
NCT=0 # count new files
CT=0 # count demos compiled
for f in ${=DSRC}; do
#    OUT=$DEMODIR/$(basename $f -demo.cc)-out.txt;
    OUT=$(dirname $f)/$(basename $f -demo.cc)-out.txt;
    echo -n "$f --> $OUT    ";

#    exit 1;

    if test -n "$DEMO_DRY_RUN"; then
        echo ' (dry-run)';
        continue;
    fi

    CT=$(($CT+1));

#    $MAKE -s tdemo  DSRC=$f; echo;  continue  ## TEST, just compile

    $MAKE -s 1demo  DSRC=$f > $DTMP
#    $MAKE    1demo  DSRC=$f > $DTMP

    ##
    if test "$?" != "0"; then
#        touch $f; continue; ##
        echo "OOPS !  check $DTMP";
        test -n "$DEMO_KEEP_GOING" && continue;
        ls -l $DTMP; exit 1;
    fi;

#    set -vx;
    if [ "$WHICH" = "vg" ]; then # valgrind

        VGCMD="${VGBIN} ${VGOPT}"

#        ( ulimit -t 10; ${=VGCMD} ./bin 2> tmp-vgdemo >/dev/null; );
        ${=VGCMD} ./bin 2> tmp-vgdemo >/dev/null;  VGRET=$?;

#        echo 1>&2 "VGRET=${VGRET}";

        if [ ${VGRET} = "1" ]; then
            echo;
            echo "  *** valgrind returned VGRET=${VGRET}, indicating an ERROR: ***";
            cat tmp-vgdemo;
        fi
    fi



    if test -f $OUT; then #  *-out.txt already there
        if diff $DTMP $OUT &>/dev/null ; then  # output unchanged
            rm $DTMP;
        else # output did change
            echo -n "  (CHANGED)";
            XCT=$(($XCT+1));
            cp -a $OUT $TMPDIR; ## old version --> /tmp
            mv $DTMP $OUT;
        fi
    else
        echo -n "  (NEW)";
        NCT=$(($NCT+1));
        mv $DTMP $OUT;
    fi

    # make sure output is not older than source:
    if test $f -nt $OUT; then  touch -r $f $OUT;  fi
    echo;
done;

echo "Stats:  $CT done,  $XCT changed,  $NCT new."


exit 0;
##############################

# diff:
#  An exit status of
#     0 means no differences were found,
#     1 means some differences were found, and
#     2 means trouble.
