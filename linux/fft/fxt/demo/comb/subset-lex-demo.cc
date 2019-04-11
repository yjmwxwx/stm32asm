
#include "comb/subset-lex.h"

#include "comb/comb-print.h"

//#include "bits/print-bin.h"
//#include "comb/composition-nz-rank.h"

#include "fxttypes.h"

#include "fxtio.h"
#include "nextarg.h"
#include "jjassert.h"


//% Nonempty subsets of the set {0,1,2,...,n-1} in (subset-)lexicographic order.
//% Representation as list of parts.
//% Loopless generation.
//% Cf. OEIS sequence A108918
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Size of the set (n>=1)");
//    jjassert( n>=1 );
    subset_lex S(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef SUBSET_LEX_MAX_ARRAY_LEN
    cout << "SUBSET_LEX_MAX_ARRAY_LEN is defined." << endl;
#endif
    bool dir = 0;
    NXARG(dir, "Benchmark: whether to go backwards");
    if ( !dir )
    {
        cout << "forward:" << endl;
        do  { ++ct; }  while ( S.next() );
    }
    else
    {
        cout << "backward:" << endl;
        S.last();
        do  { ++ct; }  while ( S.prev() );
    }

    cout << "ct=" << ct << endl;

#else  // TIMING

//    ulong C[64];
    ulong num = S.first();
//    ulong num = S.last();
    const ulong *x = S.data();
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
//        cout << "  #=" << setw(2) << num;
        print_set_as_deltaset("    ", x, num, n);

//        ulong r = 0;
//        for (ulong k=0; k<num; ++k)  r |= (1UL << (n-1-x[k]));
//        r ^= ~0UL;
//        print_bin("  ", r, n);
//        ulong nc = composition_nz_unrank(r, C, n+1);
//        print_vec("  ", C, nc);

//        cout << "  " << S.num_parts();
        print_set("    ", x, num);
        cout << endl;
    }
    while ( (num = S.next()) );
//    while ( (num = S.prev()) );

#endif  // TIMING

    return 0;
}
// -------------------------

/*

Timing:

 time ./bin 30 0
arg 1: 30 == n  [Size of the set]  default=5
arg 2: 0 == dir  [Benchmark: whether to go backwards]  default=0
forward:
./bin 30 0  3.94s user 0.00s system 100% cpu 3.943 total
 ==> 2^30/3.94 == 272,523,305 per second

 time ./bin 30 0
arg 1: 30 == n  [Size of the set]  default=5
SUBSET_LEX_MAX_ARRAY_LEN is defined.
arg 2: 0 == dir  [Benchmark: whether to go backwards]  default=0
forward:
./bin 30 0  3.92s user 0.00s system 100% cpu 3.920 total
 ==> 2^30/3.92 == 273,913,730 per second


 time ./bin 30 1
arg 1: 30 == n  [Size of the set]  default=5
arg 2: 1 == dir  [Benchmark: whether to go backwards]  default=0
backward:
./bin 30 1  6.81s user 0.03s system 99% cpu 6.842 total
 ==> 2^30/6.81 == 157,671,339 per second

 time ./bin 30 1
arg 1: 30 == n  [Size of the set]  default=5
SUBSET_LEX_MAX_ARRAY_LEN is defined.
arg 2: 1 == dir  [Benchmark: whether to go backwards]  default=0
backward:
./bin 30 1  5.54s user 0.00s system 99% cpu 5.545 total
 ==> 2^30/5.54 == 193,816,213 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 0
arg 1: 30 == n  [Size of the set]  default=5
arg 2: 0 == dir  [Benchmark: whether to go backwards]  default=0
forward:
./bin 30 0  2.24s user 0.00s system 99% cpu 2.244 total
 ==> 2^30/2.24 == 479,349,028 per second

 time ./bin 30 0
arg 1: 30 == n  [Size of the set]  default=5
SUBSET_LEX_MAX_ARRAY_LEN is defined.
arg 2: 0 == dir  [Benchmark: whether to go backwards]  default=0
forward:
./bin 30 0  2.39s user 0.00s system 99% cpu 2.392 total
 ==> 2^30/2.39 == 449,264,361 per second


 time ./bin 30 1
arg 1: 30 == n  [Size of the set]  default=5
arg 2: 1 == dir  [Benchmark: whether to go backwards]  default=0
backward:
./bin 30 1  3.35s user 0.00s system 99% cpu 3.355 total
 ==> 2^30/3.35 == 320,519,947 per second

 time ./bin 30 1
arg 1: 30 == n  [Size of the set]  default=5
SUBSET_LEX_MAX_ARRAY_LEN is defined.
arg 2: 1 == dir  [Benchmark: whether to go backwards]  default=0
backward:
./bin 30 1  3.74s user 0.00s system 99% cpu 3.738 total
 ==> 2^30/3.74 == 287,096,744 per second

*/

/*
BENCHARGS=30 0
BENCHARGS=30 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

