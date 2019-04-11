#! /usr/bin/env zsh

#set -vx

# from environment:
if [ "$WEBDIR" = "" ]; then exit 1; fi
test -d $WEBDIR || exit 1

B2WDIR=$WEBDIR/bitwizardry/files/
test -d $B2WDIR || exit 1

BWPAGE=$WEBDIR/bitwizardry/bitwizardrypage.html
test -f $BWPAGE || exit 1


## update:
cp -puv src/bits/*.h $B2WDIR/

## silently clean up:
rm $B2WDIR/*.h
cp -pu src/bits/*.h $B2WDIR/


grep '<!--.*files/' $BWPAGE

for f in $B2WDIR/*.h; do
    grep $(basename $f)  $BWPAGE  >/dev/null || \
        echo " ******** Found no link to  $(basename $f) in $BWPAGE";
done;

CHK=$PWD/scripts/chk-bw-page.pl
( cd $B2WDIR  && /usr/bin/perl -w $CHK < $BWPAGE )  || exit 1;



exit 0;
########################
