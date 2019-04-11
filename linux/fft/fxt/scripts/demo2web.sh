#! /usr/bin/env bash

# author: Joerg Arndt
# version: 2012-May-20

#set -vx

export LC_ALL=C

#JJTMP=/tmp/demo2web/
#mkdir -p ${JJTMP}
#rm -rf ${JJTMP:?}/*  ### !!!  RM  !!!
#mkdir -p ${JJTMP}


#function pv () { true; }
#function pv () { for x in $*; do eval "echo $x==\$$x"; done }

test -n "$WEBDEMOLOC" || { echo " *** WEBDEMOLOC not set in environment." 1>&2; exit 1; }
test -d "$WEBDEMOLOC" || { echo " *** $WEBDEMOLOC: no such directory." 1>&2; exit 1; }

test -n "$FXTLOC" || { echo " *** FXTLOC not set in environment." 1>&2; exit 1; }
test -d "$FXTLOC" || { echo " *** $FXTLOC: no such directory." 1>&2; exit 1; }

FIRSTHRDS=$FXTLOC/scripts/firsthdrs.pl
test -f "$FIRSTHRDS" || { echo " *** $FIRSTHRDS: no such file." 1>&2; exit 1; }
MKLIST=$FXTLOC/scripts/make-demo-list.sh
test -x "$MKLIST" || { echo " *** $MKLIST: not an executable file." 1>&2; exit 1; }

echo  "$0: topics from demo/topics.txt"  1>&2;
TOPICSTXT=$FXTLOC/demo/topics.txt

DDIRS=$(find $WEBDEMOLOC  -mindepth 1  -type d | sort);
#DDIRS2=$(grep -vE '^#' demo/topics.txt | sed 's/@.*$//g;');
#test "${DDIRS}" \!= "${DDIRS2}" && { echo  "$0: demo/topics.txt does not contain all directories in demo/ (exiting)"  1>&2; exit 1; }

for d in $DDIRS; do
    X=$(grep "^${d##*/}@" $TOPICSTXT | cut -d@ -f1,2)
    test -n "$X" || { echo " *** Missing description for [$d]." 1>&2; exit 3; }
    echo "  $X"
    D=$PWD;
    cd $d  ||  exit 2;
#    FXTLOC=$FXTLOC $MKLIST > 00main.html  ||  exit 3;
## make OEIS links:
    FXTLOC=$FXTLOC $MKLIST |  sed -r 's/ (A[0-9]{6})\b/ <a href="http:\/\/oeis.org\/\1">\1<\/a>/g'  > 00main.html  ||  exit 3;
    ln -sf 00main.html index.html;
    lshtml > files.html;
    cd $D;
done

cd $WEBDEMOLOC
MAINMAIN=00main.html
TOPICSTXT=$TOPICSTXT DDIRS=$DDIRS $FXTLOC/scripts/make-demo-main.sh > $MAINMAIN
#echo "XXXXXXXXXX $PWD"
lshtml > files.html
ln -sf $MAINMAIN index.html

exit 0;
#############################
