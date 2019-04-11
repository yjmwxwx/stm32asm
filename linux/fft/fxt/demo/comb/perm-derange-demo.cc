
#include "comb/perm-derange.h"
#include "comb/perm-trotter.h"

#include "perm/perminvert.h"
// demo-include "perm/perminvert.cc"

#include "comb/comb-print.h"


#include "fxttypes.h"
#include "fxtio.h"

#include "nextarg.h"  // NXARG()

//% Generate all permutations in derangement order.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements (no derangement order for n=3)");

    perm_derange P(n);

#ifdef TIMING

    while ( P.next() )  {;}

#else  // TIMING

    bool dfz= true;  // whether to print dots for zeros

    const ulong *x = P.data();
    ulong *xi = new ulong[n];  // inverse permutation
    ulong ct = 0;
    do
    {
        cout << setw(4) << ct << ":";
        ++ct;

        P.print("    ", dfz);
        make_inverse(x, xi, n);
        print_perm("    ", xi, n, dfz);

        cout << endl;
    }
    while ( P.next() );

    delete [] xi;

#endif  // TIMING

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 12
./bin 12  13.74s user 0.07s system 99% cpu 13.828 total
 ==> 12!/13.74 == 34,861,834 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-derange-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-derange-demo.cc DEMOFLAGS=-DTIMING"
/// End:

