
#include "comb/mixedradix-naf-subset-lex.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"

#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix non-adjacent forms (NAF) in subset-lex order.
//% Loopless generation.

// Cf. comb/mixedradix-naf-demo.cc for counting order.
// Cf. comb/mixedradix-naf-gray-demo.cc for Gray code.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of digits");

    ulong rr = 3;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");

#ifdef TIMING
#ifdef MIXEDRADIX_NAF_SUBSET_LEX_FIXARRAYS
    cout << "MIXEDRADIX_NAF_SUBSET_LEX_FIXARRAYS is defined" << endl;
#endif
    bool bq = 0;
    NXARG(bq, "With benchmark: whether to generate in backward order");
    mixedradix_naf_subset_lex M(n, rr);

#else
    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply radix for all digits (rr ignored)");
    if ( argc>3 )  jjassert( argc == (int)n+3 );
    for (ulong k=3;  k<(ulong)argc; ++k)  r[k-3] = strtoul(argv[k], 0, 10);

    mixedradix_naf_subset_lex M(n, rr, (argc>3? r:0) );
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

#else

//    M.last();
    do
    {
        cout << setw(4) << ct << ":";
        M.print("    ", true );
//        cout << "  " << M.pos();

        cout << "    ";
        ulong ns = M.iset_size();
        const ulong *iset = M.iset();
        cout << "{ ";
        for (ulong j=0; j<ns; ++j)
        {
//            cout << M.data()[iset[j]] << "* ";
            cout << iset[j];
            if ( j < ns-1 )  cout << ", ";
        }
        cout << " }";

        cout << endl;

        ++ct;

        jjassert( M.OK() );
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

 time ./bin 42 2 0 ## binary is worst case (Fibonacci strings)
 ct=701408733
./bin 42 2 0  3.52s user 0.00s system 99% cpu 3.518 total
 ==> 701408733/3.52 == 199,263,844 per second

./bin 42 2 1  3.07s user 0.00s system 99% cpu 3.075 total # backward
 ==> 701408733/3.07 == 228,471,900 per second


 time ./bin 29 3 0
 ct=715827883
./bin 29 3 0  2.78s user 0.00s system 99% cpu 2.777 total
 ==> 715827883/2.78 == 257,492,044 per second

./bin 29 3 1  2.79s user 0.00s system 99% cpu 2.787 total # backward
 ==> 715827883/2.79 == 256,569,133 per second


 time ./bin 24 4 0
 ct=727060321
./bin 24 4 0  2.49s user 0.00s system 99% cpu 2.487 total
 ==> 727060321/2.49 == 291,992,096 per second

./bin 24 4 1  2.38s user 0.00s system 99% cpu 2.386 total # backward
 ==> 727060321/2.38 == 305,487,529 per second


 time ./bin 18 8 0
 ct=2245983825
./bin 18 8 0  5.67s user 0.00s system 99% cpu 5.675 total
 ==> 2245983825/5.67 == 396,117,076 per second

./bin 18 8 1  5.56s user 0.00s system 99% cpu 5.565 total # backward
 ==> 2245983825/5.56 == 403,953,925 per second


## factorial bases:
 time ./bin 17 0 0
 ct=997313824
./bin 17 0 0  3.43s user 0.00s system 99% cpu 3.430 total
 ==> 997313824/3.43 == 290,762,047 per second

./bin 17 0 1  3.48s user 0.00s system 99% cpu 3.485 total # backward
 ==> 997313824/3.48 == 286,584,432 per second


 time ./bin 17 1 0
 ct=997313824
./bin 17 1 0  2.65s user 0.00s system 99% cpu 2.648 total
 ==> 997313824/2.65 == 376,344,839 per second

./bin 17 1 1  2.58s user 0.00s system 99% cpu 2.578 total # backward
 ==> 997313824/2.58 == 386,555,745 per second

*/

/*

BENCHARGS=42 2 0
BENCHARGS=42 2 1
BENCHARGS=29 3 0
BENCHARGS=29 3 1
BENCHARGS=24 4 0
BENCHARGS=24 4 1
BENCHARGS=18 8 0
BENCHARGS=18 8 1

BENCHARGS=17 0 0
BENCHARGS=17 0 1
BENCHARGS=17 1 0
BENCHARGS=17 1 1

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-naf-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-naf-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

