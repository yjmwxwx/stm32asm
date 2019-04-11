
// demo-is-self-contained

#include "comb/composition-nz-rank.h"

#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts.
//% Gray code with moves of only one unit, all moves are one-close or
//% two-close, two-close moves always cross a part =1 and all moves are
//% at the end, involving the last element.
//% Recursive algorithm.


// Cf. comb/composition-nz-gray-demo.cc iterative version.
// Cf. comb/composition-nz-demo.cc for compositions in lexicographic order.
// Cf. comb/composition-nz-rl-demo.cc for compositions in run-length order
// Cf. comb/composition-nz-subset-lex-demo.cc for compositions in subset-lex order


//#define TIMING  // uncomment to disable printing

ulong N;
ulong *a;  // composition

void visit(ulong m)
{
//    for (ulong j=1; j<m; ++j)
//        if ( a[j-1] < a[j] )  return;  // partitions
//    for (ulong j=1; j<m; ++j)
//        if ( a[j-1] == a[j] )  return;  // distinct parts

    static ulong ct = 0;
    cout << setw(4) << ct << ":";
    print_vec("  ", a, m);
    cout << endl;

    ulong s = 0;
    for (ulong j=0; j<m; ++j)  s += a[j];
    jjassert( s == N );

#if 0 // check rank (only with forward order)
    const ulong r = composition_nz_gray_rank( a, m, N );
//    print_bin("  ", r, (N>1 ? N-1 : 1) );
    jjassert( r == ct );
#endif
    ++ct;
}
// -------------------------


void F(ulong n, ulong m);
void B(ulong n, ulong m);

void F(ulong n, ulong m=0)
{
    if ( n==0 )
    {
#ifndef TIMING
        visit(m);
#endif
        return;
    }

    for (ulong f=n; f!=0; --f)  // first part decreasing
    {
        a[m] = f;
        if ( 0 == (f & 1) )  F(n-f, m+1);
        else                 B(n-f, m+1);
    }
}
// -------------------------


void B(ulong n, ulong m=0)
{
    if ( n==0 )
    {
#ifndef TIMING
        visit(m);
#endif
        return;
    }

    for (ulong f=1; f<=n; ++f)  // first part increasing
    {
        a[m] = f;
        if ( 0 == (f & 1) )  B(n-f, m+1);
        else                 F(n-f, m+1);
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "compositions of n");
    N = n;
    bool bq = 0;
    NXARG(bq, "whether to generate backward order");

    a = new ulong[n];

    if ( bq )
    {
        cout << "backward:" << endl;
        B(n);
    }
    else
    {
        cout << "forward:" << endl;
        F(n);
    }

#ifdef TIMING
    cout << " ct=" << ( n ? 1UL<<(n-1) : 1 ) << endl;
#endif

    delete [] a;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.0:

 time ./bin 30 0
arg 1: 30 == n  [compositions of n]  default=7
arg 2: 0 == bq  [whether to generate backward order]  default=0
forward:
 ct=536870912
./bin 30 0  4.50s user 0.00s system 99% cpu 4.504 total
 ==> 536870912/4.50 == 119,304,647 per second

 time ./bin 30 1
arg 1: 30 == n  [compositions of n]  default=7
arg 2: 1 == bq  [whether to generate backward order]  default=0
backward:
 ct=536870912
./bin 30 1  3.79s user 0.00s system 99% cpu 3.791 total
 ==> 536870912/3.79 == 141,654,594 per second

*/

/*
BENCHARGS=30 0
BENCHARGS=30 1
*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-gray-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-gray-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

