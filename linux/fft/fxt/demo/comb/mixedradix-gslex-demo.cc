
#include "comb/mixedradix-gslex.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix numbers in gslex (generalized subset lex) order.

// Cf. comb/mixedradix-gslex2-demo.cc for a loopless implementation

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

    mixedradix_gslex M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");
    cout << endl;

    ulong ct = 0;
    do
    {
#ifndef TIMING
        cout << " " << setw(4) << ct << ":  ";
        M.print("    ", true );
        // Print as multiset:
        print_multi_deltaset_as_set("    ", M.data(), n, 0 );
//        cout << setw(6) << M.to_num();

        cout << endl;
#endif  // TIMING
        ++ct;
    }
    while ( M.next() );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 30 2  ## binary is worst case
 ct = 1073741824
./bin 30 2  8.72s user 0.04s system 99% cpu 8.768 total
 ==> 1073741824/8.72 == 123,135,530 per second

 time ./bin 16 4
 ct = 4294967296
./bin 16 4  21.69s user 0.11s system 99% cpu 21.803 total
 ==> 4294967296/21.69 == 198,016,011 per second

 time ./bin 10 8
 ct = 1073741824
./bin 10 8  4.83s user 0.03s system 99% cpu 4.866 total
 ==> 1073741824/4.83 == 222,306,795 per second

 time ./bin 8 16
 ct = 4294967296
./bin 8 16  15.71s user 0.08s system 99% cpu 15.790 total
 ==> 4294967296/15.71 == 273,390,661 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 2 ## binary is worst case
 ct = 1073741824
./bin 30 2  4.72s user 0.00s system 99% cpu 4.726 total
 ==> 1073741824/4.72 == 227,487,674 per second

 time ./bin 16 4
 ct = 4294967296
./bin 16 4  13.26s user 0.00s system 99% cpu 13.264 total
 ==> 4294967296/13.26 == 323,904,019 per second

 time ./bin 10 8
 ct = 1073741824
./bin 10 8  2.45s user 0.00s system 99% cpu 2.450 total
 ==> 1073741824/2.45 == 438,261,968 per second

 time ./bin 8 16
 ct = 4294967296
./bin 8 16  10.56s user 0.00s system 99% cpu 10.565 total
 ==> 4294967296/10.56 == 406,720,387 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-gslex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-gslex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

