#! /usr/bin/perl -w

## scripts/extract-oeis-anums.pl $DD $FH | sort -u | less

## called by target 'oeis'
########## extract OEIS sequence numbers (A-numbers) from files:

while ( <> )
{
    chomp;
    $line = $_;

    while ( $line =~ /(.*?)(A[0-9]{6})\b(.*)$/ )
    {
        $pref = $1;
        $anum = $2;
        $line = $3;

        print "$anum:  $ARGV\n"
            unless ( "$pref" =~ m@1demo.*$@ );
        ## avoid catching /// make-target: "1demo DSRC=demo/seq/A225616-demo.cc"
    }
}

exit 0;
#####################################
