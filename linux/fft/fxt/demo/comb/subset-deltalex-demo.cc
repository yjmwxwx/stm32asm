
#include "comb/subset-deltalex.h"
#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

//% All subsets in lexicographic order with respect to delta sets.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Subsets of the n-element set {0,1,...,n-1}.");
    bool dfz = true;  // whether to print dots for zeros
    char c01[] = "01";
    if ( dfz )  c01[0] = '.';

    subset_deltalex S(n);
    S.first();

#ifdef TIMING
#ifdef SUBSET_DELTALEX_MAX_ARRAY_LEN
    cout << "SUBSET_DELTALEX_MAX_ARRAY_LEN is defined." << endl;
#endif
    do  {;}  while ( S.next() );
#else

    const ulong *x = S.data();
    ulong ct = 0;
    do
    {
        cout << setw(4) << ct << ":";
        cout << "    ";
        for (ulong j=0; j<n; ++j)  cout << c01[x[j]];
        print_deltaset_as_set( "    ", S.data(), n);

        cout << endl;
        ++ct;
    }
    while ( S.next() );
#endif


    return 0;
}
// -------------------------

/*
Timing:

  time ./bin 30
arg 1: 30 == n  [Subsets of the n-element set {0,1,...,n-1}.]  default=5
./bin 30  6.09s user 0.00s system 99% cpu 6.104 total
 ==> 2^30/6.09 == 176,312,286 per second

  time ./bin 30
arg 1: 30 == n  [Subsets of the n-element set {0,1,...,n-1}.]  default=5
SUBSET_DELTALEX_MAX_ARRAY_LEN is defined.
./bin 30  5.57s user 0.00s system 100% cpu 5.566 total
 ==> 2^30/5.57 == 192,772,320 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

arg 1: 30 == n  [Subsets of the n-element set {0,1,...,n-1}.]  default=5
SUBSET_DELTALEX_MAX_ARRAY_LEN is defined.
./bin 30  3.08s user 0.00s system 99% cpu 3.085 total
 ==> 2^30/3.08 == 348,617,475 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/subset-deltalex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/subset-deltalex-demo.cc DEMOFLAGS=-DTIMING"
/// End:
