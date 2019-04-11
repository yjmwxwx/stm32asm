
#include "comb/perm-colex.h"

#include "comb/comb-print.h"

#include "perm/perminvert.h"
//#include "comb/fact2perm.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Generate all permutations in co-lexicographic (colex) order


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements (n>=2).");
    jjassert( n>=2 );

    perm_colex P(n);

    ulong ct = 0;
#ifdef TIMING
#ifdef PERM_COLEX_FIXARRAYS
    cout << "PERM_COLEX_FIXARRAYS is defined." << endl;
#endif
    do { ++ct; }  while ( P.next() );
#else

    bool dfz = true;  // whether to print dots for zeros
    const ulong *x = P.data();
    const ulong *d = P.d_;
    ulong *t = new ulong[n];  // inverse permutations
    do
    {
        cout << setw(4) << ct << ":";
        print_perm("    ", x, n, dfz);
        print_mixedradix("    ", d, n-1, dfz);

        make_inverse(x, t, n);
        print_perm("        ", t, n, dfz);

        cout << endl;
        ++ct;
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

%  time ./bin 12
arg 1: 12 == n  [Permutations of n elements (n>=2).]  default=4
  ct=479001600
./bin 12  2.15s user 0.00s system 99% cpu 2.153 total
 ==> 12!/2.15 == 222,791,441  per second

with PERM_COLEX_FIXARRAYS:
%  time ./bin 12
arg 1: 12 == n  [Permutations of n elements (n>=2).]  default=4
PERM_COLEX_FIXARRAYS is defined.
  ct=479001600
./bin 12  1.44s user 0.00s system 99% cpu 1.450 total
 ==> 12!/1.44 == 332,640,000  per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

  time ./bin 12
arg 1: 12 == n  [Permutations of n elements (n>=2).]  default=4
PERM_COLEX_FIXARRAYS is defined.
  ct=479001600
./bin 12  0.91s user 0.00s system 99% cpu 0.913 total
 ==> 12!/0.91 == 526,375,384 per second

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements (n>=2).]  default=4
  ct=479001600
./bin 12  1.41s user 0.00s system 99% cpu 1.414 total
 ==> 12!/1.41 == 339,717,446 per second

*/

/*
BENCHARGS=13
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-colex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-colex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

