
#include "comb/arrangement-rgs.h"
#include "comb/print-arrangement-rgs-perm.h"
// demo-include comb/print-arrangement-rgs-perm.cc
#include "comb/is-arrangement-rgs.h"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% RGS for arrangements (all permutations of all subsets):
//% a digit is at most 1 + the number of nonzero digits in the prefix.
//% The positions of nonzero digits determine the subset, and
//%   their values (decreased by 1) are the (left) inversion table
//%   (a rising factorial number) for the permutation.
//% Lexicographic order.
//% Cf. OEIS sequence A000522.

// 1, 2, 5, 16, 65, 326, 1957, 13700, 109601, 986410, 9864101, 108505112, ...

//#define TIMING  // uncomment to disable printing

// Cf. comb/arrangement-lex-demo.cc for arrangements in lexicographic order.
// Cf. comb/kperm-lex-demo.cc for arrangements of k-subsets, lexicographic order
// Cf. comb/kperm-gray-demo.cc for arrangements of k-subsets, minimal-change order


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Length if RGS (number of elements in set)");

    arrangement_rgs A(n);

    ulong ct = 0;

#ifdef TIMING
    bool bw = 0;
    NXARG(bw, "With benchmark: whether to generate backward order");

#ifdef ARRANGEMENT_RGS_FIXARRAYS
    cout << "ARRANGEMENT_RGS_FIXARRAYS is defined" << endl;
#endif
    if ( bw )
    {
        cout << "backward:" << endl;
        A.last();
        do  { ++ct; }  while ( A.prev() );
    }
    else
    {
        cout << "forward:" << endl;
        A.first();
        do  { ++ct; }  while ( A.next() );
    }
#else  // TIMING


    // for printing: rising factorial number F[] and subset permutation P[]:
    ulong F[32], P[32];
    ulong j = 0;
//    A.last();
    do
    {
#if 0 // limit max digit
        ulong m = 0;
        for (ulong k=0; k<n; ++k)
            if ( A.data()[k] > m )  m = A.data()[k];
//        if ( m>1 )  continue;  // 2^n (set partitions with at most 2 blocks)
        if ( m>2 )  continue;  // A007051, A124302 (set partitions with at most 3 blocks)
//        if ( m>3 )  continue;  // A000000 (not: set partitions with at most 4 blocks)
#endif

        ++ct;
        cout << setw(4) << ct << ":";

        // print RGS:
        A.print("    ", true );
//        print_vec("    ", A.z_+1, n, true );  // internal data

//        cout << setw(4) << j;

        print_arrangement_rgs_perm("    ", A.data(), n, F, P, false);

        cout << endl;

        jjassert( A.OK() );
    }
    while ( (j=A.next()) );
//    while ( (j=A.prev()) );

#endif  // TIMING

    cout << " ct=" << ct;  // Arrangement number n
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12 0
arg 1: 12 == n  [Length if RGS (number of elements in set)]  default=4
arg 2: 0 == bw  [With benchmark: whether to generate backward order]  default=0
forward:
 ct=1302061345
./bin 12  3.71s user 0.00s system 99% cpu 3.713 total
 ==> 1302061345/3.71 == 350,959,931 per second

 time ./bin 12 1
arg 1: 12 == n  [Length if RGS (number of elements in set)]  default=4
arg 2: 1 == bw  [With benchmark: whether to generate backward order]  default=0
backward:
 ct=1302061345
./bin 12 1  4.00s user 0.00s system 99% cpu 4.007 total
 ==> 1302061345/4.00 == 325,515,336 per second

defining ARRANGEMENT_RGS_FIXARRAYS gives a slowdown


GCC 4.8.0:

 time ./bin 12 0
arg 1: 12 == n  [Length if RGS (number of elements in set)]  default=4
arg 2: 0 == bw  [With benchmark: whether to generate backward order]  default=0
ARRANGEMENT_RGS_FIXARRAYS is defined
forward:
 ct=1302061345
./bin 12 0  5.02s user 0.00s system 99% cpu 5.022 total
 ==> 1302061345/5.02 == 259,374,769 per second

 time ./bin 12 1
arg 1: 12 == n  [Length if RGS (number of elements in set)]  default=4
arg 2: 1 == bw  [With benchmark: whether to generate backward order]  default=0
ARRANGEMENT_RGS_FIXARRAYS is defined
backward:
 ct=1302061345
./bin 12 1  4.23s user 0.00s system 99% cpu 4.233 total
 ==> 1302061345/4.23 ==307,815,920  per second


 time ./bin 12 0
arg 1: 12 == n  [Length if RGS (number of elements in set)]  default=4
arg 2: 0 == bw  [With benchmark: whether to generate backward order]  default=0
forward:
 ct=1302061345
./bin 12 0  5.83s user 0.00s system 99% cpu 5.829 total
 ==> 1302061345/5.83 == 223,338,138 per second

 time ./bin 12 1
arg 1: 12 == n  [Length if RGS (number of elements in set)]  default=4
arg 2: 1 == bw  [With benchmark: whether to generate backward order]  default=0
backward:
 ct=1302061345
./bin 12 1  5.36s user 0.00s system 99% cpu 5.362 total
 ==> 1302061345/5.36 == 242,921,892 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/arrangement-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/arrangement-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

