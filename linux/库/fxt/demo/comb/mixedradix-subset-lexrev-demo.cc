
#include "comb/mixedradix-subset-lexrev.h"

#include "comb/comb-print.h"

#include "aux1/copy.h"  // fill()

//#include "comb/is-partition-asc.h"
//#include "comb/is-partition-desc.h"
//#include "comb/is-composition-nz.h"
//#include "comb/is-schroeder-rgs.h"
//#include "comb/is-young-tab-rgs.h"
//#include "comb/is-dyck-rgs.h"

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix numbers in subset-lexrev order.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Number of digits");

    ulong rr = 4;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "Benchmark: whether to generate in backward order");
    mixedradix_subset_lexrev M(n, rr);

#else
    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply radix for all digits (rr ignored)");
    if ( argc>3 )  jjassert( argc == (int)n+3 );

    for (ulong i=3;  i<(ulong)argc; ++i)  r[i-3] = strtoul(argv[i], 0, 10);

    mixedradix_subset_lexrev M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");
    cout << endl;
#endif


    ulong ct = 0;
#ifdef TIMING
#ifdef MIXEDRADIX_SUBSET_LEXREV_FIXARRAYS
    cout << "MIXEDRADIX_SUBSET_LEXREV_FIXARRAYS is defined." << endl;
#endif
    if ( ! bq )
    {
        cout << "forward:" << endl;
        M.first();
        do  { ++ct; }  while ( M.next() );
    }
    else
    {
        cout << "backward:" << endl;
        M.last();
        do  { ++ct; }  while ( M.prev() );
    }

#else

//    M.last();
    const ulong *x = M.data();
    do
    {
//        if ( ! is_schroeder_rgs(x, n, 0) )  continue;
//        if ( ! is_schroeder_rgs(x, n, 1) )  continue;
//        ulong Z[64];  if ( ! is_young_tab_rgs(x, n, Z, 0) )  continue;  // strange order
//        if ( ! is_dyck_rgs(x, n) )  continue;  // strange order

#if 0
        ulong m = 0;  for (ulong j=0; j<n; ++j)  if ( x[j] )  m = j+1;
//        if ( ! is_composition_nz(x, m, n) )  continue;  // maj by num parts, minor rev colex
//        if ( ! is_partition_asc(x, m, n) )  continue;  // maj by num parts, minor lex
        if ( ! is_partition_desc(x, m, n) )  continue;  // maj by num parts, minor reversed colex
#endif
#if 0  // weak compositions: reversed colex ordering
        ulong s = 0;
        for (ulong j=0; j<n; ++j)
            s += x[j];
        if ( s != n )  continue;
#endif


        cout << setw(4) << ct << ":";
        M.print("  ", true );

        print_multi_deltaset_as_set("    ", x, n, false);

        cout << endl;
        ++ct;
    }
    while ( M.next() );
//    while ( M.prev() );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)


 time ./bin 30 2 0 ## binary is worst case
forward:
 ct=1073741824
./bin 30 2 0  3.12s user 0.00s system 99% cpu 3.116 total
 ==> 1073741824/3.12 == 344,148,020 per second

 time ./bin 30 2 1 ## binary is worst case
backward:
 ct=1073741824
./bin 30 2 1  2.73s user 0.00s system 99% cpu 2.733 total
 ==> 1073741824/2.73 == 393,312,023 per second


 time ./bin 19 3 0
forward:
 ct=1162261467
./bin 19 3 0  2.09s user 0.00s system 99% cpu 2.090 total
 ==> 1162261467/2.09 == 556,105,965 per second

 time ./bin 19 3 1
backward:
 ct=1162261467
./bin 19 3 1  1.79s user 0.00s system 99% cpu 1.792 total
 ==> 1162261467/1.79 == 649,308,082 per second


 time ./bin 16 4 0
forward:
 ct=4294967296
./bin 16 4 0  7.39s user 0.00s system 99% cpu 7.396 total
 ==> 4294967296/7.39 == 581,186,372 per second

 time ./bin 16 4 1
backward:
 ct=4294967296
./bin 16 4 1  5.65s user 0.00s system 99% cpu 5.651 total
 ==> 4294967296/5.65 == 760,171,202 per second


 time ./bin 10 8 0
forward:
 ct=1073741824
./bin 10 8 0  1.49s user 0.00s system 99% cpu 1.491 total
 ==> 1073741824/1.49 == 720,632,096 per second

 time ./bin 10 8 1
backward:
 ct=1073741824
./bin 10 8 1  1.11s user 0.00s system 99% cpu 1.112 total
 ==> 1073741824/1.11 == 967,334,976 per second


 time ./bin 8 16 0
forward:
 ct=4294967296
./bin 8 16 0  7.38s user 0.00s system 99% cpu 7.385 total
 ==> 4294967296/7.38 == 581,973,888 per second

 time ./bin 8 16 1
backward:
 ct=4294967296
./bin 8 16 1  4.84s user 0.00s system 99% cpu 4.841 total
 ==> 4294967296/4.84 == 887,389,937  per second



 time ./bin 12 0 0
forward:
 ct=6227020800
./bin 12 0 0  8.37s user 0.00s system 99% cpu 8.372 total
 ==> 13!/8.37 == 743,969,032 per second

 time ./bin 12 0 1
backward:
 ct=6227020800
./bin 12 0 1  5.42s user 0.00s system 99% cpu 5.424 total
 ==> 13!/5.42 == 1,148,896,826 per second


 time ./bin 12 1 0
forward:
 ct=6227020800
./bin 12 1 0  13.87s user 0.00s system 99% cpu 13.869 total
 ==> 13!/13.87 == 448,956,077 per second

 time ./bin 12 1 1
backward:
 ct=6227020800
./bin 12 1 1  12.74s user 0.00s system 99% cpu 12.746 total
 ==> 13!/12.74 == 488,777,142 per second

*/


/*

BENCHARGS=30 2 0
BENCHARGS=30 2 1
BENCHARGS=19 3 0
BENCHARGS=19 3 1
BENCHARGS=16 4 0
BENCHARGS=16 4 1
BENCHARGS=10 8 0
BENCHARGS=10 8 1
BENCHARGS=8 16 0
BENCHARGS=8 16 1

BENCHARGS=12 0 0
BENCHARGS=12 0 1
BENCHARGS=12 1 0
BENCHARGS=12 1 1

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-subset-lexrev-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-subset-lexrev-demo.cc DEMOFLAGS=-DTIMING"
/// End:

