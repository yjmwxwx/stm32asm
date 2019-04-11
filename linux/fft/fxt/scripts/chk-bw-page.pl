#! /usr/bin/perl -w


$q=0;
while ( <STDIN> ) ## STDIN == bitwiz page
{
#    { print "+"; }
    if ( /<A HREF="files\/(.*\.h)">(.*\.h)<\/A>/ )
    {
        $L = $1;
        $F = $2;
#        { print "[$L] , [$F]\n"; }

        if ( $L ne $F )  { print "[$L] != [$F]\n";  $q=1; }
        if ( ! -f $F )  { print "no such file: [$F]\n";  $q=2; }
    }
}


exit $q;
########################
