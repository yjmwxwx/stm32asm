#! /usr/bin/perl -w

## not needed anymore with gcc option -MT (see makefile)

# insert directory parts into dependency files
#
# usage:
# fixdepend.pl 'obj-list-with-paths' < depend.mk > depend.fixed
# (followed by: mv depend.fixed depend.mk)
#
# by Joerg Arndt (arndt (AT) jjj.de)
# version: 2012-October-09


$objlst = $ARGV[0];

@objn= split(/ /,$objlst);
$n = scalar @objn;

foreach $t (@objn)
{
    if ( $n<=0 )  { goto therest; }
    $n--;

    @z = split( /\//, $t );
    $file = $z[-1];
    $qfile = quotemeta($file);

    while ( <STDIN> )
    {
        $line = $_;
        if ( $line =~ /($qfile:) *(.*)$/ )
        {
            print "$t: $2\n";
            goto endloop;
        }
        print;
    }

  die 'AARGH, cannot read STDIN';

  endloop: ;
}

therest:
while ( <STDIN> )  { print; }

exit 0;

##########################
##########################
