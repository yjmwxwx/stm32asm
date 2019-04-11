
#include "comb/perm-star-swaps.h"

#include "perm/permq.h"
#include "comb/comb-print.h"

#include "fxttypes.h"
#include "nextarg.h"  // NXARG()
#include "fxtio.h"

//% Generate swaps for permutations in star-transpostion order.
//% Cf. OEIS sequences A123400 and A159880.

//#define TIMING  // uncomment to disable printing



int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements to permute");
//    jjassert( n>0 );

    perm_star_swaps P(n);
    P.first();

#ifdef TIMING
#ifdef PERM_STAR_SWAPS_FIXARRAYS
    cout << "PERM_STAR_SWAPS_FIXARRAYS is defined." << endl;
#endif
    while ( P.next() ) {;}

#else

    bool dfz= true;  // whether to print dots for zeros
    ulong *x = new ulong[n];  // permutations
    ulong *xi = new ulong[n];  // inverse permutations
    for (ulong k=0; k<n; ++k)  x[k] = xi[k] = k;

    ulong ct = 0;
    do
    {
        cout << setw(4) << ct << ":";
        ulong sw1, sw2;
        P.get_swap(sw1, sw2);
        swap2( x[sw1], x[sw2]);  // update permutation
        print_perm("    ", x, n, dfz);

        cout << "     (" << sw1 << ", " << sw2 << ") ";

        swap2( xi[x[sw1]], xi[x[sw2]]);  // update inverse permutation
        print_perm("    ", xi, n, dfz);

        cout << endl;
        ++ct;
    }
    while ( P.next() );

    cout << " ct=" << ct << endl;

    delete [] x;
    delete [] xi;
#endif

    return 0;
}
// -------------------------

/*
A123400:
echo $(./bin 5 | g -F \) | cut -d, -f2 | cut -d\) -f1 ) | tr ' ' ','

A159880:
./bin 5 | g -F \) | cut -d] -f1 | cut -d[ -f2 | cut -d' ' -f2 | tr . 0
*/

/*
Timing:

% time ./bin 12
arg 1: 12 == n  [Number of elements to permute]  default=4
PERM_STAR_SWAPS_FIXARRAYS is defined.
./bin 12  2.52s user 0.00s system 99% cpu 2.533 total
 ==> 12!/2.52 == 190,080,000 per second

% time ./bin 12
arg 1: 12 == n  [Number of elements to permute]  default=4
./bin 12  3.18s user 0.00s system 99% cpu 3.188 total
 ==> 12!/3.18 == 150,629,433 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-star-swaps-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-star-swaps-demo.cc DEMOFLAGS=-DTIMING"
/// End:

