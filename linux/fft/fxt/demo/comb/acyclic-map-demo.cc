
#include "comb/acyclic-map.h"

//#include "comb/comb-print.h"


#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"


//% Acyclic maps: maps from {1, 2, 3, .., n} to {0, 1, 2, 3, ..., n} where
//%  each element is ultimately mapped to 0.
//% Lexicographic order.
//% See OEIS sequence A000272.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "elements in the domain are {1, 2, 3, .., n}");

    ulong m = n;
    NXARG(m, "max value each element is mapped to, must be <= n");
    jjassert( m <= n );

    acyclic_map M(n, m);

    ulong ct = 0;

#ifdef TIMING
    M.first();
    do  { ++ct; }  while ( M.next() );

#else  // TIMING

    do
    {
        ++ct;

        cout << " " << setw(4) << ct << ":";
        M.print("  ", true );
//        cout << "  " << M.pos();
        cout << endl;

        jjassert( M.OK() );
    }
    while ( M.next() );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.1:

 time ./bin 9
arg 1: 9 == n  [Number of digits]  default=4
arg 2: 10 == rr  [Base (radix) of digits (0==>falling factorial, 1==>rising factorial)]  default=10
 ct=100000000
./bin 9  1.46s user 0.00s system 99% cpu 1.467 total
 ==> 100000000/1.46 == 68,493,150 per second

*/

/*
Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)

GCC 4.9.2:

 time ./bin 9
arg 1: 9 == n  [elements in the domain are {1, 2, 3, .., n}]  default=3
arg 2: 9 == m  [max value each element is mapped to, must be <= n]  default=9
 ct=100000000
./bin 9  0.92s user 0.00s system 99% cpu 0.920 total
 ==> 100000000/0.92 == 108,695,652 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/acyclic-map-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/acyclic-map-demo.cc DEMOFLAGS=-DTIMING"
/// End:
