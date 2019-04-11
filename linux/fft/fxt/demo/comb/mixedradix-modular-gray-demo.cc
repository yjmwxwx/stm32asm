
#include "comb/mixedradix-modular-gray.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

//% Modular mixed radix Gray code.
//% Implementation following Knuth (loopless algorithm).

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

    mixedradix_modular_gray M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");
    cout << endl;

//    M.last();
    ulong ct = 0;
    do
    {
#ifndef TIMING
        cout << " " << setw(4) << ct << ":  ";
        M.print("    ", true );
//        cout << setw(6) << M.to_num();

//        ulong sd = 0;  // sum of digits
//        for (ulong j=0; j<n; ++j)  sd += M.data()[j];
//        cout << setw(3) << sd;

        cout << setw(6) << M.pos();
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
./bin 30 2  6.35s user 0.00s system 99% cpu 6.351 total
 ==> 1073741824/6.35 == 169,093,200 per second

 time ./bin 16 4
 ct=4294967296
./bin 16 4  21.73s user 0.04s system 99% cpu 21.780 total
 ==> 4294967296/21.73 == 197,651,509 per second

 time ./bin 10 8
 ct=1073741824
./bin 10 8  4.19s user 0.02s system 99% cpu 4.210 total
 ==> 1073741824/4.19 == 256,262,965 per second

 time ./bin 8 16
 ct=4294967296
./bin 8 16  17.26s user 0.04s system 100% cpu 17.298 total
 ==> 4294967296/17.26 == 248,839,356 per second

 time ./bin 12 1  ## rising factorial
 ct=6227020800
./bin 12 1  37.24s user 0.05s system 100% cpu 37.289 total
 ==> 6227020800/37.24 == 167,213,233 per second

 time ./bin 12 0  ## falling factorial
 ct=6227020800
./bin 12 0  26.45s user 0.04s system 100% cpu 26.488 total
 ==> 6227020800/26.45 == 235,426,117 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-modular-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-modular-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

