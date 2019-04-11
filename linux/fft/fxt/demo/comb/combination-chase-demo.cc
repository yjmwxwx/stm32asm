
#include "comb/combination-chase.h"
#include "aux0/binomial.h"

#include "comb/comb-print.h"

#include "fxttypes.h"

#include "jjassert.h"
#include "nextarg.h"

#include "fxtio.h"

//% Combinations in near-perfect minimal-change order (Chase's sequence).

//#define TIMING  // uncomment to disable printing

void
visit(const combination_chase &C, ulong ct)
{
    cout << setw(4) << ct << ":";
    const ulong *x = C.data();
    const ulong n = C.n_;
    print_deltaset_as_set("  ", x, n);  // zero based
//    print_deltaset_as_set1("  ", x, n);  // one based
    print_deltaset("  ", x, n);
    cout << endl;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Combinations (n choose k): n>=1");
    ulong k = 3;
    NXARG(k, " 1<=k<=n");

    if ( (k>n) || ( k==0 ) || ( n==0 ) )  { return 1; }

    combination_chase C(n, k);

    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        visit(C, ct);
#endif
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
arg 1: 32 == n  [Combinations (n choose k): n>=1]  default=7
arg 2: 20 == k  [ 1<=k<=n]  default=3
binomial(32, 20)=225792840
./bin 32 20  2.84s user 0.01s system 100% cpu 2.846 total
 ==> 225792840/2.84 == 79,504,521 per second

 time ./bin 32 12
arg 1: 32 == n  [Combinations (n choose k): n>=1]  default=7
arg 2: 12 == k  [ 1<=k<=n]  default=3
binomial(32, 12)=225792840
./bin 32 12  2.71s user 0.01s system 100% cpu 2.715 total
 ==> 225792840/2.71 == 83,318,391 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32 20
./bin 32 20  1.51s user 0.00s system 99% cpu 1.510 total
 ==> 225792840/1.51 == 149,531,682 per second

 time ./bin 32 12
./bin 32 12  1.46s user 0.00s system 99% cpu 1.461 total
 ==> 225792840/1.46 == 154,652,630 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/combination-chase-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/combination-chase-demo.cc DEMOFLAGS=-DTIMING"
/// End:

