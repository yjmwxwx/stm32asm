
// demo-is-self-contained

#include <cmath>

#include "fxttypes.h"

#include "jjassert.h"
#include "nextarg.h"  // NXARG()

#include "fxtio.h"

//% Integer partitions into distinct parts in lexicographic order, recursive algorithm.
//% Cf. OEIS sequence A000009.

//#define TIMING  // uncomment to disable printing


ulong *a;
ulong ct = 0;

void visit(ulong off)
{
    cout << setw(4) << ++ct << ":  ";
    for (ulong k=0; k<off;  ++k)
    {
        cout << a[k];
        if ( k+1<off )  cout << " + ";
    }
//    cout << "  [" << off << "]";  // number of parts
    cout << endl;
}
// -------------------------


void part_dist_lex_rec(ulong n, ulong mp, ulong off=0)
{
    if ( n==0 )
    {
#ifndef TIMING
        visit(off);
#else
        ++ct;
#endif
        return;
    }

    const ulong d = 1;  // min distance between parts and minimal part
    // d==1:  A000009
    // d==2:  A003106
    // d==3:  A179046
    // d==4:  N/A
    for (ulong m=mp+d; m<=n; ++m)
    {
        a[off] = m;
        part_dist_lex_rec(n-m, m, off+1);
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 19;
    NXARG(n, "Partitions of n");
    const ulong na = (ulong)floor( (sqrt(1+8*(double)n) - 1)/2 );  // max number of parts, see A003056
    a = new ulong[na];
//    cout << " na=" << na << endl;

    ulong mp = 0;
    NXARG(mp, "Minimal part > mp,  0 <= mp < n");
//    if ( mp<1 )  mp = 1;
    if ( mp>=n )  mp = n;

    part_dist_lex_rec(n, mp);

    cout << " " << n << ":  ct=" << ct << endl;
    cout << endl;

    delete [] a;

    return 0;
}
// -------------------------

/*
Timing:  (AMD Phenom II X4 945 3000MHz)

 time ./bin 180
arg 1: 180 == n  [Partitions of n]  default=9
arg 2: 0 == mp  [Minimal part > mp,  0 <= mp < n]  default=0
 180:  ct=141231780

./bin 180  8.79s user 0.00s system 99% cpu 8.795 total
 ==> 141231780/8.79 == 16,067,324 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-dist-lex-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-dist-lex-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:
