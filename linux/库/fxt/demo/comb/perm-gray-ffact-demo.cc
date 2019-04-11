
#include "comb/perm-gray-ffact.h"

#include "comb/comb-print.h"
#include "comb/mixedradix.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Generate all permutations in minimal-change order
//% via Gray code for falling factorial numbers, CAT algorithm.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements.");

    perm_gray_ffact P(n);

#ifdef TIMING
    while ( P.next() ) {;}
#else

    bool dfz = true;  // whether to print dots for zeros
    const ulong *x = P.data();
    const ulong *ix = P.invdata();
    const ulong *a = P.d_;

    ulong ct = 0;
    ulong sw1, sw2;
    do
    {
        cout << setw(4) << ct << ":";
        ++ct;

        print_perm("    ", x, n, dfz);

        P.get_swap(sw1, sw2);
        cout << "  (" << sw1 << ", " << sw2 << ")";

        print_mixedradix("    ", a, n-1, dfz);

        print_perm("    ", ix, n, dfz);

        cout << endl;
    }
    while ( P.next() );
#endif  // TIMING

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 12
./bin 12  3.05s user 0.01s system 100% cpu 3.055 total
 ==> 12!/3.05 == 157,049,704 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-gray-ffact-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-gray-ffact-demo.cc DEMOFLAGS=-DTIMING"
/// End:

