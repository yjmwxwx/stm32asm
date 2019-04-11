
#include "comb/perm-pref.h"

#include "comb/fact2perm.h"
#include "perm/rotate.h"

#include "comb/comb-print.h"
#include "fxtio.h"
//#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% All permutations via prefix shifts ("cool-lex" order)

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements.");

    perm_pref P(n);

    ulong *p = new ulong[n];  // permutation starting with identity
    for (ulong j=0; j<n; ++j)  p[j] = j;


    ulong ct = 0;

#ifdef TIMING

    ulong i = P.n_;
    do
    {
        ++ct;
        i = P.next();
        rotate_right1(p, i);
    }
    while ( i );

#else  // TIMING

    const bool dfz = true;  // whether to print dots for zeros

    const ulong *x = P.data();
    // inversion table:
    ulong *it = new ulong[n-1];

    ulong i = P.n_;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
        print_perm("  ", x, n, dfz);
        cout << "  " << i;  // OEIS seq. A191246 (except first term)

        print_perm("  ", p, n, dfz);  // first element: A191246

#if 0  // whether to show inversion tables
        const ulong *y = p;  // choose x or p
        perm2ffact(y, n, it);
        print_perm("    ", it, n-1, dfz);

        perm2rfact(y, n, it);
        print_perm("    ", it, n-1, dfz);
#endif

        cout << endl;
//        break;
        i = P.next();
        rotate_right1(p, i);
    }
    while ( i );

    delete [] it;
    delete [] p;

#endif  // TIMING

    cout << "ct=" << ct << endl;


    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements.]  default=4
ct=479001600
./bin 12  4.78s user 0.00s system 99% cpu 4.781 total
 ==> 12!/4.78 == 100,209,539 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-pref-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-pref-demo.cc DEMOFLAGS=-DTIMING"
/// End:
