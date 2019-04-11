
#include "comb/skew-binary.h"

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"

//% Skew binary numbers.
//% See http://en.wikipedia.org/wiki/Skew_binary_number_system
//% Cf. OEIS sequence A169683.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of digits");

    skew_binary B(n);

    ulong ct = 0;
#ifdef TIMING
    do  { ++ct; }  while ( B.next() );
#else

    ulong tr = 0;
    do
    {
        cout << setw(4) << ct << ":";
        B.print("  ", true );
        cout << "  " << n - tr; // A215020
        cout << endl;
        ++ct;
        jjassert( B.OK() );
    }
    while ( (tr=B.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)

GCC 4.9.2:

 time ./bin 30
arg 1: 30 == n  [Number of digits]  default=5
 ct=2147483647
./bin 30  3.03s user 0.00s system 99% cpu 3.037 total
 ==> 2147483647/3.03 == 708,740,477 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/skew-binary-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/skew-binary-demo.cc DEMOFLAGS=-DTIMING"
/// End:

