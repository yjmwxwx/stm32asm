
#include "comb/mixedradix-sod-lex.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix numbers with fixed sum of digits.
//% Also: k-subsets (combinations) of a multiset.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of digits");

    ulong s = 4;
    NXARG(s, "Sum of digits");

    ulong rr = 0;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");

    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply radix for all digits (rr ignored)");
    if ( argc>4 )  jjassert( argc == (int)n+4 );
    for (ulong i=4;  i<(ulong)argc; ++i)  r[i-4] = strtoul(argv[i], 0, 10);

    mixedradix_sod_lex M(n, rr, (argc>4? r:0) );
    jjassert( M.first(s) );
    M.print_nines("Nines: ");
    cout << endl;
    cout << endl;

    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(4) << ct << ":";
        M.print("  ", true );
//        print_mixedradix("    ", M.data(), n+2,  1);

//        cout << setw(6) << M.to_num();  // == ct
        cout << setw(4) << M.pos();  // == rightmost position of change

//        if ( ct>0 )  // print lowest nonzero digit
//        {
//            ulong j=0;  while ( 0==M.data()[j] )  ++j;
//            cout << " @ " << M.data()[j];
//        }

        cout << endl;
        jjassert( M.OK() );
#endif  // TIMING
    }
    while ( M.next() );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 22 12 8
 ct=354539020
./bin 22 12 8  4.92s user 0.00s system 99% cpu 4.918 total
 ==> 354539020/4.92 == 72,060,776 per second

 time ./bin 22 12 4
 ct=263310740
./bin 22 12 4  3.54s user 0.00s system 99% cpu 3.545 total
 ==> 263310740/3.54 == 74,381,564 per second

 time ./bin 32 20 2
 ct=225792840
./bin 32 20 2  4.87s user 0.01s system 99% cpu 4.879 total
 ==> 225792840/4.87 == 46,364,032 per second

 time ./bin 32 12 2
 ct=225792840
./bin 32 12 2  3.84s user 0.00s system 99% cpu 3.852 total
 ==> 225792840/3.84 == 58,800,218 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

  time ./bin 22 12 8
 ct=354539020
./bin 22 12 8  2.56s user 0.00s system 99% cpu 2.560 total
 ==> 354539020/2.56 == 138,491,804 per second

  time ./bin 22 12 4
 ct=263310740
./bin 22 12 4  1.78s user 0.00s system 99% cpu 1.787 total
 ==> 263310740/1.78 == 147,927,382 per second

  time ./bin 32 20 2
 ct=225792840
./bin 32 20 2  2.26s user 0.00s system 99% cpu 2.266 total
 ==> 225792840/2.26 == 99,908,336 per second

  time ./bin 32 12 2
 ct=225792840
./bin 32 12 2  2.03s user 0.00s system 99% cpu 2.037 total
 ==> 225792840/2.03 == 111,228,000 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-sod-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-sod-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

