
#include "comb/combination-revdoor.h"

#include "aux0/binomial.h"
#include "comb/comb-print.h"  // print_set_as_deltaset()

#include "fxttypes.h"
#include "jjassert.h"
#include "nextarg.h"

#include "fxtio.h"

//% Generating all combinations in minimal-change order: revolving door algorithm.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Combination (n choose k) in minimal-change order: n>=1");
    ulong k = 4;
    NXARG(k, "(n choose k):  1<=k<=n");
    jjassert( k<=n );
    jjassert( k>=1 );
    jjassert( n>=1 );

    combination_revdoor C(n, k);

    ulong ct = 0;
    do
    {
#ifndef TIMING
        cout << setw(3) << ct << ":    ";
        C.print_set("  ");
        C.print_deltaset("    ");
        cout << endl;
#endif  // TIMING
        ++ct;
    }
    while ( C.next() );

    ulong bnk =  binomial(n, k);
    cout << "binomial(" << n << ", " << k << ")=" << bnk << endl;
    jjassert( bnk==ct );
    cout << endl;

    return 0;
}
// -------------------------

// for n in $(seq 1 10); do for k in $(seq 1 $n); do ./bin $n $k || break 2; done; done

/*
Timing:

 time ./bin 32 20
arg 1: 32 == n  [(n choose k): n>=1]  default=7
arg 2: 20 == k  [(n choose k):  1<=k<=n]  default=4
arg 3: 0 == rq  [Option: print in reverse order]  default=0
binomial(32, 20)=225792840
./bin 32 20  1.90s user 0.02s system 99% cpu 1.929 total
 ==> 225792840/1.90 == 118,838,336 per second

 time ./bin 32 12
arg 1: 32 == n  [(n choose k): n>=1]  default=7
arg 2: 12 == k  [(n choose k):  1<=k<=n]  default=4
arg 3: 0 == rq  [Option: print in reverse order]  default=0
binomial(32, 12)=225792840
./bin 32 12  1.23s user 0.02s system 99% cpu 1.247 total
 ==> 225792840/1.23 == 183,571,414 per second

*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

  time ./bin 32 20
binomial(32, 20)=225792840
./bin 32 20  0.96s user 0.00s system 99% cpu 0.958 total
 ==> 225792840/0.96 == 235,200,875 per second

 time ./bin 32 12
binomial(32, 12)=225792840
./bin 32 12  0.66s user 0.00s system 99% cpu 0.661 total
 ==> 225792840/0.66 == 342,110,363 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/combination-revdoor-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/combination-revdoor-demo.cc DEMOFLAGS=-DTIMING"
/// End:

