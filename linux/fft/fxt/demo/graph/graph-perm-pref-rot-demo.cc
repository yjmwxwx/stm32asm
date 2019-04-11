
#include "graph/digraph.h"
#include "graph/digraph-paths.h"
// demo-include "graph/search-digraph.cc"
#include "graph/mk-special-digraphs.h"
// demo-include "graph/mk-perm-pref-rot-digraph.cc"

#include "comb/num2perm.h"  // perm2num(), num2perm()
#include "comb/comb-print.h"

#include "nextarg.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"


//% Permutations by prefix rotations.


ulong n;

static inline ulong difflen(const ulong *p, const ulong *p2)
{
    ulong j;
    for (j=0; j<n; ++j)  if ( p2[j] == p[j] )  break;
    return j;
}
// -------------------------


ulong
pfunc_perm(const digraph_paths &dp)
// Function to be called with each path.
{
//    return 1;  // just count

    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;

//    cout << setw(4) << dp.pfct_ << ":  ";
//    for (ulong k=0; k<ng; ++k)  cout << " " << rv[k];

    ulong p[32];
    ulong p2[32];

#if 0  // condition: no two successive shifts of same length
    ulong dl, dl2 = 0;
    for (ulong k=0; k<ng; ++k)
    {
        num2perm_ffact(rv[k], p, n);
        dl = difflen(p, p2);
        if ( k!= 0 )
        {
            if ( dl2==dl )  return 0;
            dl2 = dl;
        }
        for (ulong j=0; j<n; ++j) p2[j] = p[j];
    }
#endif

#if 1
    cout << dp.pfct_ << ":" << endl;
    for (ulong k=0; k<ng; ++k)
    {
        cout << setw(4) << k << ": ";
        cout << setw(4) << rv[k] << ": ";
        num2perm_ffact(rv[k], p, n);
        print_perm(" ", p, n);
        if ( k!=0 )  cout << "  " << difflen(p, p2);
        for (ulong j=0; j<n; ++j) p2[j] = p[j];

        cout << endl;
    }
#else
    for (ulong k=0; k<ng; ++k)
    {
        num2perm_ffact(rv[k], p, n);
        if ( k!=0 )  cout << ", " << difflen(p, p2);
        for (ulong j=0; j<n; ++j) p2[j] = p[j];
    }
#endif

    cout << endl;

    return 1;
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 4;
    NXARG(n, "Permutations of n elements");
    if ( n<1 )  n = 1;
    bool rq = 1;
    NXARG(rq, "Whether right rotations");

    digraph * dgp = make_perm_pref_rot_digraph(n, rq);
    digraph &dg = *dgp;

    digraph_paths dp(dg);

    ulong maxnp = 1;
    NXARG(maxnp, "stop after maxnp paths (0: never stop)");

//    dg.print("Graph =");
    cout << endl;


    // All the work is done here:
    // (pfunc_perm() is called with each path)
    dp.all_paths(pfunc_perm, 0, 0, maxnp);

    cout << "n = " << n;
    cout << "   #pfct = " << dp.pfct_;
    cout << endl;
    cout << "   #paths = " << dp.pct_;
    cout << "   #cycles = " << dp.cct_;
    cout << endl;

    delete dgp;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/graph-perm-pref-rot-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-perm-pref-rot-demo.cc DEMOFLAGS=-DTIMING"
/// End:


