
#include "comb/rgs-kincr.h"


#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"

//% All Restricted growth strings (RGS) s[0,...,n-1] so that s[k] <= s[k-1] + k
//% Lexicographic order.
//% Cf. OEIS sequence A107877.

// 1, 2, 7, 37, 268, 2496, 28612, 391189, 6230646, ...

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Length of restricted growth strings (n>=1)");
    jjassert( n>=1 );

    rgs_kincr R(n);

    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(4) << ct << ":";
        R.print("    ", true);
        cout << endl;
#endif  // TIMING
    }
    while ( R.next() );

    cout << " ct= " << ct << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 11
arg 1: 11 == n  [Length of restricted growth strings]  default=4
 ct = 2332049710
./bin 11  5.67s user 0.00s system 99% cpu 5.668 total
 ==> 2332049710/5.67 == 411,296,245 per second
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/rgs-kincr-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/rgs-kincr-demo.cc DEMOFLAGS=-DTIMING"
/// End:

