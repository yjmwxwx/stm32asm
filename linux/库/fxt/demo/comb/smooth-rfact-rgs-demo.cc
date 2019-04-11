
#include "comb/smooth-rfact-rgs.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Restricted growth strings (RGS) [d(0), d(1), d(2), ..., d(n-1)] where
//%  0 <= d(k) <= k and abs(d(k)-d(k-1)) <= 1 (smooth factorial numbers).
//% Cf. OEIS sequence A005773.

//#define TIMING  // uncomment to disable printing

// Cf. comb/catalan-rgs-demo.cc for Catalan RGS
// Cf. comb/motzkin-rgs-lex-demo.cc for Motzkin RGS


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Length of strings");

    smooth_rfact_rgs S(n);

    ulong ct = 0;

#ifdef TIMING
    S.first();
    do  { ++ct; }  while ( S.next() );

#else  // TIMING

    ulong j = 0;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":  ";

        // print RGS:
        print_vec("  ", S.data(), n, true );

        cout << setw(4) << j;

        cout << endl;

        jjassert( S.OK() );
    }
    while ( (j=S.next()) );

#endif  // TIMING

    cout << " ct=" << ct;  // OEIS sequence A005773
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 22
arg 1: 22 == n  [Length of strings]  default=5
 ct=2173243128
./bin 22  9.25s user 0.00s system 99% cpu 9.257 total
 ==> 2173243128/9.25 == 234,945,203 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/smooth-rfact-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/smooth-rfact-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

