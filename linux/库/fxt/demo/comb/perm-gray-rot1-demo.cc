
#include "comb/perm-gray-rot1.h"
// demo-include "comb/mixedradix-gray.h"

#include "comb/comb-print.h"
#include "comb/mixedradix.h"

//#include "comb/fact2perm.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

#include "jjassert.h"

//% Generate all permutations in minimal-change order such that
//% in the last permutations the first e elements are cyclically
//% rotated by one where e is the greatest even number <=n.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Permutations of n elements.");

    perm_gray_rot1 P(n);

#ifdef TIMING
    while ( P.next() ) {;}

#else

    const bool dfz = true;  // whether to print dots for zeros

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
    }
    while ( P.next() );
#endif  // TIMING

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements.]  default=4
./bin 12  13.36s user 0.07s system 99% cpu 13.437 total
 ==> 12!/13.36 == 35,853,413  per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-gray-rot1-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-gray-rot1-demo.cc DEMOFLAGS=-DTIMING"
/// End:

