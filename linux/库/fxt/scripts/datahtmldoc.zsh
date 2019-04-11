#! /usr/bin/env /bin/zsh

## create the "mathematical data" web page

cat <<EOF
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">
<HTML>
<HEAD>
<META NAME="author" CONTENT="Joerg Arndt">
<META NAME="keywords"  CONTENT="mathematical data, ugly, useful">
<META NAME="description" CONTENT="tables of mathematical data">
<META NAME="robots" CONTENT="index,follow">
<META NAME="generator" CONTENT="script">
<META HTTP-EQUIV="Content-Type" content="text/html; charset=iso-8859-1">
<META HTTP-EQUIV="content-language" CONTENT="en">
<!-- this href="http://www.jjj.de/mathdata/index.html" -->
<TITLE>jj's useful and ugly page of mathematical data</TITLE>
</HEAD>

<BODY bgcolor="#fffff0" text="#000000">

<HR NOSHADE><!-- ================================== -->
<h1 align="center">
<FONT COLOR="#ff0020">
Tables of mathematical data
</FONT>
</h1>

These files are part of the <A HREF="/fxt/">fxt</A> package.
For background information see the
<a href="/fxt/fxtpage.html#fxtbook">fxtbook</a>.

<HR NOSHADE><!-- ================================== -->
EOF

###########################

for f in data/*.txt; do
    b=$(basename $f);
    echo "<A HREF=\"$b\">$b</A>:";
    echo '<PRE>'
    grep -B25 -F '#.' $f | grep -v -F '#.' ;
    echo '</PRE>'
    echo '<P>'
done

###########################


cat <<EOF
<HR NOSHADE><!-- ================================== -->

Your
<a href="/joerg.html#contact">feedback</a>
is appreciated.

<br>
<ADDRESS>jj (J&ouml;rg Arndt)</ADDRESS>
<BR>Last modified
EOF

DATE=$(date +'%Y-%B-%d (%H:%M)'); # date and time: 2002-June-16 (23:00)
echo $DATE

cat <<EOF
<HR NOSHADE><!-- ================================== -->
Goto
<a href="/joerg.html">
jj's ugly Homepage</a>

</BODY>
</HTML>
EOF

exit 0;
#############################
