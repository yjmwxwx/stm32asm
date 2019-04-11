
#include "comb/partition-odd-asc.h"

#include "fxtio.h"

#include "fxttypes.h"
#include "nextarg.h"

#include "jjassert.h"

//% Integer partitions into odd parts as weakly ascending list of parts.
//% Cf. OEIS sequence A000009.

// Cf. comb/partition-odd-desc-demo.cc for partitions into odd parts as weakly descending lists
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/partition-demo.cc for partitions given as multiplicities of parts
// Cf. comb/composition-nz-demo.cc for all compositions as lists of parts

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 18;
    NXARG(n, "integer partitions of n into odd parts");

    partition_odd_asc P(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = n;
    do
    {
#if 0  // only into distinct parts: A000700
        const ulong *x = P.data();
        bool q = true;
        for (ulong j = 1; j<m; ++j)
            if ( x[j]==x[j-1] )  { q=false; break; }
        if ( !q )  continue;
#endif
#if 0  // only into consecutive odd parts
        // A034178: Number of solutions to n = a^2 - b^2, a > b >= 0
        const ulong *x = P.data();
        bool q = true;
        for (ulong j=1; j<m; ++j)
            if ( x[j]!=x[j-1]+2 )  { q=false; break; }
        if ( !q )  continue;

#endif
        ++ct;

        cout << setw(3) << ct << ": ";
        P.print("  ");
//        cout << "           m=" << P.m_;
        cout << endl;

        jjassert( P.OK() );
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 220
arg 1: 220 == n  [integer partitions of n into odd parts]  default=16
  ct=1586861606
./bin 220  6.92s user 0.00s system 99% cpu 6.922 total
 ==> 1586861606/6.92 == 229,315,260 per second

*/

/*
BENCHARGS= 220
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-odd-asc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-odd-asc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

