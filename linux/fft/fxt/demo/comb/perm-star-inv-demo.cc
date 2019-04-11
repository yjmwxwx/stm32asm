
#include "comb/perm-rev2.h"

#define PERM_STAR_WITH_INVERSE  // make sure inverse is computed
#include "comb/perm-star.h"

#include "comb/comb-print.h"

#include "comb/check-permgen.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"
#include "jjassert.h"


//% Inverse star transposition permutations via permutations by prefix reversals.

//#define TIMING  // uncomment to disable printing



int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements to permute n>0");
    jjassert( n>0 );

#ifndef TIMING
#ifndef PERM_STAR_WITH_INVERSE
#error "Need inverse star-permutations for testing."
#endif

    perm_star S(n);  S.first();
    const ulong *si = S.invdata();
    bool dfz= true;  // whether to print dots for zeros
    ulong ct = 0;
#endif

    perm_rev2 P(n);  P.first();
    ulong *x = new ulong[n];
    const ulong *r = P.data();
    for (ulong k=0; k<n; ++k)  x[k] = k;
    ulong i0 = 0;  // position of element zero
    do
    {
        ulong i1 = r[0];
        swap2(x[i0], x[i1]);

#ifndef TIMING
        ++ct;
        cout << setw(4) << ct << ":";
        print_perm("    ", x, n, dfz);
        cout << "    " << "(" << i0 << ", " << i1 << ")";
        P.print("    ", dfz);
        cout << endl;
        for (ulong j=0; j<n; ++j)  jjassert( si[j]==x[j] );
        S.next();
#endif

        i0 = i1;
    }
    while ( P.next()!=n );
#ifndef TIMING
    cout << " ct=" << ct << endl;
#endif

    delete [] x;

    return 0;
}
// -------------------------

/*
Timing:

% time ./bin 12
arg 1: 12 == n  [Number of elements to permute n>0]  default=4
./bin 12  3.10s user 0.00s system 99% cpu 3.113 total
 ==> 12!/3.10 == 154,516,645 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-star-inv-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-star-inv-demo.cc DEMOFLAGS=-DTIMING"
/// End:

