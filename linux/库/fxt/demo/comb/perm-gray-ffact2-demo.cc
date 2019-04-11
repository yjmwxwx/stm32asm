
#include "comb/perm-gray-ffact2.h"
// demo-include "comb/mixedradix-gray2.h"

#include "comb/comb-print.h"
#include "comb/mixedradix.h"

#include "aux0/factorial.h"  // for timing

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Generate all permutations in minimal-change order
//% via Gray code for falling factorial numbers, loopless algorithm.

//#define TIMING  // uncomment to disable printing



int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements.");

    perm_gray_ffact2 P(n);

#ifdef TIMING

    while ( P.next() ) {;}
    cout << " ct=" << factorial(n) << endl;

#else

    bool dfz = true;  // whether to print dots for zeros
    const ulong *x = P.data();
    const ulong *ix = P.invdata();
    const ulong *a = P.mrg_->data();
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

        cout << "   " << P.mrg_->pos();
        cout << "   " << (P.mrg_->dir()>0?'+':'-') << 1;

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
./bin 12  6.05s user 0.04s system 99% cpu 6.093 total
 ==> 12!/6.05 == 79,173,818 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements.]  default=4
./bin 12  3.15s user 0.00s system 99% cpu 3.155 total
 ==> 12!/3.15 == 152,064,000 per second
*/

/*
BENCHARGS=12
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-gray-ffact2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-gray-ffact2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

