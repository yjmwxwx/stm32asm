
#include "comb/ruler-func1.h"
#include "comb/composition-nz.h"

#include "comb/comb-print.h"

//#include "jjassert.h"

#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"


//% Ruler function (one-based), 2-valuations of 2*n:
//%   1 2 1 3 1 2 1 4 1 2 1 3 1 2 1 5 1 2 1 3 1 2 1 ...
//% Loopless algorithm.
//% Cf. OEIS sequence A001511.

// Cf. comb/ruler-func-demo.cc for the zero-based ruler function
// Cf. comb/ruler-func-s-demo.cc for the one-based radix s ruler function
// Cf. comb/composition-nz-demo.cc for underlying compositions

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Stop when n+1 is encountered (==>2**n - 1  elements).");
    const ulong n1 = n + 1;

    ruler_func1 R(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef COMPOSITION_NZ_FIXARRAYS
    cout << "COMPOSITION_NZ_FIXARRAYS defined." << endl;
#endif
    do  { ++ct; }  while ( n1 != R.next() );
#else

    ulong j = R.data();
    do
    {
        ++ct;
        // cout << 0 << endl;  // for zero based ruler function
//        cout << setw(2) << ct << ":";
        cout << "  " << j;
        R.print_composition("  ");  cout << endl;

        j = R.next();
    }
    while ( j != n1 );

    // last element ==n could be processed here
#endif

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30
arg 1: 30 == n  [Stop when n+1 is encountered (==>2**n - 1  elements).]  default=6
./bin 30  2.50s user 0.00s system 99% cpu 2.499 total
 ==> 2^30/2.50 == 429,496,729 per second

 time ./bin 30
arg 1: 30 == n  [Stop when n+1 is encountered (==>2**n - 1  elements).]  default=6
COMPOSITION_NZ_FIXARRAYS defined.
./bin 30  1.78s user 0.00s system 99% cpu 1.786 total
 ==> 2^30/1.78 == 603,225,743 per second
*/

/*
BENCHARGS=31
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ruler-func1-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ruler-func1-demo.cc DEMOFLAGS=-DTIMING"
/// End:
