
#include "comb/arrangement-lex.h"
// demo-include comb/perm-lex-inv.h

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Arrangements (all permutations of all subsets).
//% Lexicographic order.
//% Cf. OEIS sequence A000522.

// 1, 2, 5, 16, 65, 326, 1957, 13700, 109601, 986410, 9864101, 108505112, ...

//#define TIMING  // uncomment to disable printing

// Cf. comb/arrangement-rgs-demo.cc RGS for arrangements
// Cf. comb/kperm-lex-demo.cc for arrangements of k-subsets, lexicographic order
// Cf. comb/kperm-gray-demo.cc for arrangements of k-subsets, minimal-change order


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Length if RGS (number of elements in set)");

    arrangement_lex A(n);
    A.first();

    ulong ct = 0;

#ifdef TIMING
    A.first();
    do  { ++ct; }  while ( A.next() );
#else  // TIMING


    ulong j = 0;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

        A.print("    ", false );

        cout << endl;

//        jjassert( A.OK() );
    }
    while ( (j=A.next()) );

#endif  // TIMING

    cout << " ct=" << ct;  // Arrangement number n
    cout << endl;

    return 0;
}
// -------------------------

/*

Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.1:
 time ./bin 12
arg 1: 12 == n  [Length if RGS (number of elements in set)]  default=4
 ct=1302061345
./bin 12  3.00s user 0.00s system 99% cpu 2.999 total
 ==> 1302061345/3.00 == 434,020,448 per second


Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)

GCC 4.9.2:
 time ./bin 12
arg 1: 12 == n  [Length if RGS (number of elements in set)]  default=4
 ct=1302061345
./bin 12  1.76s user 0.00s system 99% cpu 1.768 total
 ==> 1302061345/1.76 == 739,807,582 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/arrangement-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/arrangement-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

