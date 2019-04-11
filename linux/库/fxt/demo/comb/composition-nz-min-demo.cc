
#include "comb/composition-nz-min.h"
#include "comb/composition-nz-rank.h"

#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts >= mi.
//% Lexicographic order.

// Cf. comb/composition-nz-max-demo.cc for compositions into parts <= mx
// Cf. comb/composition-nz-demo.cc for all compositions
// Cf. comb/composition-nz-left-smooth-demo.cc for left-smooth compositions
// Cf. comb/composition-nz-smooth-demo.cc for smooth compositions
// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 11;
    NXARG(n, "compositions of n into parts >= mi");
    ulong mi = 2;
    NXARG(mi, "parts >= mi");
    // mi==2:  ==> A000045, a(n)=a(n-1)+a(n-2) (Fibonacci numbers)
    // mi==3:  ==> A078012, a(n)=a(n-1)+a(n-3), cf. A000930
    // mi==4:  ==> A017898, a(n)=a(n-1)+a(n-4), cf. A003269
    // mi==5:  ==> A017899, a(n)=a(n-1)+a(n-5), cf. A003520
    // mi==6:  ==> A017900, a(n)=a(n-1)+a(n-6), cf. A005708

    composition_nz_min P(n, mi);

    ulong ct = 0;

#ifdef TIMING
#ifdef COMPOSITION_NZ_MIN_FIXARRAYS
    cout << "COMPOSITION_NZ_MIN_FIXARRAYS is defined." << endl;
#endif
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
    while ( m )
    {
        ++ct;

        cout << setw(4) << ct << ":";
        cout << "  [" << setw(2) << m << "]";  // for mi=2: A143299 (backward order)
//        cout << "  [" << n-m << "]";

//        ulong r = composition_nz_rank( P.data(), m);
////        ulong r = composition_nz_rl_rank( P.data(), m);
//        print_bin("  ", r, n);

        P.print("  ");

        cout << endl;

        jjassert( P.OK() );

        m = P.next();
    }
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

// with second easy case enabled:

 time ./bin 47 2
arg 1: 47 == n  [compositions of n into parts >= mi]  default=9
arg 2: 2 == mi  [parts >= mi]  default=2
 ct=1836311903
./bin 47 2  6.81s user 0.00s system 99% cpu 6.810 total
 ==> 1836311903/6.81 == 269,649,324 per second

 time ./bin 47 2
arg 1: 47 == n  [compositions of n into parts >= mi]  default=9
arg 2: 2 == mi  [parts >= mi]  default=2
COMPOSITION_NZ_MIN_FIXARRAYS is defined.
 ct=1836311903
./bin 47 2  5.24s user 0.00s system 99% cpu 5.243 total
 ==> 1836311903/5.24 == 350,441,202 per second


// with second easy case disabled:

 time ./bin 47 2
arg 1: 47 == n  [compositions of n into parts >= mi]  default=9
arg 2: 2 == mi  [parts >= mi]  default=2
 ct=1836311903
./bin 47 2  6.80s user 0.00s system 99% cpu 6.804 total
 ==> 1836311903/6.80 == 270,045,868 per second

 time ./bin 47 2
arg 1: 47 == n  [compositions of n into parts >= mi]  default=9
arg 2: 2 == mi  [parts >= mi]  default=2
COMPOSITION_NZ_MIN_FIXARRAYS is defined.
 ct=1836311903
./bin 47 2  5.50s user 0.00s system 99% cpu 5.504 total
 ==> 1836311903/5.50 == 333,874,891 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-min-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-min-demo.cc DEMOFLAGS=-DTIMING"
/// End:

