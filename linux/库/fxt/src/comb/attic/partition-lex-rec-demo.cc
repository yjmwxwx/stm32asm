
// demo-is-self-contained

#include "fxttypes.h"

#include "jjassert.h"
#include "nextarg.h"  // NXARG()

#include "fxtio.h"

//% Integer partitions in lexicographic order, recursive algorithm.

//#define TIMING  // uncomment to disable printing




ulong *a;
ulong ct = 0;

void visit(ulong off)
{
    cout << setw(4) << ++ct << ":  ";
    for (ulong k=0; k<off;  ++k)
    {
        cout << a[k];
        if ( k+1<off )  cout << "+";
    }
//    cout << "  [" << off << "]";  // number of parts
    cout << endl;
}
// -------------------------


void part_lex_rec(ulong n, ulong mp, ulong off=0)
// Partition n into parts m >= np.
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

    for (ulong m=mp; m<=n; ++m)
    {
        a[off] = m;
        part_lex_rec(n-m, m, off+1);
    }
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 9;
    NXARG(n, "Partitions of n");
    a = new ulong[n];

    ulong mp = 1;
    NXARG(mp, "Minimal part at least mp,  1 <= mp <= n");
    if ( mp<1 )  mp = 1;
    if ( mp>n )  mp = n;

    part_lex_rec(n, mp);

    cout << " " << n << ":  ct=" << ct << endl;
    cout << endl;

    delete [] a;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

% time ./bin 100
arg 1: 100 == n  [Partitions of n]  default=6
arg 2: 1 == mp  [Minimal part at least mp,  1 <= mp <= n]  default=1
 100:  ct=190569292
./bin 100  7.10s user 0.00s system 99% cpu 7.135 total
 ==> 190569292/7.10 == 26,840,745 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-lex-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-lex-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:
