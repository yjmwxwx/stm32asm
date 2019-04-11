
#include "comb/partition-s-desc.h"

//#include "comb/partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% S-partitions: integer partitions into parts 2^n-1.
//% Representation as weakly descending list of parts.
//% Cf. OEIS sequence A000929.

// Cf. comb/partition-2fall-desc-demo.cc for partitions such that 2*a[k] <= a[k-1]
// Cf. comb/partition-2fall-asc-demo.cc for partitions such that a[k] >= 2*a[k-1]

// Cf. comb/partition-desc-demo.cc for all partitions as weakly descending lists

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 35;
    NXARG(n, "integer partitions of n into parts 2^k-1");

    partition_s_desc P(n);

    ulong ct = 0;


#ifdef TIMING
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    bool aa = 0;
//    NXARG(aa, "Whether to render as ASCII art");

    ulong m = P.num_parts();
    do
    {
        ++ct;
//        cout << "[" << setw(2) << ct << "]";  // format for OEIS examples
        cout << setw(4) << ct << ": ";
        cout << " [" << setw(2) << m << "] ";

//        cout << " d=" << setw(2) << P.durfee_n() << " ";


//        cout << " [" << setw(2) << n-m << "] ";
//        cout << " [" << setw(2) << P.data()[m-1] << "] ";
//        cout << " [" << setw(2) << P.s_ << "] ";

        P.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
            P.print_conj_aa();
            cout << endl;
            cout << endl;
        }

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

 time ./bin 1700
arg 1: 1700 == n  [integer partitions of n into parts 2^k-1]  default=32
 ct=1158139807
./bin 1700  5.42s user 0.00s system 99% cpu 5.426 total
 ==> 1158139807/5.42 == 213,678,931 per second


// without "easy case" optimization: (drastic slowdown)

 time ./bin 900
arg 1: 900 == n  [integer partitions of n into parts 2^k-1]  default=32
 ct=24007079
./bin 900  6.67s user 0.00s system 99% cpu 6.676 total
 ==> 24007079/6.67 == 3,599,262 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-s-desc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-s-desc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

