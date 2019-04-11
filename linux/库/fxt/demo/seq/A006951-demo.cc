
#include "comb/partition-desc.h"
#include "aux0/ipow.h"

#include "comb/comb-print.h"

#include "fxtio.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A006951:
//% Number of conjugacy classes in GL(n,2).
//% Computed by a summation over integer partitions of n.
//% Also OEIS sequences "Number of conjugacy classes in GL(n,q)":
//%   q=3: A006952, q=4: A049314, q=5: A049315, q=7: A049316, q=8: A182603,
//%   q=9: A182604, q=11: A182605, q=13: A182606, q=16: A182607, q=17: A182608,
//%   q=19: A182609, q=23: A182610, q=25: A182611, q=27: A182612.
//% Non prime powers:
//%   q=6: A221578, q=10: A221579, q=12: A221580, q=14: A221581,
//%   q=15: A221582, q=18: A221583, q=20: A221584.

// Cf. comb/partition-desc-demo.cc for partitions as weakly descending lists

//#define TIMING  // uncomment to disable printing

ulong
visit(const ulong *x, ulong m, ulong q)
{
    if ( m==0 )  return 1;

    ulong st = 1;
    ulong v = x[0];
    ulong mm = 0;
    for (ulong j=0; j<m; ++j)
    {
        if ( v!=x[j] )
        {
            st *= ipow(q, mm-1) * (q-1);  // conjugacy classes in GL(n,q)
            v = x[j];
            mm = 1;
        }
        else  ++mm;
    }
    st *= ipow(q, mm-1) * (q-1);

    return st;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "n in GL(n,q)");

    ulong q = 2;
    NXARG(q, "q (a prime power) in GL(n,q)");

    partition_desc P(n);

    ulong pct = 0;
    ulong ct = 0;
    ulong m = P.num_parts();
    do
    {
        ++pct;
        ulong z = visit( P.data(), m, q );
        ct += z;

#ifndef TIMING
        cout << setw(4) << pct << ": ";
        cout << "  " << setw(4) << z;
        P.print("  ");
        cout << endl;
#endif  // TIMING
    }
    while ( (m=P.next()) );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
 echo $(for n in $(seq 0 13); do ./bin $n 2; done | grep ct= ) | sed 's/ ct=/, /g;'
 1, 1, 3, 6, 14, 27, 60, 117, 246, 490, 1002, 1998, 4053, 8088
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A006951-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A006951-demo.cc DEMOFLAGS=-DTIMING"
/// End:

