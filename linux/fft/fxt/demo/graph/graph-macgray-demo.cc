
#include "graph/digraph.h"
#include "graph/digraph-paths.h"
// demo-include "graph/search-digraph-cond.cc"
#include "graph/mk-special-digraphs.h"
// demo-include "graph/mk-gray-digraph.cc"

#include "graph/print-path.h"
//#include "comb/gray.h"
#include "comb/comb-print.h"

#include "bits/bitrotate.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "fxtio.h"
#include "jjassert.h"


//% Paths through a directed graph: modular adjacent changes (MAC) Gray paths.


ulong
pfunc(const digraph_paths &dp)
// Function to be called with each path.
{
    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;

    if ( ! dp.cq_ )   return 0;  // cycles only

    cout << dp.pfct_ << ":";
    cout << endl;
    print_gray(rv, ng);

//    dp.print_turns( 0 );  cout << endl;
//    cout << ".";  cout.flush();

    return 1;
}
// -------------------------


ulong cf_nb;  // number of bits,  set in main()
bool cfunc_mac(digraph_paths &dp, ulong ns)
// Condition: difference of successive delta values (modulo n) == +-1
// paths exist for n<=7, unknown for n>=8
{
    // path initialized, we have ns>=2
    ulong p  = dp.rv_[ns],  p1 = dp.rv_[ns-1], p2 = dp.rv_[ns-2];
    ulong c = p ^ p1,  c1 = p1 ^ p2;
    if ( c & bit_rotate_left(c1, 1, cf_nb) )  return  true;
    if ( c1 & bit_rotate_left(c, 1, cf_nb) )  return  true;
    return false;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "size in bits");
    if ( n<2 )  n = 2;
    cf_nb = n;

    ulong maxnp = 0;
    NXARG(maxnp, " stop after maxnp paths (0: never stop)");

    digraph *dgp  = make_gray_digraph(n, 0);
    digraph &dg = *dgp;
//    dg.print("Graph =");

    digraph_paths dp(dg);


    // Option: set max number of paths:
    if ( maxnp )
    {
        cout << "We will stop after " << maxnp << " paths";
        cout << " that pfunc() counts.";
        cout << endl;
    }

    ulong ns = 0, p = 0;

    // MAC: canonical paths start as 0-->1-->3
    {
        dp.mark(0, ns);
        dp.mark(1, ns);
        p = 3;
    }

    // All the work is done here:

    dp.all_cond_paths(pfunc, cfunc_mac, ns, p, maxnp);

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
/// make-target: "1demo DSRC=demo/graph/graph-macgray-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-macgray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

