
// demo-is-self-contained

#include "fxttypes.h"
#include "jjassert.h"
#include "comb/comb-print.h"

#include "fxtio.h"

#include "nextarg.h"

//% Generating all combinations in minimal-change order, recursive implementation.

//#define TIMING  // uncomment to disable printing


ulong N;    // number of bits in words
ulong K;    // number of bits in words
ulong *x;  // elements in combination at x[1] ... x[k]

ulong ct;   // count objects

void visit()
{
#ifndef TIMING
    cout << setw(4) << ct << ":";
    print_set("    ", x+1, K, 1);
    print_set1_as_deltaset("    ", x+1, K, N);
    cout << endl;
#endif
}
// -------------------------


void comb_gray(ulong n, ulong k, bool z)
{
    if ( k==n )
    {
        for (ulong j=1; j<=k; ++j)  x[j] = j;
        ++ct;
        visit();
        return;
    }

    if ( z )  // forward:
    {
        comb_gray(n-1, k, z);
        if ( k>0 )  { x[k] = n;  comb_gray(n-1, k-1, !z); }
    }
    else     // backward:
    {
        if ( k>0 )  { x[k] = n;  comb_gray(n-1, k-1, !z); }
        comb_gray(n-1, k, z);
    }
}
// -------------------------


void comb_gray_compl(ulong n, ulong k, bool z)
{
    if ( k==n )
    {
        for (ulong j=1; j<=k; ++j)  x[j] = j;
        ++ct;
        visit();
        return;
    }

    if ( z )  // forward:
    {
        if ( k>0 )  { x[k] = n;  comb_gray_compl(n-1, k-1, z); }
        comb_gray_compl(n-1, k, !z);
    }
    else     // backward:
    {
        comb_gray_compl(n-1, k, !z);
        if ( k>0 )  { x[k] = n;  comb_gray_compl(n-1, k-1, z); }
    }
}
// -------------------------

int
main(int argc, char **argv)
{
    N = 7;
    NXARG(N, "Length of words");
    K = 3;
    NXARG(K, "Combinations (n choose k)");
    x = new ulong[N+1];

    bool cq = 0;
    NXARG(cq, "Whether to generate complement");

    bool rq = 0;
    NXARG(rq, "Whether to reverse order");
    rq = !rq;

    if ( K>N )  { return 1; }

    ct = 0;
    if ( 0==cq )  comb_gray(N, K, rq);
    else          comb_gray_compl(N, K, rq);

    cout << "ct=" << ct << endl;

    delete [] x;

    return 0;
}
// -------------------------

/*
Timing:
% time ./bin 32 20
arg 1: 32 == n  [Length of words]  default=6
arg 2: 20 == k  [Combinations (n choose k)]  default=3
ct=225792840
./bin 32 20  5.19s user 0.03s system 99% cpu 5.216 total
 ==> 225792840/5.19 == 43,505,364 per second

% time ./bin 32 12
arg 1: 32 == n  [Length of words]  default=6
arg 2: 12 == k  [Combinations (n choose k)]  default=3
ct=225792840
./bin 32 12  6.39s user 0.04s system 99% cpu 6.442 total
 ==> 225792840/6.39 == 35,335,342 per second
*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/combination-gray-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/combination-gray-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

