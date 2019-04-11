
#include "comb/perm-mv0.h"

#include "comb/comb-print.h"

#include "comb/fact2perm.h"
#include "perm/perminvert.h"
#include "comb/mixedradix-lex.h"


#include "jjassert.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Generate all inverse permutations with falling factorial numbers, CAT algorithm.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements (n>=2).");
    jjassert( n>=2 );

    perm_mv0 P(n);

    mixedradix_lex M(n-1, 0);  // falling factorial basis
    M.first();

    ulong ct = 0;
#ifdef TIMING
#ifdef PERM_MV0_FIXARRAYS
    cout << "PERM_MV0_FIXARRAYS is defined." << endl;
#endif
#ifdef PERM_MV0_UPDATE_D0
    cout << "PERM_MV0_UPDATE_D0 is defined." << endl;
#endif
    do { ++ct; }  while ( P.next() );
    ulong s = 0;
    for (ulong j=0; j<n; ++j)  s ^= P.data()[j];
    for (ulong j=0; j<n; ++j)  s ^= P.d_[j];
    if ( s==239 )  return 1;  // dummy

#else  // TIMING

    bool dfz = true;  // whether to print dots for zeros
    ulong *t = new ulong[n];  // permutations for checking
    const ulong *x = P.data();
    const ulong *d = P.d_;
    do
    {
        cout << setw(4) << ct << ":";
        ++ct;
        print_perm("    ", x, n, dfz);
        print_mixedradix("    ", d, n-1, dfz);

        make_inverse(x, t, n);
        print_perm("    ", t, n, dfz);

        cout << endl;

#ifdef PERM_MV0_UPDATE_D0
        ffact2invperm(d, n, t);
        for (ulong k=0; k<n; ++k)  jjassert( t[k]==x[k] );
#endif
        M.next();
    }
    while ( P.next() );

    delete [] t;
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements (n>=2).]  default=4
  ct=479001600
./bin 12  2.28s user 0.00s system 99% cpu 2.290 total
 ==> 12!/2.28 == 210,088,421 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements (n>=2).]  default=4
 ct=479001600
./bin 12  1.25s user 0.00s system 99% cpu 1.254 total
 ==> 12!/1.25 == 383,201,280 per second

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements (n>=2).]  default=4
PERM_MV0_UPDATE_D0 is defined.
 ct=479001600
./bin 12  1.20s user 0.00s system 99% cpu 1.208 total
 ==> 12!/1.20 == 399,168,000 per second


 time ./bin 12
arg 1: 12 == n  [Permutations of n elements (n>=2).]  default=4
PERM_MV0_FIXARRAYS is defined.
 ct=479001600
./bin 12  1.13s user 0.00s system 99% cpu 1.135 total
 ==> 12!/1.13 == 423,895,221 per second

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements (n>=2).]  default=4
PERM_MV0_FIXARRAYS is defined.
PERM_MV0_UPDATE_D0 is defined.
 ct=479001600
./bin 12  1.28s user 0.00s system 99% cpu 1.280 total
 ==> 12!/1.28 == 374,220,000 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-mv0-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-mv0-demo.cc DEMOFLAGS=-DTIMING"
/// End:

