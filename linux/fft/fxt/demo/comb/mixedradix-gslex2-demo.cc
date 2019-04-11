
#include "comb/mixedradix-gslex2.h"

#include "aux1/copy.h"  // fill()


#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix numbers in gslex (generalized subset lex) order.
//% Loopless algorithm.

// Cf. comb/mixedradix-gslex-demo.cc for another implementation

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

    mixedradix_gslex2 M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");
    cout << endl;

    ulong ct = 0;
    ulong j = ( n ? n-1 : 0 );
    do
    {
#ifndef TIMING
        cout << " " << setw(4) << ct << ":  ";
        M.print("    ", true );

//        cout << "  " << j;
//        cout << "  tr=" << M.tr_;

        // Print as multiset:
        print_multi_deltaset_as_set("    ", M.data(), n, 0 );

//        cout << setw(6) << M.to_num();

        cout << endl;
#endif  // TIMING
        ++ct;
    }
    while ( n != (j=M.next()) );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

time ./bin 30 2 ## binary is worst case
 ct=1073741824
./bin 30 2  3.04s user 0.00s system 99% cpu 3.037 total
 ==> 1073741824/3.04 == 353,204,547 per second

 time ./bin 16 4
 ct=4294967296
./bin 16 4  11.69s user 0.00s system 99% cpu 11.691 total
 ==> 4294967296/11.69 == 367,405,243 per second

 time ./bin 10 8
 ct=1073741824
./bin 10 8  2.28s user 0.00s system 99% cpu 2.278 total
 ==> 1073741824/2.28 == 470,939,396 per second

 time ./bin 8 16
 ct=4294967296
./bin 8 16  10.15s user 0.00s system 99% cpu 10.150 total
 ==> 4294967296/10.15 == 423,149,487 per second

 time ./bin 12 0
 ct=6227020800
./bin 12 0  15.41s user 0.00s system 99% cpu 15.415 total
 ==> 13!/15.41 == 404,089,604 per second

 time ./bin 12 1
 ct=6227020800
./bin 12 1  18.18s user 0.00s system 99% cpu 18.184 total
 ==> 13!/18.18 == 342,520,396 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-gslex2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-gslex2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

