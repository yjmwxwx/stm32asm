
#include "comb/partition-nonsquashing-desc.h"

#include "comb/partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Non-squashing partitions as weakly descending list of parts.
//% A non-squashing partition of n is a partition a[1] + a[2] + ... + a[m] = n
//%   such that a[k] >= sum(j=k+1..m, a[j] ).
//% Lexicographic order.
//% With parameter sd = true generate strongly decreasing partitions:
//%   partitions such that a[k] > sum(j=k+1..m, a[j] ).
//% See:
//%  N. J. A. Sloane, James A. Sellers: "On Non-Squashing Partitions",
//%    arXiv:math/0312418 [math.CO], (22-December-2003).
//% Cf. OEIS sequences A018819, A000123 (non-squashing), and A040039 (strongly decreasing).

// Cf. comb/partition-binary-desc-demo.cc for binary partitions as weakly descending lists
// Cf. comb/partition-strongly-decr-desc-demo.cc for strongly decreasing partitions
// Cf. comb/partition-desc-demo.cc for partitions as weakly descending lists

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 20;
    NXARG(n, "non-squashing (or strongly decreasing) partitions of n");
    bool sd = false;
    NXARG(sd, "whether strongly decreasing (otherwise non-squashing)");

    partition_nonsquashing_desc P(n, sd);

    ulong ct = 0;


#ifdef TIMING
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

 time ./bin 1000
arg 1: 1000 == n  [non-squashing partitions of n]  default=20
 ct=1981471878
./bin 1000  7.41s user 0.00s system 99% cpu 7.416 total
 ==> 1981471878/7.41 == 267,405,111 per second

*/

/*
## A018819:
echo $(for n in $(seq 1 50); do ./bin $n 0 ; done | grep ct ) | sed 's/ ct=/, /g;'

## A040039:
echo $(for n in $(seq 1 50); do ./bin $n 1 ; done | grep ct ) | sed 's/ ct=/, /g;'

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-nonsquashing-desc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-nonsquashing-desc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

