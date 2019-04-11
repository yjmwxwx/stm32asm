
#include "comb/combination-emk.h"

#include "aux0/binomial.h"
#include "comb/comb-print.h"

#include "jjassert.h"

#include "nextarg.h"
#include "fxtio.h"
#include "fxttypes.h"



//% Combinations in strong minimal-change order (Eades-McKay sequence).
//% Iterative generation via modulo moves.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Combinations (n choose k)");
    ulong k = 3;
    NXARG(k, "k elements at a time");

    combination_emk C(n, k);

    ulong j = 0;
    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(3) << ct << ":";
        const ulong *x = C.data();
        print_set("    ", x, k);
        cout << "  " << j << "  ";
        print_set_as_deltaset("  ", x, k, n);
//        print_set("    s=", C.s_, k);
//        print_set("    a=", C.a_, k);
        cout << endl;
#endif  // TIMING
        j = C.next();
    }
    while ( j<k );

    cout << " ct = " << ct << endl;
    jjassert( ct == binomial(n, k) );

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 32 20
arg 1: 32 == n  [Combinations (n choose k)]  default=7
arg 2: 20 == k  [k elements at a time]  default=3
 ct = 225792840
./bin 32 20  3.72s user 0.02s system 99% cpu 3.744 total
 ==> 225792840/3.72 == 60,697,000 per second

 time ./bin 32 12
arg 1: 32 == n  [Combinations (n choose k)]  default=7
arg 2: 12 == k  [k elements at a time]  default=3
 ct = 225792840
./bin 32 12  2.66s user 0.00s system 99% cpu 2.658 total
 ==> 225792840/2.66 == 84,884,526 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32 20
./bin 32 20  2.34s user 0.00s system 99% cpu 2.345 total
 ==> 225792840/2.34 == 96,492,666 per second

 time ./bin 32 12
./bin 32 12  1.80s user 0.00s system 99% cpu 1.804 total
 ==> 225792840/1.80 == 125,440,466 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/combination-emk-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/combination-emk-demo.cc DEMOFLAGS=-DTIMING"
/// End:
