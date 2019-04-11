#! /usr/bin/perl -w

##  perl -w 2c.pl < mersenne-factorizations-400.txt > mersprimefact.h

#use strict;

$debug = 0;


$maxprime="18446744073709551615";  # == 2^64-1


sub get_prime
{
    if ( "$po" <= $maxprime )
    {
        $debug && print "$po"."UL,\n";
        push @ft, $po;
    }
    else
    {
        $debug && print "/*"."$po"."UL, */\n";
    }
}
##############################


$ct=0;
@ft=();
while ( <STDIN> )
{
    $debug && print "\n // --- $_";

    chomp;
    $ff=$_;
    $debug && print "[ct=$ct]\n";

    $ff =~ s/([0-9]+): (.*)/$2/;
    $mx=$1;
    $e=1;
    $po=1;

    $debug && print "// $mx \n";
    while ( $ff =~ s/([0-9]+).?(.*)/$2/ )
    {
        $ct++;
        $p=$1;
#        $debug && print "  p=[$p]\n";
        if ( $p == $po )
        {
            $e = $e + 1;
        }
        else
        {
            if (  $po!=1 )
            {
                &get_prime();
            }
            $e = 1;
        }

        $po = $p;
    }
    &get_prime();

    if ( $mx >= 128 )  { goto end_loop; }
}
#print '} /* end mersfact_tab[] */'."\n";
end_loop: ;

############################


@ft = sort {$a <=> $b} @ft;

print 'extern const umod_t ';
print 'mersenne_prime_factor_tab[] =' . "\n{\n";

$to=1;
foreach $t ( @ft ) # uniq
{
    if ( $t != $to )
    {
        print " $t"."ULL,\n";
        $to = $t;
    }
}
print ' 0 /* termination */'."\n";
print "};\n";


########################################################
########################################################
