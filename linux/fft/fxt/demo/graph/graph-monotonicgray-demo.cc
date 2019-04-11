
#include "graph/digraph.h"
#include "graph/digraph-paths.h"
#include "graph/mk-special-digraphs.h"
// demo-include "graph/mk-gray-digraph.cc"
// demo-include "graph/search-digraph.cc"
// demo-include "graph/search-digraph-cond.cc"

#include "comb/test-gray.h"

#include "graph/print-path.h"
#include "comb/comb-print.h"

#include "sort/sortfunc.h"
#include "perm/zip.h"

#include "bits/bitcount.h"
#include "bits/graycode.h"
#include "bits/bitlow.h"
#include "bits/print-bin.h"
#include "bits/bitrotate.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "fxtio.h"
#include "jjassert.h"


//% Paths through a directed graph: all canonical monotonic Gray paths starting with zero.

//#define TIMING  // uncomment to disable printing

ulong
pfunc_monotonic(const digraph_paths &dp)
// Function to be called with each path.
{
    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;
    if ( is_monotonic_gray(rv, ng) )
    {
#ifndef TIMING
        print_gray(rv, ng);
#endif
        return 1;
    }

    return 0;
}
// -------------------------

ulong
pfunc_all(const digraph_paths &dp)
// Function to be called with each path.
{
    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;
    jjassert ( is_monotonic_gray(rv, ng) );  // always true with conditional search
#ifndef TIMING
    print_gray(rv, ng);
#endif
//    ulong shortq = 1;
//    dp.print_turns( shortq );  cout << endl;

//    if ( 0==(dp.pfct_ % (1UL<<10))  ) cout << "."; cout.flush();

    return 1;
}
// -------------------------


ulong *bc_tab;  // table of bit counts: bc_tab[k] == bit_count(k)
ulong *bc_mon;  // table of bit counts as they occur in monotonic Gray paths
// n=4:  0 1 2 1 2 1 2 1 2 3 2 3 2 3 4 3
// n=5:  0 1 2 1 2 1 2 1 2 1 2 3 2 3 2 3 2 3 2 3 2 3 4 3 4 3 4 3 4 3 4 5
bool
cfunc_monotonic(digraph_paths &dp, ulong ns)
{
//    if ( ns<2 )  return true;  // never for canonical paths
    return ( bc_tab[dp.rv_[ns]] == bc_mon[ns] );
}
// -------------------------


int mon_cmp(const ulong &a, const ulong &b)
{
    if ( a==b )  return 0;
    if ( (a^b)&1 )  return ( a&1 ? +1 : -1 );  // even is smaller
    return ( a>b ? +1 : -1 );
}
// -------------------------

void setup_bc_tab(ulong n)
{
    ulong n2 = 1UL << n;
    bc_tab = new ulong[n2];
    for (ulong k=0; k<n2; ++k)  bc_tab[k] = bit_count(k);
    bc_mon = new ulong[n2];

    for (ulong k=0; k<n2; ++k)  bc_mon[k] = bc_tab[k];
    quick_sort(bc_mon, n2, mon_cmp);
    zip(bc_mon, n2);

//    for (ulong k=0; k<n2; ++k)  cout << bc_mon[k] << " ";  cout << endl;
}
// -------------------------


int my_cmp(const ulong &a, const ulong &b)
{
    ulong ca = bit_count(a);
    ulong cb = bit_count(b);
    if ( ca!=cb )  return (ca<cb ? +1 : -1);  // lower bit-count first
    if ( a==b )  return  0;
    return (a>b ? +1 : -1);
//    ulong xa = inverse_gray_code(a),  xb = inverse_gray_code(b);
//    return (xa<xb ? +1 : -1);
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "word length in bits");
    if ( n<2 )  n = 2;

    ulong maxnp = 0;
    NXARG(maxnp, "stop after maxnp paths (0: never stop)");

    ulong canonicalq = 1;
//    NXARG(canonicalq, "Option: canonical paths only");

    ulong condq = 1;
    NXARG(condq, "whether to do conditional search");

    ulong sortq = 0;
    NXARG(sortq, "whether to do edge-sorting");


    digraph * dgp = make_gray_digraph(n, 0);
    digraph &dg = *dgp;
    if ( sortq )  dg.sort_edges(my_cmp);

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
    if ( canonicalq )
    {
        ns = start_monotonic_gray_path(dp, n);
        p = dp.rv_[ns-1];
#ifndef TIMING
        cout << "Fixed path at first " << ns << " positions.";
        cout << endl;
        cout << " (last fixed value p=" << p << ").";
        print_bin_path(dp.rv_, ns, n);
        cout << endl;
#endif
        --ns;
    }

    // All the work is done here:
    // (pfunc_monotonic() is called with each path)

    if ( condq )  // use conditional search
    {
        setup_bc_tab(n);
//        for (ulong k=0; k<100; ++k )
        dp.all_cond_paths(pfunc_all, cfunc_monotonic, ns, p, maxnp);
    }
    else  // use usual search
    {
        dp.all_paths(pfunc_monotonic, ns, p, maxnp);
    }

    cout << "n = " << n;
    cout << "   #pfct = " << dp.pfct_;
    cout << endl;
    cout << "   #paths = " << dp.pct_;
//    cout << "   #cycles = " << dp.cct_;  // no cycles
    cout << endl;

    delete [] bc_tab;
    delete [] bc_mon;
    delete dgp;

    return 0;
}
// -------------------------

/*
Edge sorting gives a speedup:

% time ./bin 8 1 1 0 > /dev/null  # without edge sorting
./bin 8 1 1 0 > /dev/null  1.14s user 0.00s system 100% cpu 1.142 total

% time ./bin 8 1 1 1 > /dev/null  # with edge sorting
./bin 8 1 1 1 > /dev/null  0.03s user 0.00s system 98% cpu 0.029 total
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/graph-monotonicgray-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-monotonicgray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

