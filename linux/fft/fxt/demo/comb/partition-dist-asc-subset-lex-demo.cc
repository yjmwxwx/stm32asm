
#include "comb/partition-dist-asc-subset-lex.h"

#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions into distinct parts.
//% Representation as list of parts in increasing order.
//% Subset-lex order.
//% Only the last two positions in a partition at the end change.
//% Loopless algorithm.
//% Cf. OEIS sequence A000009.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/composition-nz-subset-lex-demo.cc for compositions into positive parts in subset-lex order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 19;
    NXARG(n, "partitions of n");

    partition_dist_asc_subset_lex P(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
//    ulong C[64];
    do
    {
#if 0
        bool q = 1;
        for (ulong j=0; j<m; ++j)  // only odd parts
            if ( 0==(P.data()[j] & 1UL) )  { q=0;  break; }
        if ( !q )  continue;
#endif

        cout << setw(4) << ct << ":";

        cout << "  [" << setw(2) << m << "]";

        P.print("  ");


        cout << endl;

        jjassert( P.OK() );

        ++ct;
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 220
arg 1: 220 == n  [partitions of n]  default=19
  ct=1586861606
./bin 220  5.26s user 0.00s system 99% cpu 5.260 total
 ==> 1586861606/5.26 == 301,684,715 per second

*/

/*
BENCHARGS=220
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-dist-asc-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-dist-asc-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

