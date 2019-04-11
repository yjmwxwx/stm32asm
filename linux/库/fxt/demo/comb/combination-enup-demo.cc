
#include "comb/combination-enup.h"

#include "nextarg.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "comb/comb-print.h"


//% Strong minimal-change order for combinations via enup (endo) steps

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Combinations (n choose k)");
    ulong k = 3;
    NXARG(k, "k elements at a time");

    combination_enup C(n, k);

    ulong j = 0;
    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(4) << ct << ":";
        const ulong *x = C.data();
        print_set("    ", x, k);
        print_set_as_deltaset("    ", x, k, n);
//        print_set("    s=", C.s_, k);
//        print_set("    a=", C.a_, k);

//        cout << "    ";  // composition
//        for (ulong i=1; i<=k; ++i)  cout << " " << (x[i]-x[i-1]);

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
./bin 32 20  5.13s user 0.02s system 99% cpu 5.161 total
 ==> 225792840/5.13 == 44,014,198 per second

 time ./bin 32 12
arg 1: 32 == n  [Combinations (n choose k)]  default=8
arg 2: 12 == k  [k elements at a time]  default=3
 ct = 225792840
./bin 32 12  4.00s user 0.01s system 99% cpu 4.015 total
 ==> 225792840/4.00 == 56,448,210 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32 20
./bin 32 20  2.58s user 0.00s system 99% cpu 2.584 total
 ==> 225792840/2.58 == 87,516,604 per second

 time ./bin 32 12
./bin 32 12  2.03s user 0.00s system 99% cpu 2.039 total
 ==> 225792840/2.03 == 111,228,000 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/combination-enup-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/combination-enup-demo.cc DEMOFLAGS=-DTIMING"
/// End:
