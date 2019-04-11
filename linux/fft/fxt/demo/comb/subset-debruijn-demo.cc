
#include "comb/subset-debruijn.h"
#include "comb/debruijn.h"
#include "comb/necklace.h"

#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Generate all subsets in De Bruijn order.

//#define TIMING  // uncomment to disable printing

#define ZEBRA_HACK()  { for (ulong j=0; j<n; j+=2)  x[j]^=1UL; }

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Size of the set");
    bool zq = 0;
    NXARG(zq, "Option: alternative order");

    subset_debruijn S(n);

#ifdef TIMING
    ulong num;
    do { num=S.next(); } while ( num );

#else  // TIMING
    ulong *x = (ulong *)S.data();  // non-const to allow zebra hack
    ulong ct = 0;
    ulong num;
    do
    {
        if ( zq )  ZEBRA_HACK();
        cout << "    " << setw(2) << ct << ":";
        num = print_deltaset_as_set("    ", x, n, 1);

        cout << "   #=" << num;
        print_deltaset_as_set("    ", x, n);
        cout << endl;
        if ( zq )  ZEBRA_HACK();

        S.next();
        ++ct;
    }
    while ( ct < (1UL<<n) );  // needed for zebra hack
//    while ( num );
#endif  // TIMING

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 28
arg 1: 28 == n  [Size of the set]  default=5
arg 2: 0 == zq  [Option: alternative order]  default=0
./bin 28  13.08s user 0.03s system 99% cpu 13.122 total
 ==> 2^28/13.08 == 20,522,588 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/subset-debruijn-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/subset-debruijn-demo.cc DEMOFLAGS=-DTIMING"
/// End:

