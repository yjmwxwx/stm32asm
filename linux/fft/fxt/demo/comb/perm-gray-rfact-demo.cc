
#include "comb/perm-gray-rfact.h"
// demo-include "comb/mixedradix-gray.h"

#include "comb/comb-print.h"
#include "comb/mixedradix.h"

#include "comb/fact2perm.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

#include "jjassert.h"

//% Generate all permutations in minimal-change order
//% via Gray code for rising factorial numbers, CAT algorithm.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements.");

    perm_gray_rfact P(n);

#ifdef TIMING

#ifdef PGRF_SUCC_BY_INV
    cout << "PGRF_SUCC_BY_INV is defined." << endl;
#endif

    while ( P.next() ) {;}

#else  // TIMING

    const bool dfz = true;  // whether to print dots for zeros

    ulong *tt = new ulong[n-1];  // aux
    const ulong *x = P.data();
    const ulong *ix = P.invdata();
    const ulong *a = P.M_->data();  // factorial number
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

        cout << "   " << P.M_->pos();
        cout << "   " << (P.M_->dir()>0?'+':'-') << 1;

        print_perm("    ", ix, n, dfz);

        cout << endl;

        perm2rfact(x, n, tt);
        for (ulong k=0; k<n-1; ++k)  jjassert( a[k]==tt[k] );
    }
    while ( P.next() );

    delete [] tt;

#endif  // TIMING

    return 0;
}
// -------------------------

/*
Timing:

%  time ./bin 12
arg 1: 12 == n  [Permutations of n elements.]  default=4
PGRF_SUCC_BY_INV is defined.
./bin 12  5.96s user 0.00s system 99% cpu 5.965 total
 ==> 12!/5.96 == 80,369,395  per second

%  time ./bin 12
arg 1: 12 == n  [Permutations of n elements.]  default=4
./bin 12  6.72s user 0.00s system 100% cpu 6.728 total
 ==> 12!/6.72 == 71,280,000 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-gray-rfact-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-gray-rfact-demo.cc DEMOFLAGS=-DTIMING"
/// End:

