
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


//% Paths through a directed graph: adjacent changes (AC) Gray paths.


ulong
pfunc(const digraph_paths &dp)
// Function to be called with each path.
{
    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;

//    if ( ! dp.cq_ )   return 0;  // cycles only

    cout << dp.pfct_ << ":" << endl;
    print_gray(rv, ng);

//    dp.print_turns( 0 );  cout << endl;
//    cout << ".";  cout.flush();

    return 1;
}
// -------------------------


ulong cf_mt;  // mid track < cf_mt,  set in main()
bool cfunc_ac(digraph_paths &dp, ulong ns)
// Condition: difference of successive delta values == +-1
// paths exist for n<=6 but no path for n==7.
{
//    if ( ns<2 )  return  true;
    if ( ns<2 )  return  (dp.rv_[1] < cf_mt);  // avoid track-reflected solutions
    ulong p  = dp.rv_[ns],  p1 = dp.rv_[ns-1], p2 = dp.rv_[ns-2];
    ulong c = p ^ p1, c1 = p1 ^ p2;
    if ( c & (c1<<1) )  return  true;
    if ( c1 & (c<<1) )  return  true;
    return false;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "size in bits");
    if ( n<2 )  n = 2;
    cf_mt = (1UL << ((n+1)/2));

    ulong maxnp = 0;
    NXARG(maxnp, " stop after maxnp paths (0: never stop)");

    digraph * dgp = make_gray_digraph(n, 0);
    digraph & dg = *dgp;
//    dg.print("Graph =");

    digraph_paths dp(dg);


    // Option: set max number of paths:
    if ( maxnp )
    {
        cout << "We will stop after " << maxnp << " paths";
        cout << " that pfunc() counts.";
        cout << endl;
    }

    // All the work is done here:
    ulong ns = 0, p = 0;
    dp.all_cond_paths(pfunc, cfunc_ac, ns, p, maxnp);

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

/*
Timing:

% time ./bin 7
arg 1: 7 == n  [size in bits]  default=5
arg 2: 0 == maxnp  [ stop after maxnp paths (0: never stop)]  default=0
n = 7   #pfct = 0
   #paths = 0   #cycles = 0
./bin 7  20.85s user 0.03s system 99% cpu 20.888 total
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

% time ./bin 7
arg 1: 7 == n  [size in bits]  default=5
arg 2: 0 == maxnp  [ stop after maxnp paths (0: never stop)]  default=0
n = 7   #pfct = 0
   #paths = 0   #cycles = 0
./bin 7  12.27s user 0.00s system 99% cpu 12.270 total
*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/graph-acgray-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-acgray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

