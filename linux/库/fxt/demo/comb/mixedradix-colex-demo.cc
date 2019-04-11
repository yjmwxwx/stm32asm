
#include "comb/mixedradix-colex.h"

#include "comb/comb-print.h"

#include "aux1/copy.h"  // fill()

//#include "comb/arith-3-progression.h"


#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix counting, most significant digit changes most often.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Number of digits");

    ulong rr = 1;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");

    ulong ct = 0;

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "Benchmark: whether to generate in backward order");
    mixedradix_colex M(n, rr);

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

#else  // TIMING

    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply radix for all digits (rr ignored)");
    if ( argc>3 )  jjassert( argc == (int)n+3 );
    for (ulong k=3;  k<(ulong)argc; ++k)  r[k-3] = strtoul(argv[k], 0, 10);

    mixedradix_colex M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");  cout << endl;

    do
    {
#if 0  // Avoiding 3-term arithmetic progressions: (all for rising factorial base)
        if ( 0 != test_arith_3_progression(M.data(), n) )  continue;  // A000000
        // 1, 2, 6, 20, 67, 226, 699, 1970, 4673, 10879, 25690
//        if ( 0 != test_arith_3_progression_eqd(M.data(), n) )  continue;  // A000000
        // 1, 2, 6, 20, 88, 424, 2444, 15046, 107744, 815280, 7029140
//        if ( 0 != test_arith_3_progression_consec(M.data(), n) )  continue;  // A000000
        // 1, 2, 6, 20, 88, 476, 3060, 22792, 192410, 1819514, 19024342, 218083350
#endif

        cout << " " << setw(4) << ct << ":";
        M.print("  ", true );
//        cout << "  " << M.pos();
//        print_multi_deltaset_as_set("    ", M.data(), n, 1 );
        cout << endl;

        ++ct;
    }
    while ( M.next() );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 2  ## binary is worst case
 ct=1073741824
./bin 30 2  3.71s user 0.00s system 99% cpu 3.709 total
 ==> 1073741824/3.71 ==289,418,281  per second

 time ./bin 19 3
 ct=1162261467
./bin 19 3  2.93s user 0.00s system 99% cpu 2.934 total
 ==> 1162261467/2.93 == 396,676,268 per second

 time ./bin 16 4
 ct=4294967296
./bin 16 4  11.84s user 0.00s system 99% cpu 11.846 total
 ==> 4294967296/11.84 == 362,750,616 per second

 time ./bin 10 8
 ct=1073741824
./bin 10 8  2.43s user 0.00s system 99% cpu 2.431 total
 ==> 1073741824/2.43 == 441,869,063 per second

 time ./bin 8 16
 ct=4294967296
./bin 8 16  11.22s user 0.00s system 99% cpu 11.223 total
 ==> 4294967296/11.22 == 382,795,659 per second

 time ./bin 12 1  ## rising factorial
 ct=6227020800
./bin 12 1  14.85s user 0.00s system 99% cpu 14.853 total
 ==> 6227020800/14.85 == 419,328,000 per second

 time ./bin 12 0  ## falling factorial
 ct=6227020800
./bin 12 0  15.28s user 0.00s system 99% cpu 15.280 total
 ==> 6227020800/15.28 == 407,527,539 per second
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
/// make-target: "1demo DSRC=demo/comb/mixedradix-colex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-colex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

