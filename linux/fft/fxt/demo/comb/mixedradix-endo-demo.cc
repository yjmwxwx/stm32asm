
#include "comb/mixedradix-endo.h"
#include "comb/endo-enup.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"

#include <cstdlib>  // strtoul()

//% Mixed radix counting: endo sequence
//% (endo := "Even Numbers DOwn, odd (numbers up)")

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

    mixedradix_endo M(n, rr, (argc>3? r:0) );
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
% time ./bin 30 2  ## binary is worst case
 # = 1073741824
./bin 30 2  9.39s user 0.05s system 99% cpu 9.448 total
 ==> 1073741824/9.39 == 114,349,502 per second

% time ./bin 16 4
 # = 4294967296
./bin 16 4  29.77s user 0.15s system 99% cpu 29.927 total
 ==> 4294967296/29.77 == 144,271,659 per second

% time ./bin 10 8
 # = 1073741824
./bin 10 8  6.64s user 0.04s system 99% cpu 6.691 total
 ==> 1073741824/6.64 == 161,708,106 per second

% time ./bin 8 16
 # = 4294967296
./bin 8 16  23.55s user 0.12s system 99% cpu 23.675 total
 ==> 4294967296/23.55 == 182,376,530 per second
*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-endo-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-endo-demo.cc DEMOFLAGS=-DTIMING"
/// End:

