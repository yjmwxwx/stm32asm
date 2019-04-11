#/usr/bin/perl -w

$r=0;
$P = '[a-zA-Z0-9_.\-]+';
while ( <STDIN> )
{
    chomp;
    $L = $_;
    unless ( $L =~ /^\/\/ *($P\/$P):$/ )  { next; }
    $F = $1;
#    print " $F\n";
    unless ( -f "src/$F" )
    {
        print "$L  [no such file]\n";
        $r = 1;
    }
}

exit $r;
#########################
