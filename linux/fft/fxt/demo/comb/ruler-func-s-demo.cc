
#include "comb/ruler-func-s.h"
#include "comb/composition-nz-sorts.h"

#include "comb/comb-print.h"

//#include "jjassert.h"

#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"

//% Ruler function (one-based), s-valuations of s*n:
//% s=2:  1 2 1 3 1 2 1 4 1 2 1 3 1 2 1 5 1 2 1 3 1 2 1 ...
//%   cf. OEIS sequence A001511 and A007814 (zero based)
//% s=3:  1 1 2 1 1 2 1 1 3 1 1 2 1 1 2 1 1 3 1 1 2 1 1 ...
//%   cf. OEIS sequences A051064 and A007949 (zero based)
//% Loopless algorithm.

// Cf. comb/composition-nz-sorts-demo.cc for underlying compositions

// Cf. comb/ruler-func1-demo.cc for the one-based ruler function (s=2)
// Cf. comb/ruler-func-demo.cc for the zero-based ruler function (s=2)

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Stop when n+1 is encountered (==>s**n - 1  elements).");
    const ulong n1 = n + 1;

    ulong s = 3;
    NXARG(s, "ruler function for radix s (s>=2)");

    ruler_func_s R(n, s);

    ulong ct = 0;

#ifdef TIMING
#ifdef COMPOSITION_NZ_SORTS_FIXARRAYS
    cout << "COMPOSITION_NZ_SORTS_FIXARRAYS defined." << endl;
#endif
    do  { ++ct; }  while ( n1 != R.next() );
#else

    ulong j = R.data();
    do
    {
        ++ct;
//        cout << setw(2) << ct << ":";
        cout << "  " << j;  // one based
//        cout << "  " << j - 1;  // zero based
//        cout << ",";
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

 time ./bin 30 2
arg 1: 30 == n  [Stop when n+1 is encountered (==>s**n - 1  elements).]  default=3
arg 2: 2 == s  [ruler function for radix s (s>=2)]  default=3
./bin 30 2  2.85s user 0.00s system 99% cpu 2.858 total
 ==> 2^30/2.85 == 376,751,517 per second

 time ./bin 19 3
arg 1: 19 == n  [Stop when n+1 is encountered (==>s**n - 1  elements).]  default=3
arg 2: 3 == s  [ruler function for radix s (s>=2)]  default=3
./bin 19 3  3.58s user 0.00s system 99% cpu 3.585 total
 ==> 3^19/3.58 == 324,654,041 per second

 time ./bin 15 4
arg 1: 15 == n  [Stop when n+1 is encountered (==>s**n - 1  elements).]  default=3
arg 2: 4 == s  [ruler function for radix s (s>=2)]  default=3
./bin 15 4  3.71s user 0.00s system 99% cpu 3.717 total
 ==> 4^15/3.71 == 289,418,281 per second


 time ./bin 30 2
arg 1: 30 == n  [Stop when n+1 is encountered (==>s**n - 1  elements).]  default=3
arg 2: 2 == s  [ruler function for radix s (s>=2)]  default=3
COMPOSITION_NZ_SORTS_FIXARRAYS defined.
./bin 30 2  2.75s user 0.00s system 99% cpu 2.749 total
 ==> 2^30/2.75 == 390,451,572 per second

 time ./bin 19 3
arg 1: 19 == n  [Stop when n+1 is encountered (==>s**n - 1  elements).]  default=3
arg 2: 3 == s  [ruler function for radix s (s>=2)]  default=3
COMPOSITION_NZ_SORTS_FIXARRAYS defined.
./bin 19 3  3.31s user 0.00s system 99% cpu 3.314 total
 ==> 3^19/3.31 == 351,136,394 per second

 time ./bin 15 4
arg 1: 15 == n  [Stop when n+1 is encountered (==>s**n - 1  elements).]  default=3
arg 2: 4 == s  [ruler function for radix s (s>=2)]  default=3
COMPOSITION_NZ_SORTS_FIXARRAYS defined.
./bin 15 4  2.91s user 0.00s system 99% cpu 2.908 total
 ==> 4^15/2.91 == 368,983,444 per second
*/

/*
BENCHARGS=30 2
BENCHARGS=19 3
BENCHARGS=15 4
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ruler-func-s-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ruler-func-s-demo.cc DEMOFLAGS=-DTIMING"
/// End:
