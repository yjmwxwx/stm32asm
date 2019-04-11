#! /usr/bin/perl -w

# recognized timings output for either of
#
## zsh builtin time:
#export TIMEFMT='%J %U user %S system %P cpu %E total';
## /usr/bin/time:
#export TIME='%C %U user %S system %P cpu %e total';

#######################

$D = 0; ## whether debug (verbose) mode

$E = 0; # to skip to first program, set to 1 to parse fxt-demos
$ct = 0;
$time = 0;
$xfer = 0;

sub clear_vars()
{
#    print "CLEAR_VARS\n";
    $ct = 0;
    $time = 0;
    $xfer = 0;
};

#sub fmt_val()
#{
#    my $ps = shift;
#    my $t = int( $ps );
#    my $p0 = $t % 1000;  $t -= $p0;  $t /= 1000;
#    my $p1 = $t % 1000;  $t -= $p1;  $t /= 1000;
#    my $p2 = $t % 1000;  $t -= $p2;  $t /= 1000;
#    my $p3 = $t % 1000;            # $t -= $p3;  $t /= 1000;
#    $D && print " ++++ ========== FMT : [[ $p3 , $p2 , $p1 , $p0 ]]\n";
##    my $fm = "$p3 , $p2 , $p1 , $p0";
#    my $fm = "";
#    if ( $p3 != 0 )  { $fm = "$fm" . "$p3,"; }
#    if ( $p2 != 0 )  { $fm = "$fm" . "$p2,"; }
#    if ( $p1 != 0 )  { $fm = "$fm" . "$p1,"; }
#    if ( $p0 != 0 )  { $fm = "$fm" . "$p0"; }
#    return $fm;
#};

$MHz = $ARGV[0]  || die "Need one argument: CPU frequency in Mhz.";
$Hz = 1_000_000.0 * $MHz;

print "// eval-bench-log: CPU @ $MHz MHz (supplied as argument)\n";

while ( <STDIN> )
{
    chomp;
    $L = $_;

    $D && print "L=[$L]\n";
    !$D && print "$L\n";

    if ( $E == 0 )
    {
        # first benchmark run:
        if ( $L =~ /------------------------------------------------/ )
        {
            $D && print " ++++ FIRST PROG:\n";
            $E = 1;
        }
        next;
    }


#    if ( $L =~ /.*\b([0-9.]+)s user .*cpu .*system .*total/ )
    if ( $L =~ /.* \b([0-9]+\.[0-9]*)s.*user/ )  # found timing line
    {
        $time = $1;
        $D && print " ++++ TIME: $time\n";

        if ( 1 )
        {
            if ( $time==0 )
            {
#                $D &&
                print " ++++ ========== STATS ERROR zero time:  ct=$ct  xfer-$xfer  time=$time\n";
                print STDERR "line $.: ERROR: zero time:  ct=$ct  xfer-$xfer  time=$time\n";
#                exit 1;

                &clear_vars();
                next;
            }

            if ( $ct==0 && $xfer==0 )
            {
                $D && print " ++++ ========== STATS ERROR neither ct nor xfer:  ct=$ct  xfer=$xfer\n";
                print STDERR "line $.: ERROR: neither ct nor xfer set:  ct=$ct  xfer=$xfer\n";
#                exit 1;

                &clear_vars();
                next;
            }

            if ( ($xfer != 0) && ($ct != 0) )
            {
                print STDERR "line $.: WARNING: have both ct and xfer:  ct=$ct  xfer=$xfer\n";
            }


            if ( $ct != 0 ) ## CT stats
            {
                $persec = $ct / $time; # [1 per second]

                $rate = $Hz / $persec; # inverse(!) rate
                $rate = int( $rate * 100.0 ) / 100.0;

                $persec = int($persec); # floor
                $persec = $persec / 1000_000.0;  # [million per second]
#                $fmt = &fmt_val( $persec );
                $D && print " ++++ ========== STATS CT : ct=$ct  time=$time  persec=$persec [M/sec]\n";
                print " ==> $ct/$time == $persec [M per second];  1/rate == $rate [cycles]\n";
            }

            if ( $xfer != 0 ) # XFER stats
            {
                $t = $xfer / $time; # [MB/sec]
                $persec = int( $t * 1_000.0 ) / 1_000.0; # float, truncated after 6 digits

                $rate = $persec / $Hz * 1_000_000.0; # [Byte/cycle]
                $rate = int( $rate * 1000.0 ) / 1000.0;

                $D && print " ++++ ========== STATS XFER:  xfer=$xfer  time=$time  persec=$persec [MB/sec]\n";
                print " ==> $xfer/$time == $persec [MB per second];  rate == $rate [Byte/cycle]\n";
            }

            &clear_vars();
            next;

        }
    }

    if ( $L =~ /xfer[ ]*=[ ]*([0-9]+)[ ]*([kmgte])[ ]?B/i ) # found "xfer=" line
    {
        $num = $1;

        $xfer = $num / 2**20; # [MB]
        if ( $2 )
        {
            $sf = $2;
            $sf = uc($sf);      # upper case
            if ( $sf eq 'K' )  {  $xfer = $num / 2**10; }
            if ( $sf eq 'M' )  {  $xfer = $num; }
            if ( $sf eq 'G' )  {  $xfer = $num * 2**10; }
            if ( $sf eq 'T' )  {  $xfer = $num * 2**20; }
            if ( $sf eq 'E' )  {  $xfer = $num * 2**30; }
        }
        $D && print " ++++ XFER: num=$num sf=[$sf] ==> xfer=$xfer [MB]\n";
    }

    if ( $L =~ /^[ ]*[a-zA-Z]*ct[ ]*=[ ]*([0-9]+)/ ) # found "ct=" line
    {
        $ct = $1;
        $D && print " ++++ CT: $ct\n";
    }

    if ( $L =~ /args=/ )
    {
        $D && print " ++++ ARGS.\n";
        &clear_vars();
        next;
    }

#    if ( $L =~ /^$/ )
#    {
#        $D && print " ++++ EMPTY.\n";
#    }

}
