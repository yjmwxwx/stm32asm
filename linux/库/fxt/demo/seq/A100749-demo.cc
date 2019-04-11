
#include "comb/composition-nz.h"


#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% OEIS sequence A100749:
//% number of compositions of n having k odd parts.

// Cf. comb/composition-nz-demo.cc for (all) compositions
// Cf. seq/A225084-demo.cc for compositions of n with maximal up-step k


//#define TIMING  // uncomment to disable printing

inline ulong num_odd_parts(const ulong *a, ulong m)
{
    ulong s = 0;
    for (ulong j=0; j<m; ++j)  s += a[j] & 1UL;
    return s;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "compositions of n");
    composition_nz P(n);

    bool cq = 0;
//    NXARG(cq, "whether to print cumulative values");

    ulong ct = 0;

    ulong st[64];
    for (ulong j=0; j<=n; ++j)  st[j] = 0;

    ulong m = P.num_parts();
    do
    {
        ++ct;
        const ulong s = num_odd_parts(P.data(), P.num_parts());
        st[s] += 1;
#ifndef TIMING
        cout << setw(4) << ct << ":";
        cout << " " << setw(2) << s;
        P.print("  ");
        cout << endl;
#endif  // TIMING
//        jjassert( P.OK() );
    }
    while ( (m=P.next()) );

//    cout << " ct=" << ct << endl;

    if ( cq )  // cumulative sums
    {
        for (ulong j=0, t=0; j<=n; ++j)
        { t+=st[j]; cout << t << ", "; ct-=st[j]; }
    }
    else
    {
        for (ulong j=0; j<=n; ++j)
        { cout << st[j] << ", "; ct-=st[j]; }
    }
    cout << endl;

    jjassert( ct==0 );

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A100749-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A100749-demo.cc DEMOFLAGS=-DTIMING"
/// End:

