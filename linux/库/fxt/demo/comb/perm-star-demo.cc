
#include "comb/perm-star.h"

//#include "perm/permq.h"
#include "comb/fact2perm.h"
//#include "comb/mixedradix.h"
//#include "comb/comb-print.h"

#include "comb/check-permgen.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"  // NXARG()
#include "fxtio.h"


//% Generate all permutations in star-transposition order.

//#define TIMING  // uncomment to disable printing

//#define VERBOSE  // define to print internal data and inversion table

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements to permute (n>=1)");
    jjassert( n>0 );

    perm_star P(n);

#ifdef TIMING

#ifdef PERM_STAR_FIXARRAYS
    cout << "PERM_STAR_FIXARRAYS is defined." << endl;
#endif
#ifdef PERM_STAR_WITH_INVERSE
    cout << "PERM_STAR_WITH_INVERSE is defined." << endl;
#endif
    while ( P.next() )  {;}

#else  // TIMING

    ulong *fc = new ulong[n-1];

    const bool dfz = true;  // whether to print dots for zeros

    check_permgen C(n);
    C.first( P.invdata() );  // inverse permutations(!)
    const ulong nfh = factorial(n)/2;
    ulong ct = 0;
    do
    {
        cout << setw(4) << ct << ":";
        ++ct;

        P.print("    ", dfz);
        cout << "    (" << 0 << ", " << P.get_swap() << ") ";
        P.print_inv("    ", dfz);

#ifdef VERBOSE
        print_vec("  b=", P.b_+1, n-1, true);
        print_vec("  c=", P.c_+1, n-1, true);
        perm2rfact(P.data(), n, fc);
//        perm2rfact(P.invdata(), n, fc);
        print_mixedradix("   fc=", fc, n-1, true);
#endif
        cout << endl;

        if ( ct<nfh )
        {
            jjassert( ! C.is_repeat() );
            jjassert( ! C.is_repeat_rev() );
        }
    }
    while ( P.next() );

    delete [] fc;

#endif  // TIMING


    return 0;
}
// -------------------------

/*
Timing:

% time ./bin 12
arg 1: 12 == n  [Number of elements to permute (n>=1)]  default=4
PERM_STAR_FIXARRAYS is defined.
PERM_STAR_WITH_INVERSE is defined.
./bin 12  2.53s user 0.00s system 99% cpu 2.534 total
 ==> 12!/2.53 == 189,328,695 per second

% time ./bin 12
arg 1: 12 == n  [Number of elements to permute (n>=1)]  default=4
PERM_STAR_FIXARRAYS is defined.
./bin 12  2.54s user 0.00s system 100% cpu 2.534 total
 ==> 12!/2.54 == 188,583,307 per second

% time ./bin 12
arg 1: 12 == n  [Number of elements to permute (n>=1)]  default=4
PERM_STAR_WITH_INVERSE is defined.
./bin 12  5.36s user 0.00s system 99% cpu 5.370 total
 ==> 12!/5.36 == 89,365,970 per second

% time ./bin 12
arg 1: 12 == n  [Number of elements to permute (n>=1)]  default=4
./bin 12  3.40s user 0.00s system 99% cpu 3.406 total
 ==> 12!/3.40 == 140,882,823 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-star-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-star-demo.cc DEMOFLAGS=-DTIMING"
/// End:

