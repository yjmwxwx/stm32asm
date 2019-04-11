
#include "comb/combination-endo.h"

#include "nextarg.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "comb/comb-print.h"


//% Strong minimal-change order for combinations (Chase's sequence) via endo steps

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Combinations (n choose k)");
    ulong k = 3;
    NXARG(k, "k elements at a time");

    combination_endo C(n, k);

    ulong j = 0;
    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(3) << ct << ":";
        const ulong *x = C.data();
        print_set("    ", x, k);
        print_set_as_deltaset("    ", x, k, n);
//        print_set("    s=", C.s_, k);
//        print_set("    a=", C.a_, k);
        cout << endl;
#endif  // TIMING
        j = C.next();
    }
    while ( j<k );

    cout << " ct = " << ct << endl;

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 32 20
arg 1: 32 == n  [Combinations (n choose k)]  default=8
arg 2: 20 == k  [k elements at a time]  default=3
 ct = 225792840
./bin 32 20  4.95s user 0.02s system 99% cpu 4.977 total
 ==> 225792840/4.95 == 45,614,715 per second

 time ./bin 32 12
arg 1: 32 == n  [Combinations (n choose k)]  default=8
arg 2: 12 == k  [k elements at a time]  default=3
 ct = 225792840
./bin 32 12  3.80s user 0.02s system 99% cpu 3.830 total
 ==> 225792840/3.80 == 59,419,168 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/combination-endo-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/combination-endo-demo.cc DEMOFLAGS=-DTIMING"
/// End:
