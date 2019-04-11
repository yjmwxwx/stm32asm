
#include "comb/ksubset-lex.h"

#include "comb/comb-print.h"

//#include "bits/print-bin.h"
//#include "comb/composition-nz-rank.h"

#include "fxttypes.h"

#include "fxtio.h"
#include "nextarg.h"
#include "jjassert.h"


//% Nonempty subsets of the set {0,1,2,...,n-1} with at most k elements.
//% Representation as list of parts.
//% Subset-lex order.
//% Loopless generation.
//% See OEIS sequence A117670.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Size of the set (n>=1)");
    jjassert( n>=1 );

    ulong k = 3;
    NXARG(k, "Max size of subsets (1<=k<=n)");
    jjassert( k>=1 );

    ksubset_lex S(n, k);

    ulong ct = 0;

#ifdef TIMING
#ifdef KSUBSET_LEX_MAX_ARRAY_LEN
    cout << "KSUBSET_LEX_MAX_ARRAY_LEN is defined." << endl;
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
//        if ( S.num_parts() < 3 )  continue;

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
//        cout << "  m = " << num;
        cout << endl;

        jjassert( S.OK() );
    }
    while ( (num = S.next()) );
//    while ( (num = S.prev()) );

#endif  // TIMING

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.0:

 time ./bin 30 30 0
arg 1: 30 == n  [Size of the set (n>=1)]  default=8
arg 2: 30 == k  [Max size of subsets (1<=k<=n)]  default=4
arg 3: 0 == dir  [Benchmark: whether to go backwards]  default=0
forward:
ct=1073741823
./bin 30 30 0  2.71s user 0.00s system 99% cpu 2.716 total
 ==> 1073741823/2.71 == 396,214,694 per second


 time ./bin 30 30 1
arg 1: 30 == n  [Size of the set (n>=1)]  default=8
arg 2: 30 == k  [Max size of subsets (1<=k<=n)]  default=4
arg 3: 1 == dir  [Benchmark: whether to go backwards]  default=0
backward:
ct=1073741823
./bin 30 30 1  2.90s user 0.00s system 99% cpu 2.902 total
 ==> 1073741823/2.90 == 370,255,801 per second


 time ./bin 40 10 0
arg 1: 40 == n  [Size of the set (n>=1)]  default=6
arg 2: 10 == k  [Max size of subsets (1<=k<=n)]  default=3
arg 3: 0 == dir  [Benchmark: whether to go backwards]  default=0
forward:
ct=1221246131
./bin 40 10 0  3.82s user 0.00s system 99% cpu 3.826 total
 ==> 1221246131/3.82 == 319,697,940 per second

 time ./bin 40 10 1
arg 1: 40 == n  [Size of the set (n>=1)]  default=6
arg 2: 10 == k  [Max size of subsets (1<=k<=n)]  default=3
arg 3: 1 == dir  [Benchmark: whether to go backwards]  default=0
backward:
ct=1221246131
./bin 40 10 1  3.53s user 0.00s system 99% cpu 3.531 total
 ==> 1221246131/3.53 == 345,962,076 per second

*/

/*
BENCHARGS=30 30 0
BENCHARGS=30 30 1

BENCHARGS=40 10 0
BENCHARGS=40 10 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ksubset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ksubset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

