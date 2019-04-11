
#include "comb/mixedradix-gray.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix Gray code, CAT algorithm.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Number of digits");

    ulong rr = 4;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");

    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply radix for all digits (rr ignored)");
    if ( argc>3)  jjassert( argc == (int)n+3 );
    for (ulong k=3;  k<(ulong)argc; ++k)  r[k-3] = strtoul(argv[k], 0, 10);

    mixedradix_gray M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");
    cout << endl;

//    for (ulong j=0; j<n; j+=2)  // complement selected tracks
//    {  M.a_[j] = M.m1_[j];  M.i_[j] = -1UL; }

//    M.last();
    ulong ct = 0;
    do
    {
#ifndef TIMING
        cout << " " << setw(4) << ct << ":  ";
        M.print("    ", true );
        cout << setw(6) << M.to_num();
        cout << setw(6) << M.pos() << "  " << (M.dir()<0?'-':'+') << 1;

//        cout << "    ";
//        for (ulong j=0; j<n; ++j)  cout << " " << ((long)(M.i_[j])<0?'-':'+');

        cout << endl;
#endif  // TIMING
        ++ct;
    }
    while ( M.next() );
//    while ( M.prev() );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 30 2  ## binary is worst case
 ct=1073741824
./bin 30 2  8.34s user 0.00s system 100% cpu 8.337 total
 ==> 1073741824/8.34 == 128,746,022 per second

 time ./bin 16 4
 ct=4294967296
./bin 16 4  18.33s user 0.03s system 100% cpu 18.354 total
 ==> 4294967296/18.33 == 234,313,545 per second

 time ./bin 10 8
 ct=1073741824
./bin 10 8  3.53s user 0.00s system 100% cpu 3.536 total
 ==> 1073741824/3.53 == 304,176,154 per second

 time ./bin 8 16
 ct=4294967296
./bin 8 16  15.00s user 0.04s system 100% cpu 15.029 total
 ==> 4294967296/15.00 == 286,331,153 per second

 time ./bin 12 1  ## rising factorial
 ct=6227020800
./bin 12 1  31.88s user 0.04s system 100% cpu 31.915 total
 ==> 6227020800/31.88 == 195,326,875 per second

 time ./bin 12 0  ## falling factorial
 ct=6227020800
./bin 12 0  23.03s user 0.03s system 99% cpu 23.075 total
 ==> 6227020800/23.03 == 270,387,355 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 2 ## binary is worst case
 ct=1073741824
./bin 30 2  4.79s user 0.00s system 99% cpu 4.790 total
 ==> 1073741824/4.79 == 224,163,220 per second

 time ./bin 19 3
 ct=1162261467
./bin 19 3  3.46s user 0.00s system 99% cpu 3.464 total
 ==> 1162261467/3.46 == 335,913,718 per second

 time ./bin 16 4
 ct=4294967296
./bin 16 4  12.83s user 0.00s system 99% cpu 12.831 total
 ==> 4294967296/12.83 == 334,759,726 per second

 time ./bin 10 8
 ct=1073741824
./bin 10 8  2.23s user 0.00s system 99% cpu 2.231 total
 ==> 1073741824/2.23 == 481,498,575 per second

 time ./bin 8 16
 ct=4294967296
./bin 8 16  9.58s user 0.00s system 99% cpu 9.581 total
 ==> 4294967296/9.58 == 448,326,440 per second


 time ./bin 12 1  ## rising factorial
 ct=6227020800
./bin 12 1  21.20s user 0.00s system 99% cpu 21.206 total
 ==> 6227020800/21.20 == 293,727,396 per second

 time ./bin 12 0  ## falling factorial
 ct=6227020800
./bin 12 0  14.54s user 0.00s system 99% cpu 14.540 total
 ==> 6227020800/14.54 == 428,268,280 per second

*/

/*
BENCHARGS=30 2
BENCHARGS=19 3
BENCHARGS=16 4
BENCHARGS=10 8
BENCHARGS=8 16
BENCHARGS=12 1
BENCHARGS=12 0

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

