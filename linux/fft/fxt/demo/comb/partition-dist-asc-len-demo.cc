
#include "comb/partition-dist-asc-len.h"

//#include "comb/partition-odd-to-dist.h"
//#include "comb/comb-print.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions into distinct parts.
//% Representation as list of parts in increasing order.
//% Major order by number of parts, minor order lexicographic.
//% Cf. OEIS sequence A000009.


// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts in lexicographic order
// Cf. comb/partition-desc-bb-demo.cc all partitions, with bounds for size and number of parts

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 19;
    NXARG(n, "integer partitions of n into distinct parts");

    partition_dist_asc_len P(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
    do
    {
        ++ct;

#if 1 // whether to print anything
        cout << setw(4) << ct << ":";
//        cout << " [" << setw(2) << m << "] ";
        P.print("  ");

//        ulong mt = partition_asc_dist_to_odd(P.data(), m, T);
//        print_vec("\n  T: ", T, mt);
//        ulong mx = partition_asc_odd_to_dist(T, mt, X);
//        print_vec("\n  X: ", X, mx);
//        for (ulong i=0; i<m; ++i)  jjassert( X[i] == P.data()[i] );
//        cout << endl;

        cout << endl;

        jjassert( P.OK() );
#endif
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

// easy case on:
 time ./bin 220
arg 1: 220 == n  [integer partitions of n into distinct parts]  default=19
 ct=1586861606
./bin 220  6.02s user 0.00s system 99% cpu 6.025 total
 ==> 1586861606/6.02 == 263,598,273 per second

// easy case off:
% time ./bin 220
arg 1: 220 == n  [integer partitions of n into distinct parts]  default=19
 ct=1586861606
./bin 220  6.79s user 0.00s system 99% cpu 6.799 total
 ==> 1586861606/6.79 == 233,705,685 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-dist-asc-len-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-dist-asc-len-demo.cc DEMOFLAGS=-DTIMING"
/// End:
