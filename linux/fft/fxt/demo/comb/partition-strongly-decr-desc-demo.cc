
#include "comb/partition-strongly-decr-desc.h"

//#include "comb/partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Strongly decreasing partitions as list of parts.
//% A strongly decreasing partition of n is a partition
//%   a[1] + a[2] + ... + a[m] = n  such that a[k] > sum(j=k+1..m, a[j] ).
//% Lexicographic order.
//% Cf. OEIS sequences A040039 and A033485.

// Cf. comb/partition-nonsquashing-desc-demo.cc for non-squashing partitions
// Cf. comb/partition-desc-demo.cc for partitions as weakly descending lists

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 20;
    NXARG(n, "strongly decreasing partitions of n");

    partition_strongly_decr_desc P(n);

    ulong ct = 0;


#ifdef TIMING
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ulong m = P.num_parts();
    do
    {
#if 0  // odd parts only: A000000
        bool q = 1;
        for (ulong j=0; j<m; ++ j)
            if ( 0==(P.data()[j] & 1) )  { q=0; break; }
        if ( ! q )  continue;
#endif
//        cout << m << ", ";  continue;  // A000000
//        cout << P.data()[m-1] << ", ";  continue;  // A000000

        ++ct;
        cout << setw(4) << ct << ": ";

        cout << " [" << setw(2) << m << "] ";

//        cout << " [" << setw(2) << n-m << "] ";
//        cout << " [" << setw(2) << P.data()[m-1] << "] ";

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

 time ./bin 1000
arg 1: 1000 == n  [strongly decreasing partitions of n]  default=20
 ct=990735939
./bin 1000  4.05s user 0.00s system 99% cpu 4.046 total
 ==> 990735939/4.05 == 244,626,157 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-strongly-decr-desc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-strongly-decr-desc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

