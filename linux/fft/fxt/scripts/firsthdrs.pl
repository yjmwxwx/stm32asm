#/usr/bin/perl -w

## called by demo2web.sh
########## extract names of first headers included by a demo:

$hh = 0;

while ( <STDIN> )
{
    chomp;
    $line = $_;
#    print "[$line]\n";

#    if ( $line =~ /^\/\/ *demo-is-self-contained *\"(.+)\".*$/ )
#    {
#        print 'demo-is-self-contained';
#        exit 0;
#    }

    if ( $line =~ /^\#include *\"(.+\.h)\".*$/ )
    {
        $hdr = $1;
        $hdr="src/".$hdr;
        $hh = 1;
#        print "*** #[$hdr]\n";
        print "$hdr\n";

        next;
    }

    if ( $line =~ /^\/\/ *demo-include *\"(.+)\".*$/ )
    {
        $hdr = $1;
        $hdr="src/".$hdr;
        $hh = 1;
#        print "*** //[$hdr]\n";
        print "$hdr\n";

        next;
    }

    if ( $hh != 0 )  { exit 0; }
}

exit 1;
#####################################
