
#include "comb/rgs-maxincr.h"

#include "comb/comb-print.h"

//#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"

//% Restricted growth strings (RGS) s[0,...,n-1]
//%   so that s[k] <= max( j < k, s[j] + i )
//% Lexicographic order
//% OEIS sequences:
//% i=1 ==> Bell numbers, A000110
//% i=2 ==> A080337, see also A080107
//% i=3 ==> A189845


//#define TIMING  // uncomment to disable printing

//#define STATS  // uncomment to count descends


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Length of restricted growth strings");
    ulong i = 2;
    NXARG(i, "Increment allowed (1==> set partitions)");

    rgs_maxincr R(n, i);
#ifdef STATS
    const ulong *x = R.data();
    ulong *st = new ulong[n];
    for (ulong k=0; k<n; ++k)  st[k] = 0;
#endif  // STATS

    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(4) << ct <<":";
        R.print("  ", true);
//        print_vec("    ", R.m_, n, true);
#ifdef STATS
        ulong nd = 0;
//        for (ulong k=1; k<n; ++k)  nd += ( x[k-1] > x[k] );  // descends
//        for (ulong k=1; k<n; ++k)  nd += ( x[k-1] >= x[k] );  // non-ascends
//        for (ulong k=1; k<n; ++k)  nd += ( x[k-1] < x[k] );  // ascends
//        for (ulong k=1; k<n; ++k)  nd += ( x[k-1] < x[k] );  // non-ascends
//        for (ulong k=1; k<n; ++k)  nd += ( x[k-1] == x[k] );  // equality
//        for (ulong k=1; k<n; ++k)  nd += ( x[k-1] != x[k] );  // non-equality
        nd = x[n-1]/i;  // last element
        cout << "  nd=" << nd;
        ++st[nd];
#endif  // STATS
        cout << endl;
#endif  // TIMING
    }
    while ( R.next() );

#ifdef STATS
    cout << "stats: ";
    for (ulong k=0; k<n; ++k)  cout << st[k] << ", ";
    delete [] st;
#endif  // STATS

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 15 1
 ct = 1382958545
./bin 15 1  12.09s user 0.06s system 99% cpu 12.150 total
 ==> 1382958545/12.09 == 114,388,630 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 15 1
arg 1: 15 == n  [Length of restricted growth strings]  default=4
arg 2: 1 == i  [Increment allowed (1==> set partitions)]  default=2
 ct=1382958545
./bin 15 1  6.72s user 0.00s system 99% cpu 6.724 total
 ==> 1382958545/6.72 == 205,797,402 per second
*/

/*
BENCHARGS=15 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/rgs-maxincr-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/rgs-maxincr-demo.cc DEMOFLAGS=-DTIMING"
/// End:

