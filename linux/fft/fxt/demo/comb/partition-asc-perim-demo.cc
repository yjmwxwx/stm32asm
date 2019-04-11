
#include "comb/partition-asc-perim.h"

#include "sort/sort.h"  // is_sorted()

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Partitions into parts of 2 sorts where sorts are oscillating.
//% These are conjectured to be equinumerous with
//%   non-empty sets of non-negative integers with perimeter n,
//%   as defined in OEIS sequence A182372.
//% Representations as weakly ascending lists.
//% Lexicographic order: major order by sorts, minor by parts.


// Cf. seq/A182372-demo.cc
// Cf. comb/partition-asc-sorts-demo.cc (partitions; lex: major by sorts, minor by parts)


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 13;
    NXARG(n, "partitions of n");

    partition_asc_perim P(n);

    ulong ct = 0;

#ifdef TIMING
    P.first();
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ulong m = P.num_parts();
    do
    {
//        if ( ! P.first_sort() )  continue;  // only first sort ==1, A227135
//        if ( P.first_sort() )  break;  // only first sort ==0, A227134

        ++ct;

        cout << setw(4) << ct << ":";
        P.print("  ");
//        P.print_rev("  ");  // print in weakly descending order
//        P.print_by_sorts("  ");
        cout << endl;

        jjassert( P.OK() );
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

gcc 4.8.0:

 time ./bin 170
arg 1: 170 == n  [partitions of n]  default=13
 ct=1270747344
./bin 170  7.87s user 0.00s system 99% cpu 7.877 total
 ==> 1270747344/7.87 == 161,467,260 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-perim-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-perim-demo.cc DEMOFLAGS=-DTIMING"
/// End:

