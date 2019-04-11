
#include "comb/mixedradix-lex.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix counting.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Number of digits");

    ulong rr = 4;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");
    ulong ct = 0;

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "Benchmark: whether to generate in backward order");
    mixedradix_lex M(n, rr);

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

    mixedradix_lex M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");  cout << endl;

    do
    {
#if 0
        // args: n n: A000248: forests with n nodes and height <= 1.
        // args: n 1: (rfact) A000000
        // args: n 2: A052548: 2-sided prudent polygons with area n
        // args: n 3: A000000
        const ulong *x = M.data();
        bool q = true;
        for (ulong j=0; j<n; ++j)
        {
            ulong dj = x[j];
            if ( dj == j )  continue;  // either a fixed point ...
            if ( dj >= n )  { q=false; break; }
            if ( x[dj] != dj )  { q=false; break; }  // ... or pointing to a fixed point
        }
        if ( !q )  continue;
#endif
        // radices 1 3 5 7 ...: A001147 (perfect matchings, fixed-point free involutions).
        cout << setw(6) << ct << ":";
        M.print("  ", true );
        cout << "  " << M.pos();
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
Timing:

 time ./bin 30 2  ## binary is worst case
 ct=1073741824
./bin 30 2  6.44s user 0.02s system 99% cpu 6.474 total
 ==> 1073741824/6.44 == 166,730,096 per second

 time ./bin 19 3
 ct=1162261467
./bin 19 3  4.52s user 0.02s system 99% cpu 4.545 total
 ==> 1162261467/4.52 == 257,137,492 per second

 time ./bin 16 4
 ct=4294967296
./bin 16 4  13.64s user 0.00s system 100% cpu 13.643 total
 ==> 4294967296/13.64 == 314,880,300 per second

 time ./bin 10 8
 ct=1073741824
./bin 10 8  2.90s user 0.01s system 99% cpu 2.908 total
 ==> 1073741824/2.90 == 370,255,801 per second

 time ./bin 8 16
 ct=4294967296
./bin 8 16  12.54s user 0.04s system 99% cpu 12.607 total
 ==> 4294967296/12.54 == 342,501,379 per second

 time ./bin 12 1  ## rising factorial
 ct=6227020800
./bin 12 1  20.03s user 0.02s system 100% cpu 20.049 total
 ==> 6227020800/20.03 == 310,884,712 per second

 time ./bin 12 0  ## falling factorial
 ct=6227020800
./bin 12 0  19.45s user 0.04s system 100% cpu 19.494 total
 ==> 6227020800/19.45 == 320,155,311 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 2  ## binary is worst case
 ct=1073741824
./bin 30 2  3.53s user 0.00s system 99% cpu 3.531 total
 ==> 1073741824/3.53 == 304,176,154 per second
./bin 30 2  3.18s user 0.00s system 99% cpu 3.189 total  // with array


  time ./bin 16 4
 ct=4294967296
./bin 16 4  11.07s user 0.00s system 99% cpu 11.073 total
 ==> 4294967296/11.07 == 387,982,592 per second
./bin 16 4  9.55s user 0.00s system 99% cpu 9.555 total  // with array


  time ./bin 12 0  ## falling factorial
 ct=6227020800
./bin 12 0  15.05s user 0.00s system 99% cpu 15.054 total
 ==> 6227020800/15.05 == 413,755,534 per second
./bin 12 0  14.68s user 0.00s system 99% cpu 14.689 total  // with array

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
/// make-target: "1demo DSRC=demo/comb/mixedradix-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

