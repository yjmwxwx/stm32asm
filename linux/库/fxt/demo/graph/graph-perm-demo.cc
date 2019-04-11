
#include "graph/digraph.h"
#include "graph/digraph-paths.h"
// demo-include "graph/search-digraph.cc"
#include "graph/mk-special-digraphs.h"
// demo-include "graph/mk-complete-digraph.cc"

#include "perm/permq.h"

#include "nextarg.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"


//% Paths through the complete graph: Permutations.



ulong
pfunc_perm(const digraph_paths &dp)
// Function to be called with each path:
//  print all but the first node.
{
    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;

//    if ( is_inverse(rv, rv, ng) )  // select self-inverse permutations:
    // # = 1,2,4,10,26,76,232,764,2620,9496,...
    {
        cout << setw(4) << dp.pfct_ << ":  ";
        for (ulong k=1; k<ng; ++k)  cout << " " << rv[k];
        cout << endl;

        return 1;
    }

    return 0;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "number of nodes of graph");
    if ( n<1 )  n = 1;

    digraph * dgp = make_complete_digraph(n);
    digraph &dg = *dgp;

    digraph_paths dp(dg);

    ulong maxnp = 0;
    NXARG(maxnp, "stop after maxnp paths (0: never stop)");

    dg.print("Graph =");
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
/// make-target: "1demo DSRC=demo/graph/graph-perm-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-perm-demo.cc DEMOFLAGS=-DTIMING"
/// End:

