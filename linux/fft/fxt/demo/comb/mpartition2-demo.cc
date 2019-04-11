
#include "comb/mpartition2.h"

#include "fxtio.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions of n into m parts.
//% Representation as list of parts in weakly ascending order.
//% Same functionality as class mpartition, this
//%   implementation avoids the auxiliary array s[].
//% Cf. OEIS sequence A008284.

// Cf. comb/mpartition-demo.cc (same output)
// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending compositions
// Cf. comb/partition-desc-demo.cc for partitions as weakly descending compositions

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 19;
    NXARG(n, "integer partitions of n");
    ulong m = 11;
    NXARG(m, "partitions into m parts");

    mpartition2 P(n, m);
    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(3) << ct << ": ";
        const ulong *x = P.data();
        for (ulong k=0; k<m; ++k)
            cout << " " << setw(2) << x[k];
        cout << endl;
#endif
//        if ( ct > 20 )  break;

    }
    while ( P.next() );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.8.0:

 time ./bin 140 20
arg 1: 140 == n  [integer partitions of n]  default=19
arg 2: 20 == m  [partitions into m parts]  default=11
 ct=693703134
./bin 140 20  3.89s user 0.00s system 99% cpu 3.898 total
 ==> 693703134/3.89 == 178,329,854 per second

*/

/*
BENCHARGS=140 20
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mpartition2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mpartition2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

