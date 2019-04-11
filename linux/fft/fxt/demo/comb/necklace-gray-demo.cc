
// demo-is-self-contained

#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "nextarg.h"


//% Generate binary Lyndon words ordered so that only few changes
//% between successive elements occur (note: in general not a Gray code).
//% Recursive CAT algorithm.


ulong *fo;  // aux: detect extra transitions
ulong sxct;  // count extra transitions

ulong *f;  // data in f[1..N],  f[0] = 0
ulong N;  // word length

ulong ct;  // count objects

//#define TIMING  // uncomment to disable printing

void
visit(ulong j)
{
    if ( N!=j )  return;  // only Lyndon words
//    if ( (N%j)!=0 )  return;  // only necklaces

    ++ct;
#ifndef TIMING
    cout << setw(4) << ct << ":";
    print_vec("  ", f+1, N, true);
//    cout << "   j=" << j;
//    if ( N%j==0 )  cout << "  N";
//    if ( N==j )  cout << "  L";

    if ( ct>1 )
    {
        ulong xct = 0;
        for (ulong i=1; i<=N; ++i)  xct += (fo[i] != f[i]);
        xct -= 1;
        if ( xct!=0 )  cout << "  <<+" << xct;
        sxct += xct;
    }
    for (ulong i=1; i<=N; ++i)  fo[i] = f[i];
    cout << endl;
#endif  // TIMING
}
// -------------------------

void xgen(ulong n, ulong j, int x=+1)
{
    if ( n > N )  visit(j);
    else
    {
        if ( -1==x )
        {
            if ( 0==f[n-j] )  { f[n] = 1;  xgen(n+1, n, -x); }
            f[n] = f[n-j];  xgen(n+1, j, +x);
        }
        else
        {
            f[n] = f[n-j];  xgen(n+1, j, +x);
            if ( 0==f[n-j] )  { f[n] = 1;  xgen(n+1, n, -x); }
        }
    }
}
// -------------------------

int
main(int argc, char **argv)
{
    N = 8;
    NXARG(N, "Length of words (n>=1)");

    fo = new ulong[N+1];
    f = new ulong[N+1];
    for (ulong i=0; i<=N; ++i)  f[i] = 0;
    ct = 0;
    sxct = 0;
    xgen(1, 1);
    cout << "  ct =" << ct << endl;
    cout << "  sxct =" << sxct << endl;

    delete [] fo;
    delete [] f;

    return 0;
}
// -------------------------

/*
Timing: (with Lyndon words)
 time ./bin 32 2
arg 1: 32 == N  [Length of words (n>=1)]  default=8
  ct =134215680
./bin 32 2  3.94s user 0.02s system 99% cpu 3.964 total
 ==> 134215680/3.94 == 34,064,893 per second
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/necklace-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/necklace-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

