
#include "comb/partition-dist-d-asc.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions such that parts differ by at least d.
//% Representation as list of parts in increasing order.
//% Lexicographic order.
//% Cf. OEIS sequences
//%  A000041 (all partitions; d=0), A000009 (distinct parts; d=1),
//%  A003114 (d=2), A025157 (d=3), A025158 (d=4), A025159 (d=5),
//%  A025160 (d=6), A025161 (d=7), and A025162 (d=8).

// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-asc-demo.cc for (all) partitions

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 24;
    NXARG(n, "integer partitions of n");
    ulong d = 2;
    NXARG(d, "minimal difference of parts");

    partition_dist_d_asc P(n, d);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else


    ulong m = P.num_parts();
    do
    {
        ++ct;

        cout << setw(3) << ct << ":";
//        cout << " [" << setw(2) << m << "] ";
        P.print("  ");

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

 time ./bin 115 0
arg 1: 115 == n  [integer partitions of n]  default=24
arg 2: 0 == d  [minimal difference of parts]  default=2
 ct=1064144451
./bin 115 0  5.51s user 0.00s system 99% cpu 5.512 total
 ==> 1064144451/5.51 ==193,129,664  per second

 time ./bin 210 1
arg 1: 210 == n  [integer partitions of n]  default=24
arg 2: 1 == d  [minimal difference of parts]  default=2
 ct=884987529
./bin 210 1  3.98s user 0.00s system 99% cpu 3.982 total
 ==> 884987529/3.98 == 222,358,675 per second

 time ./bin 260 2
arg 1: 260 == n  [integer partitions of n]  default=24
arg 2: 2 == d  [minimal difference of parts]  default=2
 ct=754188500
./bin 260 2  3.26s user 0.00s system 99% cpu 3.259 total
 ==> 754188500/3.26 == 231,346,165 per second

 time ./bin 500 8
arg 1: 500 == n  [integer partitions of n]  default=24
arg 2: 8 == d  [minimal difference of parts]  default=2
 ct=1787713239
./bin 500 8  7.14s user 0.00s system 99% cpu 7.147 total
 ==> 1787713239/7.14 == 250,380,005 per second

*/

/*
BENCHARGS=115 0
BENCHARGS=210 1
BENCHARGS=260 2
BENCHARGS=500 8
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-dist-d-asc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-dist-d-asc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

