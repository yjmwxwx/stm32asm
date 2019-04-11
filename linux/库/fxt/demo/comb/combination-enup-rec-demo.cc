
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"

#include "comb/comb-print.h"


//% Recursive generation of enup order for combinations (strong minimal-change order).

//#define TIMING  // define to disable printing


ulong N;    // number of bits in words
ulong K;    // number of ones in words
ulong *rv;  // elements in combination at rv[1] ... rv[k]

ulong ct;   // count objects


void visit()
{
#ifndef TIMING
    cout << setw(4) << ct << ":";
    print_set("  ", rv+1, K, 1);
    print_set1_as_deltaset("  ", rv+1, K, N);
    cout << endl;
#endif
}
// -------------------------


void
comb_enup(ulong n, ulong k, bool z)
{
    if ( k==n )
    {
        for (ulong j=1; j<=k; ++j)  rv[j] = j;
        ++ct;
        visit();
        return;
    }

    if ( z )  // forward:
    {
        if ( (n>=2) && (k>=2) )  { rv[k] = n;  rv[k-1] = n-1;  comb_enup(n-2, k-2, z); }  // 11
        if ( (n>=2) && (k>=1) )  { rv[k] = n;  comb_enup(n-2, k-1, z); }                  // 10
        if ( (n>=1) )            { comb_enup(n-1, k, !z); }                               // 0
    }
    else     // backward:
    {
        if ( (n>=1) )            { comb_enup(n-1, k, !z); }                               // 0
        if ( (n>=2) && (k>=1) )  { rv[k] = n;  comb_enup(n-2, k-1, z); }                  // 10
        if ( (n>=2) && (k>=2) )  { rv[k] = n;  rv[k-1] = n-1;  comb_enup(n-2, k-2, z); }  // 11
    }
}
// -------------------------

void
comb_enup_compl(ulong n, ulong k, bool z)
{
    if ( (k==0) || (k==n) )
    {
        for (ulong j=1; j<=k; ++j)  rv[j] = j;
        ++ct;
        visit();
        return;
    }

    if ( z )  // forward:
    {
        if ( (n>=1) && (k>=1) )  { rv[k] = n;  comb_enup_compl(n-1, k-1, !z); }   // 1
        if ( (n>=2) && (k>=1) )  { rv[k] = n-1;  comb_enup_compl(n-2, k-1, z); }  // 01
        if ( (n>=2) )            { comb_enup_compl(n-2, k-0, z); }                // 00
    }
    else     // backward:
    {
        if ( (n>=2) )            { comb_enup_compl(n-2, k-0, z); }                // 00
        if ( (n>=2) && (k>=1) )  { rv[k] = n-1;  comb_enup_compl(n-2, k-1, z); }  // 01
        if ( (n>=1) && (k>=1) )  { rv[k] = n;  comb_enup_compl(n-1, k-1, !z); }   // 1
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
    rv = new ulong[K+1];

    bool cq = 0;
    NXARG(cq, "Whether to generate complement");

    bool rq = 0;
    NXARG(rq, "Whether to reverse order");
    rq = !rq;

    jjassert( K <= N );


    ct = 0;
    if ( 0==cq )  comb_enup(N, K, rq);
    else          comb_enup_compl(N, K, rq);

    cout << "ct=" << ct << endl;

    delete [] rv;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 32 20
arg 1: 32 == N  [Length of words]  default=7
arg 2: 20 == K  [Combinations (n choose k)]  default=3
arg 3: 0 == rq  [Whether to reverse order]  default=0
ct=225792840
./bin 32 20  4.80s user 0.03s system 99% cpu 4.827 total
 ==> 225792840/4.80 == 47,040,175 per second

 time ./bin 32 12
arg 1: 32 == N  [Length of words]  default=7
arg 2: 12 == K  [Combinations (n choose k)]  default=3
arg 3: 0 == rq  [Whether to reverse order]  default=0
ct=225792840
./bin 32 12  6.05s user 0.02s system 99% cpu 6.086 total
 ==> 225792840/6.05 == 37,321,130 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/combination-enup-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/combination-enup-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

