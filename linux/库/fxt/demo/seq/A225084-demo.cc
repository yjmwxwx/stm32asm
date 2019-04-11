
#include "comb/composition-nz.h"


#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% OEIS sequence A225084:
//% number of compositions of n with maximal up-step k.
//% OEIS sequence A225085:
//% number of compositions of n with maximal up-step <= k.
//% Cf. A003116 (max up-step 1) and A224959 (max up-step 2).


// Cf. comb/composition-nz-demo.cc for (all) compositions
// Cf. comb/composition-nz-upstep-demo.cc for compositions of n with maximal up-step k


//#define TIMING  // uncomment to disable printing

inline ulong max_upstep(const ulong *a, ulong m)
{
    ulong s = 0;
    for (ulong j=1; j<m; ++j)
    {
        if ( a[j] > a[j-1] )
        {
            ulong d = a[j] - a[j-1];
            if ( d > s )  s = d;
        }
    }
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
    NXARG(cq, "whether to print cumulative values (A225085)");

    ulong ct = 0;

    ulong st[64];
    for (ulong j=0; j<n; ++j)  st[j] = 0;  // stats

    ulong m = P.num_parts();
    do
    {
        ++ct;
        const ulong s = max_upstep(P.data(), P.num_parts());
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
        for (ulong j=0, t=0; j<n; ++j)
        { t+=st[j]; cout << t << ", "; ct-=st[j]; }
    }
    else
    {
        for (ulong j=0; j<n; ++j)
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
/// make-target: "1demo DSRC=demo/seq/A225084-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A225084-demo.cc DEMOFLAGS=-DTIMING"
/// End:
