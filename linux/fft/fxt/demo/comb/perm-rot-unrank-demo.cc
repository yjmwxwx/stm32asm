

#include "comb/mixedradix-lex.h"
#include "perm/rotate.h"
#include "perm/perminvert.h"
// demo-include "perm/perminvert.cc"

#include "perm/reverse.h"
#include "perm/permcomplement.h"

//#include "comb/mixedradix-gray.h"

#include "perm/permq.h"

#include "comb/comb-print.h"

#include "aux1/copy.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"

#include "nextarg.h"  // NXARG()



//% Unranking for permutations by rotations (cyclic shifts).

//#define TIMING  // uncomment to disable printing

void
ffact2perm_rot(const ulong *fc, ulong n, ulong *x)
// Convert falling factorial number fc[0, ..., n-2] into
// permutation of x[0, ...,n-1].
{
    for (ulong k=0; k<n; ++k)  x[k] = k;
    for (ulong k=n-1, j=2;  k!=0;  --k, ++j)  rotate_right(x+k-1, j, fc[k-1]);

//    for (ulong k=n-1, j=2;  k!=0;  --k, ++j)  rotate_left(x+k-1, j, fc[k-1]);
//    reverse(x, n);
//    make_complement(x, x, n);
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements");

    mixedradix_lex M(n-1, 0);  // falling factorial
//    mixedradix_gray M(n-1, 0);  // falling factorial
    const ulong *m = M.data();
    ulong *x = new ulong[n];   // permutation
    ulong ct = 0;

#ifdef TIMING
    do
    {
        ffact2perm_rot(m, n, x);
        ++ct;
    }
    while ( M.next() );

#else  // TIMING

    ulong *xi = new ulong[n];  // inverse permutation
    ulong *t = new ulong[n];   // aux
    ulong ndt = 0;  // number of transitions that are no derangements
    const bool dfz= true;  // whether to print dots for zeros

    do
    {
        ffact2perm_rot(m, n, x);

        cout << setw(4) << ct << ":";
        print_mixedradix("  ", m, n-1, dfz);

        print_perm("    ", x, n, dfz);

        make_inverse(x, xi, n);
        print_perm("    ", xi, n, dfz);

        if ( ct>0 )
        {
            if ( !is_derangement(x, t, n) )
            {
                cout << " N";
                ++ndt;
            }
        }
        for (ulong j=0; j<n; ++j)  t[j] = x[j];

        cout << endl;
        ++ct;
    }
    while ( M.next() );
    cout << " # non-derangement transitions = " << ndt << endl;

    delete [] xi;
    delete [] t;

#endif  // TIMING

    cout << " ct=" << ct << endl;

    delete [] x;

    return 0;
}
// -------------------------

/*
Timing:

  time ./bin 11
arg 1: 11 == n  [Number of elements]  default=4
 # non-derangement transitions = 0
 ct=39916800
./bin 11  8.75s user 0.05s system 99% cpu 8.824 total
 ==> 39916800/8.75 == 4,561,920 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-rot-unrank-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-rot-unrank-demo.cc DEMOFLAGS=-DTIMING"
/// End:

