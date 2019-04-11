
#include "comb/mixedradix-naf.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"

#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix non-adjacent forms (NAF).

// Cf. comb/mixedradix-naf-subset-lex-demo.cc for subset-lex order.
// Cf. comb/mixedradix-naf-gray-demo.cc for Gray code.
// Cf. bits/bitfibgray-demo.cc for binary Gray code in a binary word.
// Cf. bits/fibrep2-demo.cc for binary NAFs (Fibonacci words) in lexicographic order in a binary word.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of digits");

    ulong rr = 3;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "Benchmark: whether to generate in backward order");
    mixedradix_naf M(n, rr);

#else
    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply radix for all digits (rr ignored)");
    if ( argc>3 )  jjassert( argc == (int)n+3 );
    for (ulong k=3;  k<(ulong)argc; ++k)  r[k-3] = strtoul(argv[k], 0, 10);

    mixedradix_naf M(n, rr, (argc>3? r:0) );
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
    do
    {
        cout << setw(4) << ct << ":";
        M.print("    ", true );
        cout << "  " << M.pos();
        cout << endl;

        jjassert( M.OK() );

        ++ct;

//        for (ulong j=0; j<n; ++j)  ct += M.data()[j];  // A000000
    }
    while ( M.next() );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

----- args=42 2 0 ## binary is worst case (Fibonacci strings)
forward:
 ct=701408733
./bin 42 2 0  3.53s user 0.00s system 99% cpu 3.534 total
 ==> 701408733/3.53 == 198,699,357 per second

----- args=42 2 1
backward:
 ct=701408733
./bin 42 2 1  3.70s user 0.00s system 99% cpu 3.698 total
 ==> 701408733/3.70 == 189,569,927 per second


----- args=29 3 0
forward:
 ct=715827883
./bin 29 3 0  3.30s user 0.00s system 99% cpu 3.303 total
 ==> 715827883/3.30 == 216,917,540 per second

----- args=29 3 1
backward:
 ct=715827883
./bin 29 3 1  3.39s user 0.00s system 99% cpu 3.393 total
 ==> 715827883/3.39 == 211,158,667 per second


----- args=24 4 0
forward:
 ct=727060321
./bin 24 4 0  2.87s user 0.00s system 99% cpu 2.872 total
 ==> 727060321/2.87 == 253,331,122 per second

----- args=24 4 1
backward:
 ct=727060321
./bin 24 4 1  2.88s user 0.00s system 99% cpu 2.879 total
 ==> 727060321/2.88 == 252,451,500 per second


----- args=18 8 0
forward:
 ct=2245983825
./bin 18 8 0  7.84s user 0.00s system 99% cpu 7.846 total
 ==> 2245983825/7.84 == 286,477,528 per second

----- args=18 8 0
backward:
 ct=2245983825
./bin 18 8 1  7.85s user 0.00s system 99% cpu 7.856 total
 ==> 2245983825/7.85 == 286,112,589 per second


## factorial bases:
----- args=17 0 0
forward:
 ct=997313824
./bin 17 0 0  2.68s user 0.00s system 99% cpu 2.679 total
 ==> 997313824/2.68 == 372,132,023 per second

----- args=17 0 1
backward:
 ct=997313824
./bin 17 0 1  2.72s user 0.00s system 99% cpu 2.717 total
 ==> 997313824/2.72 == 366,659,494 per second


----- args=17 1 0
forward:
 ct=997313824
./bin 17 1 0  4.34s user 0.00s system 99% cpu 4.340 total
 ==> 997313824/4.34 == 229,795,811 per second

----- args=17 1 1
backward:
 ct=997313824
./bin 17 1 1  4.77s user 0.00s system 99% cpu 4.776 total
 ==> 997313824/4.77 == 209,080,466 per second

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

/*
OEIS sequences:

Falling factorial numbers: A000085 (self-inverse permutations, with offset 1)
%  for n in $(seq 1 11); do ./bin $n 0 | grep ct= ; done
(same for rising factorial numbers)

Radix 2: A000045 (Fibonacci numbers)
Radix 3: A028859
Radix 4: A125145
Radix 5: A086347

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-naf-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-naf-demo.cc DEMOFLAGS=-DTIMING"
/// End:

