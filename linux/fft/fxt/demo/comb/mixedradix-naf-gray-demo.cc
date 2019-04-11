
#include "comb/mixedradix-naf-gray.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"

#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Gray code for mixed radix non-adjacent forms (NAF).

// Cf. comb/ntnz-gray-demo.cc for an recursive version with fixed base.
// Cf. comb/mixedradix-naf-subset-lex-demo.cc for subset-lex order.
// Cf. comb/mixedradix-naf-demo.cc for counting order.
// Cf. comb/perm-involution-naf-demo.cc for involutions via falling factorial NAFs


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of digits (n>=1)");
    jjassert( n>=1 );

    ulong rr = 3;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "Benchmark: whether to generate in backward order");
    mixedradix_naf_gray M(n, rr);

#else
    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply radix for all digits (rr ignored)");
    if ( argc>3 )  jjassert( argc == (int)n+3 );
    for (ulong k=3;  k<(ulong)argc; ++k)  r[k-3] = strtoul(argv[k], 0, 10);

    mixedradix_naf_gray M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");
    cout << endl;
#endif

    ulong ct = 0;
#ifdef TIMING
#ifdef MIXEDRADIX_NAF_MAX_ARRAY_LEN
    cout << "MIXEDRADIX_NAF_MAX_ARRAY_LEN is defined." << endl;
#endif
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
        cout << " " << setw(4) << ct << ":  ";
        M.print("    ", true );
        cout << "  " << M.pos();
        cout << "  " << (M.dir()==+1 ? '+' : '-' );
        print_sign_vec("    ", M.d_, n);
        cout << endl;

        jjassert( M.OK() );
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

----- args=42 2 0 ## binary is worst case (Fibonacci Gray code)
forward:
 ct=701408733
./bin 42 2 0  5.83s user 0.00s system 99% cpu 5.827 total
 ==> 701408733/5.83 == 120,310,245 per second

----- args=42 2 1
backward:
 ct=701408733
./bin 42 2 1  6.22s user 0.00s system 99% cpu 6.227 total


----- args=29 3 0
forward:
 ct=715827883
./bin 29 3 0  5.11s user 0.00s system 99% cpu 5.113 total
 ==> 715827883/5.11 == 140,083,734 per second

----- args=29 3 1
backward:
 ct=715827883
./bin 29 3 1  5.26s user 0.00s system 99% cpu 5.257 total


----- args=24 4 0
forward:
 ct=727060321
./bin 24 4 0  4.72s user 0.00s system 99% cpu 4.721 total
 ==> 727060321/4.72 == 154,038,203 per second

----- args=24 4 1
backward:
 ct=727060321
./bin 24 4 1  5.08s user 0.00s system 99% cpu 5.078 total


----- args=18 8 0
forward:
 ct=2245983825
./bin 18 8 0  11.28s user 0.00s system 99% cpu 11.282 total
 ==> 2245983825/11.28 == 199,112,041 per second

----- args=18 8 1
backward:
 ct=2245983825
./bin 18 8 1  11.57s user 0.00s system 99% cpu 11.575 total


## factorial bases:
----- args=17 0 0
forward:
 ct=997313824
./bin 17 0 0  4.10s user 0.00s system 99% cpu 4.100 total
 ==> 997313824/4.10 == 243,247,274 per second

----- args=17 0 1
backward:
 ct=997313824
./bin 17 0 1  3.92s user 0.00s system 99% cpu 3.924 total

----- args=17 1 0
forward:
 ct=997313824
./bin 17 1 0  6.66s user 0.00s system 99% cpu 6.658 total
 ==> 997313824/6.66 == 149,746,820  per second

----- args=17 1 1
backward:
 ct=997313824
./bin 17 1 1  7.62s user 0.00s system 99% cpu 7.627 total

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
/// make-target: "1demo DSRC=demo/comb/mixedradix-naf-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-naf-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

