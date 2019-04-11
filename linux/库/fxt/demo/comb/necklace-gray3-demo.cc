
// demo-is-self-contained

#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

//% Generate Gray code (max 3 changes per update) for necklaces

// Method (with correction) from:
// Mark Weston, Vincent Vajnovszki:
// "Gray codes for necklaces and Lyndon words of arbitrary base",
// Proceedings of GASCOM'06, Dijon, France, 11-14. September, pp.55-62., 30-May-2006.


long *fo;  // aux: detect extra transitions
ulong sxct;  // count extra transitions

long *f;  // data in f[1..m],  f[0] = 0
long N;  // word length
long ct;
long k;  // k-ary necklaces, k==sigma in the paper

//#define TIMING  // uncomment to disable printing


void visit(long j)
{
    if ( N!=j )  return;  // only Lyndon words
//    if ( (N%j)!=0 )  return;  // only necklaces

    ++ct;
#ifndef TIMING
    cout << setw(4) << ct << ":";
    print_vec("  ", (const ulong *)f+1, (ulong)N, true);
//    cout << "   j=" << j;
//    if ( N%j==0 )  cout << "  N";
//    if ( N==j )  cout << "  L";

    if ( ct>1 )
    {
        ulong xct = 0;
        for (long i=1; i<=N; ++i)  xct += (fo[i] != f[i]);
        xct -= 1;
        if ( xct!=0 )  cout << "  <<+" << xct;
        sxct += xct;
    }
    for (long i=1; i<=N; ++i)  fo[i] = f[i];
    cout << endl;
#endif  // TIMING
}
// -------------------------

void gen3(long z, long t, long j)
{
    if ( t > N ) { visit(j); }
    else
    {
        if ( (z&1)==0 )  // z (number of elements ==(k-1)) is even?
        {
            // GCC 4.9.1 with -Wstrict-overflow=5 issues the warning
            // "assuming signed overflow does not occur when ..."
            // This is a false positive.
            for (long i=f[t-j]; i<=k-1; ++i)
            {
                f[t] = i;
                gen3( z+(i!=k-1), t+1, (i!=f[t-j]?t:j) );
            }
        }
        else
        {
            for (long i=k-1; i>=f[t-j]; --i)
            {
                f[t] = i;
                gen3( z+(i!=k-1), t+1, (i!=f[t-j]?t:j) );
            }
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    N = 8;
    NXARG(N, "Length of words (n>=1)");

    k = 2;
    NXARG(k, "Number of different beads (k>=2)");

    fo = new long[N+1];
    f = new long[N+1];
    sxct = 0;
    ct = 0;
    f[0] = 0;
    gen3(0, 1, 1);

    cout << endl;
    cout << " ct=" << ct << endl;
    cout << "  sxct =" << sxct << endl;

    delete [] fo;
    delete [] f;

    return 0;
}
// -------------------------

/*
Timing: (with Lyndon words)
 time ./bin 32 2
 ct=134215680
./bin 32 2  6.95s user 0.04s system 99% cpu 6.994 total
 ==> 134215680/6.95 == 19,311,608 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/necklace-gray3-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/necklace-gray3-demo.cc DEMOFLAGS=-DTIMING"
/// End:
