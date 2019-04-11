
#include "comb/partition-odd-asc-subset-lex.h"

#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Partitions of n into odd parts, subset-lex order.
//% Loopless algorithm.
//% Cf. OEIS sequence A000009.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/composition-nz-subset-lex-demo.cc for compositions in subset-lex order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 19;
    NXARG(n, "partitions of n");

    partition_odd_asc_subset_lex P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef PARTITION_ODD_ASC_SUBSET_LEX_FIXARRAYS
    cout << "PARTITION_ODD_ASC_SUBSET_LEX_FIXARRAYS defined." << endl;
#endif
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
//    ulong C[64];
    do
    {
#if 0
        bool qq = 1;
        for (ulong j=1; j<m; ++j)  // only distinct parts: A000700
            if ( P.data()[j-1] == P.data()[j]  )  { qq=0;  break; }
        if ( !qq )  continue;
#endif

        cout << setw(4) << ct << ":";

        cout << "  [" << setw(2) << m << "]";

        P.print("  ");


        cout << endl;

//        jjassert( m <= n );
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
./bin 220  7.19s user 0.00s system 99% cpu 7.188 total
 ==> 1586861606/7.19 == 220,703,978 per second

 % time ./bin 220
arg 1: 220 == n  [partitions of n]  default=19
PARTITION_ODD_ASC_SUBSET_LEX_FIXARRAYS defined.
 ct=1586861606
./bin 220  7.56s user 0.00s system 99% cpu 7.568 total
 ==> 1586861606/7.56 == 209,902,328 per second

*/

/*
BENCHARGS=220
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-odd-asc-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-odd-asc-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

