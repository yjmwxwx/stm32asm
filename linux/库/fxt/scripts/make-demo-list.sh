#! /usr/bin/env bash

#echo "PWD = [$PWD]"
#ls -lF
#exit 0;

## called by demo2web.sh
############## generate html page:

FIRSTHDRS=$FXTLOC/scripts/firsthdrs.pl
#test -f "$FIRSTHRDS" || { echo " *** $FIRSTHRDS: no such file." 1>&2; exit 1; }

#exec 1<>${JJTMP}/00main.html

PAT="^${PWD##*/}@"
TITLE1=$(grep $PAT $FXTLOC/demo/topics.txt | cut -d@ -f2)
TITLE2=$(grep $PAT $FXTLOC/demo/topics.txt | cut -d@ -f3)

cat <<EOF
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">
<HTML>
<HEAD>
<TITLE>The fxt demos: $TITLE1</TITLE>
<META NAME="author" CONTENT="Joerg Arndt">
<META NAME="description" CONTENT="$TITLE2">
<META NAME="generator" CONTENT="script">
<META NAME="robots" CONTENT="index,follow">
<META HTTP-EQUIV="content-language" CONTENT="en">
<META HTTP-EQUIV="Content-Type" content="text/html; charset=iso-8859-15">
<!-- GENERATED_FILE DEMO2WEB_MAGIC -->
</HEAD>
<BODY bgcolor="#fffff0" text="#000000">
<H1>The fxt demos: $TITLE1</H1>
Directory ${PWD##*/}: $TITLE2
<BR>
Find a list of all files in this directory <a href="files.html">here</a>.
An index of all topics is <a href="../">here</a>
<P>

You may want to look at the outputs first.
<P>

EOF


ALLHDRS="";
for f in *-demo.cc; do
    g=${f/-demo.cc/-out.txt}
    test -f "$g" || { echo " *** file [$g] is missing " 1>&2;  exit 1; }

#    sf=${f#demo/}
#    sg=${g#demo/}
    sf=$f;  sg=$g;

    echo "<!-- ---------- $f ---------- -->";
    echo "<a name=\"${f/-demo.cc/}\"></a>"
    echo "<a href=\"$sg\">$sg</a> is the output of <a href=\"$sf\">$sf</a>.";
    echo '<BR>'
#    echo "Description:";
    echo '<B>'
    grep -F '//%' $f | cut -d'%' -f2-
    echo '</B>'
    echo '<BR>'

    if grep -F 'demo-is-self-contained' $f >/dev/null ; then
        : # nothing
    else
        HDRS=$(perl $FIRSTHDRS < $f);
        test -n "$HDRS" || { echo " *** firsthdrs.pl failed (?)" 1>&2;  exit 10; }
        echo "The demo uses the functions from"
        for h in $HDRS; do
            hf=$h
            h=$(basename $h)
            echo "<a href=\"$h\">$h</a> (fxt/$hf)";
            ALLHDRS="$ALLHDRS $hf";
        done
    fi
    echo '<P>'
done

cat <<EOF
</BODY>
</HTML>
EOF


############# copy included files:

test -n "$FXTLOC" || { echo " *** $FXTLOC not set in environment." 1>&2; exit 1; }
test -d "$FXTLOC" || { echo " *** $FXTLOC: no such directory." 1>&2; exit 1; }

SUHDRS=$(for h in $ALLHDRS; do echo $h; done | sort | uniq )
TT=""
for h in $SUHDRS; do ## prepend "include/" where needed
    if ! test -f "$FXTLOC/$h"; then
        h=include/$h;
    fi
    test -f $FXTLOC/$h  ||  { echo " *** $h: no such file." 1>&2; exit 1;}
    TT="$h $TT";
done;
SUHDRS=$TT

## copy them to current dir:
for h in $SUHDRS; do
    cp -a $FXTLOC/$h . ;
done;


exit 0;
#############################
