
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"

//#include "comb/composition-nz-rank.h"
//#include "comb/comb-print.h"
//#include "bits/print-bin.h"


//% Run length limited (RLL) words (at most 2 identical consecutive bits),
//% recursive CAT algorithm.

// Cf. bits/bit-rll2-demo.cc

//#define TIMING  // define to disable printing


ulong n;    // number of bits in words
ulong *rv;  // bits of the word

ulong ct;   // count objects
ulong rct;  // count recursions (==work)

//ulong Z[64];

void visit()
{
#ifndef TIMING
    cout << setw(4) << ct << ":";
    cout << "   ";
    cout << " .";  // assume highest bit in RLL word is zero
    for (ulong j=0; j<n; ++j)  cout << " " << (rv[j] ? '1' : '.');

    cout << "   ";
    cout << " " << (!rv[0] ? '1' : '.');  // assume highest bit in RLL word is zero
    for (ulong j=1; j<n; ++j)  cout << " " << (rv[j]==rv[j-1] ? '1' : '.');

//    ulong w = 0,  b = 1UL << n, j = 1;
//    b >>= 1;  if ( ! rv[0] )  w |= b;
//    while ( b>>=1 )  { if (rv[j]==rv[j-1]) w|=b;  ++j;  }
//    print_bin("    ", w, n+1);
//    w = ~w;
//    ulong nc = composition_nz_unrank(w, Z, n+1);
//    print_vec("  ", Z, nc);

    cout << endl;
#endif
}
// -------------------------


void rll_rec(ulong d, bool z)
// RLL(2) words in lexicographic order
// (corresponding to Fibonacci words in minimal-change order).
{
    if ( d>=n )
    {
        ++ct;  // count objects
        visit();
    }
    else
    {
        ++rct;  // measure computational work
#if 1
        if ( z==0 )
        {
            rv[d]=0;  rv[d+1]=1;  rll_rec(d+2, 1);
            rv[d]=1;  rll_rec(d+1, 1);
        }
        else  // z==1
        {
            rv[d]=0;  rll_rec(d+1, 0);
            rv[d]=1;  rv[d+1]=0;  rll_rec(d+2, 0);
        }
#else
        // compact version:
        rv[d]=0;  rv[d+1]=1;  rll_rec(d+2-z, !z);
        rv[d]=1;  rv[d+1]=0;  rll_rec(d+1+z, !z);
#endif
    }
}
// -------------------------


void rll_rec2(ulong d, bool z)
// RLL(2) words in order with fewer changes than with lexicographic order
// (corresponding to Fibonacci words in lexicographic order).
{
    if ( d>=n )
    {
        ++ct;  // count objects
        visit();
    }
    else
    {
        ++rct;  // measure computational work
#if 1
        if ( z==0 )
        {
            rv[d]=0;  rv[d+1]=1;  rll_rec2(d+2, 1);
            rv[d]=1;  rll_rec2(d+1, 1);
        }
        else  // z==1
        {
            rv[d]=1;  rv[d+1]=0;  rll_rec2(d+2, 0);
            rv[d]=0;  rll_rec2(d+1, 0);
        }
#else
        // compact version:
        ulong x = 1 - z;
        rv[d]=z;  rv[d+1]=x;  rll_rec2(d+2, x);
        rv[d]=x;  rll_rec2(d+1, x);
#endif
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 7;
    NXARG(n, "Length of RLL words == n+1");
    rv = new ulong[n+1];  // incl. sentinel rv[n]
    bool gq = true;
    NXARG(gq, "Whether Fibonacci words shall appear in minimal-change order");

    ct = 0;
    rct = 0;

    if ( gq )  rll_rec(0, 0);
    else       rll_rec2(0, 0);

    cout << "ct=" << ct << endl;
    cout << "rct=" << rct << endl;  // rct == ct-1
    cout << "work/object=" << (double)rct/(double)ct << endl;  // ratio <= 1

    delete [] rv;

    return 0;
}
// -------------------------

/*
Timing:

% time ./bin 41
arg 1: 41 == n  [Length of RLL words == n+1]  default=7
ct=433494437
rct=433494436
work/object=1
./bin 41  4.38s user 0.00s system 100% cpu 4.380 total
 ==> 433494437/4.38 == 98,971,332 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 41
arg 1: 41 == n  [Length of RLL words == n+1]  default=7
arg 2: 1 == gq  [whether Fibonacci words in minimal-change order]  default=1
ct=433494437
rct=433494436
work/object=1
./bin 41  2.54s user 0.00s system 99% cpu 2.537 total
 ==> 433494437/2.54 == 170,667,101 per second

./bin 41  3.09s user 0.00s system 99% cpu 3.094 total  // compact version

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/rll-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/rll-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

