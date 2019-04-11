
#include "comb/partition-2fall-asc.h"

#include "comb/partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% Partitions of n is a partition a[1] + a[2] + ... + a[m] = n
//%   such that a[k] >= 2 * a[k-1].
//% Representation as weakly ascending list of parts.
//% Lexicographic order.
//% Cf. OEIS sequence A000929.


// Cf. comb/partition-2fall-desc-demo.cc same in descending order
// Cf. comb/partition-s-desc-demo.cc for partitions into parts 2^k-1


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 35;
    NXARG(n, "partitions of n");

    partition_2fall_asc P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef PARTITION_2FALL_ASC_FIXARRAYS
    cout << "PARTITION_2FALL_ASC_FIXARRAYS is defined" << endl;
#endif
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    bool aa = 0;
//    NXARG(aa, "Whether to render as ASCII art");

    ulong m = P.num_parts();
    do
    {
//        cout << m-1 << ", ";  continue;  // A000000
//        cout << P.data()[m-1] << ", ";  continue;  // A000000

        ++ct;
        cout << setw(4) << ct << ": ";

        cout << " [" << setw(2) << m << "] ";

//        cout << " [" << setw(2) << n-m << "] ";
//        cout << " [" << setw(2) << P.data()[m-1] << "] ";

        P.print("  ");

        if ( aa )  // ASCII art
        {
            P.print_aa();
//            P.print_conj_aa();
            cout << endl;
            cout << endl;
        }

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

GCC 4.9.0:

 time ./bin 1500
arg 1: 1500 == n  [partitions of n]  default=32
 ct=520383836
./bin 1500  3.16s user 0.00s system 99% cpu 3.163 total
 ==> 520383836/3.16 == 164,678,429 per second

 time ./bin 1500
arg 1: 1500 == n  [partitions of n]  default=32
PARTITION_2FALL_ASC_FIXARRAYS is defined
 ct=520383836
./bin 1500  2.28s user 0.00s system 99% cpu 2.288 total
 ==> 520383836/2.28 == 228,238,524 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-2fall-asc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-2fall-asc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

