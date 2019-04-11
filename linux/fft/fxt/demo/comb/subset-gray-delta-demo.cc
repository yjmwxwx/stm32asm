
#include "comb/subset-gray-delta.h"

#include "comb/comb-print.h"  // print_deltaset_as_set()
#include "nextarg.h"
#include "fxttypes.h"

#include "fxtio.h"


//% Generate all subsets (as delta sets) in minimal-change order.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Size of the set");
//    bool rq = 0;
//    NXARG(rq, "Whether to generate subsets in reversed order");

    bool cq = 0;
    NXARG(cq, "Whether to start with full set");

    subset_gray_delta S(n);
    S.first(cq);


#ifdef TIMING
#ifdef SUBSET_GRAY_DELTA_MAX_ARRAY_LEN
    cout << "SUBSET_GRAY_DELTA_MAX_ARRAY_LEN is defined." << endl;
#endif
//    if ( rq )  do {;} while ( S.prev()!=n );
//    else
    do {;} while ( S.next()!=n );

#else  // TIMING

    const ulong *x = S.data();
    ulong q;
    do
    {
        cout << setw(2) << S.current() << ":";

        // print as bit set:
        print_deltaset("  ", x, n);
        cout << "   chg @ " << S.pos();

        print_deltaset_as_set("    ", x, n);
        cout << endl;

//        if ( rq )  q = S.prev();
//        else
        q = S.next();
    }
    while ( q!=n );
#endif  // TIMING

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 30
arg 1: 30 == n  [Size of the set]  default=5
arg 2: 0 == cq  [Whether to start with full set]  default=0
./bin 30  5.90s user 0.02s system 100% cpu 5.912 total
 ==> 2^30/5.90 == 181,990,139 per second

 time ./bin 30
arg 1: 30 == n  [Size of the set]  default=5
arg 2: 0 == cq  [Whether to start with full set]  default=0
SUBSET_GRAY_DELTA_MAX_ARRAY_LEN is defined.
./bin 30  5.84s user 0.01s system 99% cpu 5.853 total
 ==> 2^30/5.84 == 183,859,901 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/subset-gray-delta-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/subset-gray-delta-demo.cc DEMOFLAGS=-DTIMING"
/// End:

