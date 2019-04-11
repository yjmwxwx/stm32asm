
#include "comb/mixedradix-gray2.h"

#include "comb/comb-print.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix Gray code, loopless algorithm.
//% Implementation following Knuth.

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

    mixedradix_gray2 M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");
    cout << endl;

//    M.last();
    ulong ct = 0;
    do
    {
#ifndef TIMING
        cout << " " << setw(4) << ct << ":  ";
        M.print("    ", true );

//        ulong sd = 0;  // sum of digits
//        for (ulong j=0; j<n; ++j)  sd += M.data()[j];
//        cout << setw(3) << sd;

        cout << setw(6) << M.to_num();
        cout << setw(6) << M.pos() << "  " << (M.dir()<0?'-':'+') << 1;
        print_vec("    f=", M.f_, n+1);  // focus pointer incl. sentinel
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
./bin 30 2  8.94s user 0.01s system 100% cpu 8.951 total
 ==> 1073741824/8.94 == 120,105,349 per second

 time ./bin 16 4
 ct=4294967296
./bin 16 4  22.05s user 0.03s system 100% cpu 22.080 total
 ==> 4294967296/22.05 == 194,783,097 per second

 time ./bin 10 8
 ct=1073741824
./bin 10 8  4.06s user 0.02s system 100% cpu 4.078 total
 ==> 1073741824/4.06 == 264,468,429 per second

 time ./bin 8 16
 ct=4294967296
./bin 8 16  15.66s user 0.04s system 100% cpu 15.703 total
 ==> 4294967296/15.66 == 274,263,556 per second

 time ./bin 12 1  ## rising factorial
 ct=6227020800
./bin 12 1  42.56s user 0.06s system 99% cpu 42.642 total
 ==> 6227020800/42.56 == 146,311,578 per second

 time ./bin 12 0  ## falling factorial
 ct=6227020800
./bin 12 0  24.21s user 0.05s system 100% cpu 24.257 total
 ==> 6227020800/24.21 == 257,208,624 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 2 ## binary is worst case
 ct=1073741824
./bin 30 2  5.00s user 0.00s system 99% cpu 4.998 total
 ==> 1073741824/5.00 == 214,748,364 per second

 time ./bin 16 4
 ct=4294967296
./bin 16 4  16.79s user 0.00s system 99% cpu 16.790 total
 ==> 4294967296/16.79 == 255,805,080 per second

 time ./bin 10 8
 ct=1073741824
./bin 10 8  3.64s user 0.00s system 99% cpu 3.643 total
 ==> 1073741824/3.64 == 294,984,017 per second

 time ./bin 8 16
 ct=4294967296
./bin 8 16  15.19s user 0.00s system 99% cpu 15.195 total
 ==> 4294967296/15.19 == 282,749,657 per second

 time ./bin 12 1  ## rising factorial
 ct=6227020800
./bin 12 1  27.93s user 0.00s system 99% cpu 27.938 total
 ==> 6227020800/27.93 == 222,950,977 per second

 time ./bin 12 0  ## falling factorial
 ct=6227020800
./bin 12 0  20.30s user 0.00s system 99% cpu 20.306 total
 ==> 6227020800/20.30 == 306,749,793 per second

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
/// make-target: "1demo DSRC=demo/comb/mixedradix-gray2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-gray2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

