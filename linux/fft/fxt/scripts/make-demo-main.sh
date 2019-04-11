#! /usr/bin/env bash

############## generate html page:

cat <<EOF
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">
<HTML>
<HEAD>
<TITLE>The fxt demos: main page</TITLE>
<META NAME="author" CONTENT="Joerg Arndt">
<META NAME="description" CONTENT="Demos of the FXT package">
<META NAME="generator" CONTENT="script">
<META NAME="robots" CONTENT="index,follow">
<META HTTP-EQUIV="content-language" CONTENT="en">
<META HTTP-EQUIV="Content-Type" content="text/html; charset=iso-8859-1">
<!-- GENERATED_FILE DEMO2WEB_MAGIC -->
</HEAD>
<BODY bgcolor="#fffff0" text="#000000">
<H1>The fxt demos: main page</H1>
<P>
EOF

for d in $DDIRS; do
    S="${d##*/}"
    PAT="^${S}@"
#    TITLE1=$(grep $PAT $TOPICSTXT | cut -d@ -f2)
    TITLE2=$(grep $PAT $TOPICSTXT | cut -d@ -f3)
#    echo "<A href=\"$S/\">$S</A>: $TITLE2"
    echo "<A href=\"$S/index.html\">$S</A>: $TITLE2"
    echo '<P>'
done


cat <<EOF
</BODY>
</HTML>
EOF



exit 0;
#############################
