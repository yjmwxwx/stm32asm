#!/usr/bin/perl -w

# quick hack by Joerg Arndt (arndt (AT) jjj.de)
# version: 2000-March-14 (00h44)

while ( <> )  { /jjmagictag/  &&  last; }

while ( <> )
{
    /jjmagictag/  &&  last;
    if ( /^ *([a-z]+) ([a-zA-Z0-9_]+)\(([^\)]*)\)(.*)/ )
    {
        $rettp = $1;
        $name = $2;
        $sig = $3;
        $rest = $4;
        print "//$rettp $name($sig)$rest\n";
        $_ = $sig;
        s/const //g;
        s/double \*[^,]*/dp/g;
        s/double[^,]*/d/g;
        s/Complex \*[^,]*/cp/g;
        s/Complex[^,]*/c/g;
        s/ulong \*[^,]*/up/g;
        s/ulong[^,]*/u/g;
#        s/ushort[^,]*/ldn/g;
        s/long[^,]*/l/g;
        s/int[^,]*/i/g;
        s/mod \*[^,]*/mp/g;
        s/mod[^,]*/m/g;
        s/wavelet_filter[^,]*/w/g;
        print "$name(";
        print;
        print ");\n";
    }
    else
    {
        print;
    }
}

exit 0;
