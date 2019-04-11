
#include "comb/ruler-func.h"

#include "comb/comb-print.h"

#include "nextarg.h"
#include "fxttypes.h"

#include "fxtio.h"

//% Ruler function (zero-based), 2-valuations of n:
//%   0 1 0 2 0 1 0 3 0 1 0 2 0 1 0 4 0 1 0 2 0 1 ...
//% Loopless algorithm (specialization of Knuth's method
//%   for mixed radix Gray code).
//% Cf. OEIS sequence A007814.

// Cf. comb/ruler-func1-demo.cc for the one-based ruler function

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Stop when n is encountered (==>2**n elements).");

    ruler_func R(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef RULER_FUNC_MAX_ARRAY_LEN
    cout << "RULER_FUNC_MAX_ARRAY_LEN is defined." << endl;
#endif
    do  { ++ct; }  while ( n != R.next() );

#else

    ulong j;
    do
    {
        ++ct;
        j = R.next();
        cout << " " << j;
        print_vec("    ", R.f_, n);  cout << endl;  // focus pointers
    }
    while ( j!=n );

#endif
    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 30
arg 1: 30 == n  [Stop when n is encountered in the sequence (==>2**n elements).]  default=6
RULER_FUNC_MAX_ARRAY_LEN is defined.
./bin 30 0  3.66s user 0.00s system 99% cpu 3.666 total
 ==> 2^30/3.66 == 293,372,083 per second

 time ./bin 30
arg 1: 30 == n  [Stop when n is encountered in the sequence (==>2**n elements).]  default=6
./bin 30 0  4.40s user 0.00s system 99% cpu 4.407 total
 ==> 2^30/4.40 == 244,032,232 per second
*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30
arg 1: 30 == n  [Stop when n is encountered in the sequence (==>2**n elements).]  default=6
RULER_FUNC_MAX_ARRAY_LEN is defined.
./bin 30  2.76s user 0.00s system 99% cpu 2.766 total
 ==> 2^30/2.76 == 389,036,892 per second

 time ./bin 30
arg 1: 30 == n  [Stop when n is encountered in the sequence (==>2**n elements).]  default=6
./bin 30  3.21s user 0.00s system 99% cpu 3.213 total
 ==> 2^30/3.21 == 334,499,010 per second
*/

/*
BENCHARGS=31
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ruler-func-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ruler-func-demo.cc DEMOFLAGS=-DTIMING"
/// End:
