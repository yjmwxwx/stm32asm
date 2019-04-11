
#include "comb/perm-lex-inv.h"


#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

#include "perm/permq.h"  // is_inverse()

#include "jjassert.h"

//% Generate all permutations in lexicographic order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements.");

    perm_lex_inv P(n);

#ifdef TIMING
#ifdef PERM_LEX_INV_FIXARRAYS
    cout << "PERM_LEX_INV_FIXARRAYS is defined." << endl;
#endif
#ifdef PERM_LEX_INV_OPT
    cout << "PERM_LEX_INV_OPT is defined." << endl;
#endif

    ulong ct = 0;
    do { ++ct; }  while ( P.next() );

    // make sure program updates inverse permutations:
//    jjassert( is_inverse(P.data(), P.invdata(), n) );

#else  // TIMING

    bool dfz= true;  // whether to print dots for zeros
    const ulong *x = P.data();
    const ulong *xi = P.invdata();

    cout << "         permutation         inv. perm.";
    cout << endl;

    ulong ct = 0;
    do
    {
#if 0
        if ( ! is_simple(x, n) )  continue;  // A111111
//        jjassert( is_simple(xi, n) );
#endif
#if 0  // fixed number of descents (Eulerian numbers, cf. A008292)
        ulong d=0;
        for (ulong i=1; i<n; ++i)  d += (x[i-1] > x[i]);
        if ( d != 1 )  continue; // A000295
//        if ( d != 2 )  continue; // A000460
//        if ( d != 3 )  continue; // A000498
//        if ( d != n/2 )  continue; // A006551, cf. A025585 and A180056
#endif

#if 1  // allow/suppress printing
        cout << setw(4) << ct << ":";
        P.print("    ", dfz);
        cout << setw(3) << P.pos();
        P.print_inv("    ", dfz);
//        print_vec("      ", P.d_, n, true);

        cout << endl;

        jjassert( is_inverse(x, xi, n) );
#endif
        ++ct;
    }
    while ( P.next() );

#endif // TIMING

    cout << "ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)


GCC 4.9.1:

 time ./bin 13
arg 1: 13 == n  [Permutations of n elements.]  default=4
PERM_LEX_INV_FIXARRAYS is defined.
PERM_LEX_INV_OPT is defined.
ct=6227020800
./bin 13  9.43s user 0.00s system 99% cpu 9.438 total
 ==> 6227020800/9.43 == 660,341,548 per second

 time ./bin 13
arg 1: 13 == n  [Permutations of n elements.]  default=4
PERM_LEX_INV_FIXARRAYS is defined.
ct=6227020800
./bin 13  13.09s user 0.00s system 99% cpu 13.098 total
 ==> 6227020800/13.09 == 475,708,235 per second

 time ./bin 13
 time ./bin 13
arg 1: 13 == n  [Permutations of n elements.]  default=4
ct=6227020800
./bin 13  47.61s user 0.00s system 99% cpu 47.627 total
 ==> 6227020800/47.61 == 130,792,287 per second

 time ./bin 13
arg 1: 13 == n  [Permutations of n elements.]  default=4
PERM_LEX_INV_OPT is defined.
ct=6227020800
./bin 13  43.29s user 0.00s system 99% cpu 43.307 total
 ==> 6227020800/43.29 == 143,844,324 per second

*/

/*
BENCHARGS=13
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-lex-inv-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-lex-inv-demo.cc DEMOFLAGS=-DTIMING"
/// End:

