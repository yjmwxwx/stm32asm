
#include "comb/mixedradix-modular-gray2.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Modular mixed radix Gray code, CAT algorithm.

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

    mixedradix_modular_gray2 M(n, rr, (argc>3? r:0) );
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
        cout << setw(6) << M.pos();
//        print_vec("  ", M.x_, n);
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
./bin 30 2  7.07s user 0.03s system 100% cpu 7.104 total
 ==> 1073741824/7.07 == 151,872,959 per second

 time ./bin 16 4
 ct=4294967296
./bin 16 4  17.53s user 0.05s system 100% cpu 17.576 total
 ==> 4294967296/17.53 == 245,006,691 per second

 time ./bin 10 8
 ct=1073741824
./bin 10 8  4.06s user 0.01s system 99% cpu 4.069 total
 ==> 1073741824/4.01 == 267,766,040 per second

 time ./bin 8 16
 ct=4294967296
./bin 8 16  14.47s user 0.04s system 99% cpu 14.519 total
 ==> 4294967296/14.47 == 296,818,748 per second

 time ./bin 12 1  ## rising factorial
 ct=6227020800
./bin 12 1  27.63s user 0.06s system 100% cpu 27.693 total
 ==> 6227020800/27.63 == 225,371,726 per second

 time ./bin 12 0  ## falling factorial
 ct=6227020800
./bin 12 0  22.02s user 0.03s system 100% cpu 22.052 total
 ==> 6227020800/22.01 == 282,917,800 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-modular-gray2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-modular-gray2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

