
#include "comb/setpart-rgs-gray.h"
// demo-include "comb/print-setpart.cc"

// demo-include "comb/setpart-rgs-gray.cc"

#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"

//% Set partitions of the n-set as restricted growth strings (RGS):
//% strings s[0, 1, ..., n-1] such that s[k] <= max(s[0], s[1], ..., s[k-1]) + 1.
//% Minimal-change order for set partitions,
//%  note that the RGS can change in more than one position.


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Partition set of n elements");
    int dr0 = +1;
    NXARG(dr0, "Starting direction in recursion (+-1)");
    dr0 = ( (dr0>0) ? +1 : -1 );
//    ulong px = 0;
//    NXARG(px, "If !=0, only list partitions into exactly px sets");

    setpart_rgs_gray P(n, dr0);

    ulong ct = 0;
#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else  // TIMING
    do
    {
//        if ( px && (P.m_[n]!=px) )  continue;
        ++ct;
        cout << setw(4) << ct << ":";
        P.print("  ", true);
        P.print_set("    ");
        cout << endl;

        jjassert( P.OK() );
    }
    while ( P.next() );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 15 0
arg 1: 15 == n  [Partition set of n elements]  default=5
arg 2: 0 == dr0  [Starting direction in recursion (+-1)]  default=1
 ct = 1382958545
./bin 15 0  8.98s user 0.03s system 100% cpu 9.014 total
 ==> 1382958545/8.98 == 154,004,292 per second

same with dr0 == 1

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

time ./bin 15 0
arg 1: 15 == n  [Partition set of n elements]  default=5
arg 2: 0 == dr0  [Starting direction in recursion (+-1)]  default=1
 ct = 1382958545
./bin 15 0  5.52s user 0.00s system 99% cpu 5.526 total
 ==> 1382958545/5.52 == 250,535,968 per second

*/

/*
BENCHARGS=15
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/setpart-rgs-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/setpart-rgs-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

