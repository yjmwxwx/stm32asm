
#include "comb/subset-gray.h"

#include "comb/comb-print.h"  // print_set()

#include "nextarg.h"
#include "fxttypes.h"

#include "fxtio.h"
#include "jjassert.h"


//% Generate all subsets in minimal-change order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Size of the set (n>=1)");
    jjassert( n >= 1 );
    bool rq = 0;
    NXARG(rq, "Whether to generate subsets in reversed order");

    subset_gray S(n);

    S.first();

#ifdef TIMING
#ifdef SUBSET_GRAY_MAX_ARRAY_LEN
    cout << "SUBSET_GRAY_MAX_ARRAY_LEN is defined." << endl;
#endif

    if ( !rq )
    {
        cout << "forward:" << endl;
        while ( S.next() )  {;}
    }
    else
    {
        cout << "backward:" << endl;
        while ( S.prev() )  {;}
    }

#else  // TIMING
    ulong num, idx = 0;
    do
    {
        num = S.num();
        cout << setw(4) << idx << ":  ";
        S.print_deltaset("    ");
        cout << "  #=" << num;
        S.print_set("    ");
        cout << endl;

        ++idx;
        num = ( rq ? S.prev() : S.next() );
    }
    while ( num );
#endif  // TIMING

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 30 0
SUBSET_GRAY_MAX_ARRAY_LEN is defined.
forward:
./bin 30 0  4.03s user 0.00s system 100% cpu 4.030 total
 ==> 2^30/4.03 == 266,437,177 per second

 time ./bin 30 1
SUBSET_GRAY_MAX_ARRAY_LEN is defined.
backward:
./bin 30 1  5.98s user 0.03s system 99% cpu 6.009 total
 ==> 2^30/5.98 == 179,555,488 per second


 time ./bin 30 0
forward:
./bin 30 0  4.44s user 0.01s system 100% cpu 4.452 total
 ==> 2^30/4.44 == 241,833,744 per second

 time ./bin 30 1
backward:
./bin 30 1  6.41s user 0.02s system 99% cpu 6.425 total
 ==> 2^30/6.41 == 167,510,424 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 0
SUBSET_GRAY_MAX_ARRAY_LEN is defined.
forward:
./bin 30 0  3.17s user 0.00s system 99% cpu 3.172 total
 ==> 2^30/3.17 == 338,719,818 per second

 time ./bin 30 1
SUBSET_GRAY_MAX_ARRAY_LEN is defined.
backward:
./bin 30 1  3.18s user 0.00s system 99% cpu 3.183 total
 ==> 2^30/3.18 == 337,654,661 per second


 time ./bin 30 0
forward:
./bin 30 0  2.91s user 0.00s system 99% cpu 2.918 total
 ==> 2^30/2.91 == 368,983,444 per second

 time ./bin 30 1
backward:
./bin 30 1  4.11s user 0.00s system 99% cpu 4.113 total
 ==> 2^30/4.11 == 261,251,052 per second


*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/subset-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/subset-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

