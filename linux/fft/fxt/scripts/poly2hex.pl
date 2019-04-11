
## convert polynomials (as coefficient list) into hexadecimal numbers

## input: lines of the form
# a,b,c,...,q
## output: the hexadecimal numbers
# 2^a + 2^b + 2^c + ... + 2^q

# grep -v \# data/lowbit64-primpoly.txt | head -n 10 | perl foo.pl

use Math::BigInt;

$e = Math::BigInt->new('1');
$s = Math::BigInt->new('0');

while ( <STDIN> )
{
    @z = split /,/;
    $s = 0;

    foreach $t ( @z )  { $s += ( $e << $t ); }
#    foreach $t ( @z )  { $s += ( $e << (64-$t) ); }  ## OPTION: reverse 64-bit polys

#    $s -=  ( $e << ($z[0]) );  ## OPTION: omit leading coefficient
#    print "n=$z[0]:\n";  ## OPTION: print degree
    print ($s->as_hex());

    print "ULL"; ## OPTION: long long marker for C
    print "\n";
}

##################
