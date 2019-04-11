
#include "comb/mixedradix-endo-gray.h"
#include "comb/endo-enup.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"

#include <cstdlib>  // strtoul()


//% Mixed radix counting: endo Gray sequence
//% (endo := "Even Numbers Down, Odd (numbers up)")

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

    mixedradix_endo_gray M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");
    cout << endl;

//    M.last();
    ulong ct = 0;
    do
    {
#ifndef TIMING
        cout << " " << setw(4) << ct << ":  ";
        M.print("    ", true );
        cout << setw(6) << M.to_num();
        cout << setw(6) << M.pos() << "  " << (M.dir()<0?'-':'+') << 1;
        cout << endl;
#endif  // TIMING
        ++ct;
    }
    while ( M.next() );
//    while ( M.prev() );

    cout << " # = " << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 30 2  ## binary is worst case
 # = 1073741824
./bin 30 2  16.06s user 0.09s system 99% cpu 16.172 total
 ==> 1073741824/16.06 == 66,858,145 per second

 time ./bin 16 4
 # = 4294967296
./bin 16 4  50.12s user 0.24s system 99% cpu 50.398 total
 ==> 4294967296/50.12 == 85,693,681 per second

 time ./bin 10 8
 # = 1073741824
./bin 10 8  11.45s user 0.06s system 99% cpu 11.516 total
 ==> 1073741824/11.45 == 93,776,578 per second

 time ./bin 8 16
 # = 4294967296
./bin 8 16  38.18s user 0.20s system 99% cpu 38.408 total
 ==> 4294967296/38.18 == 112,492,595 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-endo-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-endo-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

