
// demo-is-self-contained

#include "comb/composition-nz-rank.h"
//#include "comb/endo-enup.h"

#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts, subset-lex order.
//% Recursive algorithm.


//#define TIMING  // uncomment to disable printing

ulong N;
ulong *a;  // composition

void visit(ulong m)
{
//    for (ulong j=1; j<m; ++j)
//        if ( a[j-1] > a[j] )  return;  // partitions
//    for (ulong j=1; j<m; ++j)
//        if ( a[j-1] == a[j] )  return;  // distinct parts
//    for (ulong j=0; j<m; ++j)
//        if ( 0==(a[j] & 1) )  return;  // odd parts

    static ulong ct = 0;
    cout << setw(4) << ct << ":";

//    const ulong r = composition_nz_gray_rank( a, m, N );
    ulong r = composition_nz_rank( a, m );
    r = ~r;  // complement
    print_bin("    ", r, (N>1 ? N-1 : 1) );

//    cout << "  [" << m << "]";

    print_vec("    ", a, m);
    cout << endl;

    ulong s = 0;
    for (ulong j=0; j<m; ++j)  s += a[j];
    jjassert( s == N );


    ++ct;
}
// -------------------------


void F(ulong n, ulong m)
{
    if ( n==0 )
    {
#ifndef TIMING
        visit(m);
#endif
        return;
    }


    a[m] = n;  F(0, m+1);
    for (ulong f=1; f<n; f+=1)
    {
        ulong r = n - f;
        a[m] = f;
        F(r, m+1);
    }
}
// -------------------------




int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "compositions of n");
    N = n;

    a = new ulong[n];

    F(n, 0);

#ifdef TIMING
    cout << " ct=" << ( n ? 1UL<<(n-1) : 1 ) << endl;
#endif

    delete [] a;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-subset-lex-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-subset-lex-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

