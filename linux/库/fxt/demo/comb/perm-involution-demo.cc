
#include "comb/perm-involution.h"

#include "perm/permq.h"
#include "comb/comb-print.h"
#include "perm/printcycles.h"

#include "comb/fact2perm.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Involutions (self-inverse permutations).
//% Cf. OEIS sequence A000085.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Self-inverse permutations of n elements.");

    perm_involution P(n);
    ulong ct = 0;

#ifdef TIMING
#ifdef PERM_INVOLUTION_FIXARRAYS
    cout << "PERM_INVOLUTION_FIXARRAYS defined." << endl;
#endif
    do  { ++ct; }  while ( P.next() );

#else

    const bool dfz= true;  // whether to print dots for zeros

    const ulong *x = P.data();
//    ulong it[64];  // inversion table
    do
    {
#if 0
        if ( ! is_simple(P.data(), n) )  continue;  // A244522
#endif
#if 0  // no adjacent transpositions: A170941
        { const ulong *x = P.data();
            bool q = true;
            for (ulong k=0; k<n; ++k)
                if ( x[k] == k+1 )  { q=0;  break; }
            if ( !q )  continue;
        }
#endif

        ++ct;
#if 1
        cout << setw(4) << ct << ":";

        P.print("  ", dfz);

//        perm2rfact(x, n, it);
//        print_vec("  ", it, n-1, dfz);

        print_cycles("    ", x, n);

        cout << endl;

        jjassert( is_involution(x, n) );
#endif
    }
    while ( P.next() );

#endif
    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

  time ./bin 17
arg 1: 17 == n  [Self-inverse permutations of n elements.]  default=5
 ct=211799312
./bin 17  3.96s user 0.00s system 99% cpu 3.971 total
 ==> 211799312/3.96 == 53,484,674 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 17 1
arg 1: 17 == n  [Self-inverse permutations of n elements.]  default=5
 ct=211799312
./bin 17 1  2.91s user 0.00s system 99% cpu 2.915 total
 ==> 211799312/2.91 == 72,783,268 per second


GCC 4.8.0:

 time ./bin 17
arg 1: 17 == n  [Self-inverse permutations of n elements (n>=1).]  default=5
 ct=211799312
./bin 17  3.18s user 0.00s system 99% cpu 3.180 total
 ==> 211799312/3.18 == 66,603,557 per second

 time ./bin 17
arg 1: 17 == n  [Self-inverse permutations of n elements (n>=1).]  default=5
PERM_INVOLUTION_FIXARRAYS defined.
 ct=211799312
./bin 17  3.34s user 0.00s system 99% cpu 3.344 total
 ==> 211799312/3.34 == 63,412,967 per second

*/

/*
BENCHARGS=17
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-involution-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-involution-demo.cc DEMOFLAGS=-DTIMING"
/// End:

