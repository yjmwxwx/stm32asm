
#include "comb/perm-rev2.h"

#include "comb/comb-print.h"
#include "comb/mixedradix.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"
#include "jjassert.h"


//% Permutations by prefix reversals, CAT algorithm.

//#define TIMING  // uncomment to disable printing



int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements to permute n>0");
    jjassert( n>0 );

    perm_rev2 P(n);
    P.first();

    ulong ct = 0;

#ifdef TIMING
#ifdef PERM_REV2_FIXARRAYS
    cout << "PERM_REV2_FIXARRAYS is defined." << endl;
#endif
    ulong e;
    do  { ++ct;  e = P.next(); }  while ( e!=n );

#else

    bool dfz= true;  // whether to print dots for zeros
    ulong e;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
        P.print("    ", dfz);
//        print_mixedradix("    ", P.d_+2, n-3, dfz);
        cout << endl;
        e = P.next();
    }
    while ( e!=n );

#endif

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

% time ./bin 12
arg 1: 12 == n  [Number of elements to permute n>0]  default=4
./bin 12  1.74s user 0.00s system 100% cpu 1.742 total
 ==> 12!/1.74 == 275,288,275 per second

% time ./bin 12
arg 1: 12 == n  [Number of elements to permute n>0]  default=4
PERM_REV2_FIXARRAYS is defined.
./bin 12  2.37s user 0.00s system 99% cpu 2.377 total
 ==> 12!/2.37 == 202,110,379 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12
arg 1: 12 == n  [Number of elements to permute n>0]  default=4
./bin 12  1.55s user 0.00s system 99% cpu 1.555 total
 ==> 12!/1.55 == 309,033,290 per second

 time ./bin 12
arg 1: 12 == n  [Number of elements to permute n>0]  default=4
PERM_REV2_FIXARRAYS is defined.
./bin 12  1.38s user 0.00s system 99% cpu 1.381 total
 ==> 12!/1.38 == 347,102,608 per second

*/

/*
BENCHARGS=12
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-rev2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-rev2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

