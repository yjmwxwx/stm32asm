
#include "comb/mixedradix-gslex-alt2.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix numbers in alternative gslex (generalized subset lex) order.

// Cf. comb/mixedradix-gslex-demo.cc for a similar ordering.
// Cf. comb/mixedradix-lex-demo.cc for lexicographic ordering (wrt. delta sets).
// Cf. comb/mixedradix-subset-lex-demo.cc for subset-lex ordering.
// Cf. comb/mixedradix-gslex-alt-demo.cc (less optimized version).

//#define TIMING  // uncomment to disable printing



int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Number of digits");

    ulong rr = 4;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "Benchmark: whether to generate in backward order");
    mixedradix_gslex_alt2 M(n, rr);

#else
    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply radix for all digits (rr ignored)");
    if ( argc>3)  jjassert( argc == (int)n+3 );
    for (ulong k=3;  k<(ulong)argc; ++k)  r[k-3] = strtoul(argv[k], 0, 10);

    mixedradix_gslex_alt2 M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");
    cout << endl;
#endif


    ulong ct = 0;
#ifdef TIMING
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

//    M.last();
    do
    {
        cout << setw(4) << ct << ":";
        M.print("    ", true );


        // Print as multiset:
        print_multi_deltaset_as_set("    ", M.data(), n, 0 );

        cout << endl;
        ++ct;
    }
    while ( M.next() );
//    while ( M.prev() );

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 2 0 ## binary is worst case
forward:
 ct=1073741824
./bin 30 2 0  3.65s user 0.00s system 99% cpu 3.656 total
 ==> 1073741824/3.65 == 294,175,842 per second

 time ./bin 30 2 1
backward:
 ct=1073741824
./bin 30 2 1  2.78s user 0.00s system 99% cpu 2.780 total
 ==> 1073741824/2.78 == 386,238,066 per second


 time ./bin 19 3 0
forward:
 ct=1162261467
./bin 19 3 0  3.27s user 0.00s system 99% cpu 3.273 total
 ==> 1162261467/3.27 == 355,431,641 per second

 time ./bin 19 3 1
backward:
 ct=1162261467
./bin 19 3 1  3.22s user 0.00s system 99% cpu 3.220 total
 ==> 1162261467/3.22 == 360,950,766 per second


 time ./bin 16 4 0
forward:
 ct=4294967296
./bin 16 4 0  10.88s user 0.00s system 99% cpu 10.887 total
 ==> 4294967296/10.88 == 394,758,023 per second

 time ./bin 16 4 1
backward:
 ct=4294967296
./bin 16 4 1  11.94s user 0.00s system 99% cpu 11.942 total
 ==> 4294967296/11.94 == 359,712,503 per second


 time ./bin 10 8 0
forward:
 ct=1073741824
./bin 10 8 0  2.77s user 0.00s system 99% cpu 2.770 total
 ==> 1073741824/2.77 == 387,632,427 per second

 time ./bin 10 8 1
backward:
 ct=1073741824
./bin 10 8 1  2.54s user 0.00s system 99% cpu 2.540 total
 ==> 1073741824/2.54 == 422,733,001 per second


 time ./bin 8 16 0
forward:
 ct=4294967296
./bin 8 16 0  9.31s user 0.00s system 99% cpu 9.312 total
 ==> 4294967296/9.31 == 461,328,388 per second

 time ./bin 8 16 1
backward:
 ct=4294967296
./bin 8 16 1  11.46s user 0.00s system 99% cpu 11.466 total
 ==> 4294967296/11.46 == 374,778,996 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-gslex-alt2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-gslex-alt2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

