
#include "graph/digraph.h"
#include "graph/digraph-paths.h"
// demo-include "graph/search-digraph.cc"
#include "graph/mk-special-digraphs.h"
// demo-include "graph/mk-debruijn-digraph.cc"

#include "bits/parity.h"

#include "nextarg.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"


//% Find all paths through the binary De Bruijn graph.

//#define TIMING  // uncomment to disable printing


void
db_manip(digraph &dg, ulong mq)
{
    ulong n = dg.ng_/2;

    if ( mq >= 100 )
    {
        dg.reverse_edge_order();  // reverse ordering
        mq -= 100;
    }

    switch ( mq )
    {
    case 1:
        // different ordering: more changes in first half
        for (ulong k=0; k<2*n; k+=2)  dg.reverse_edge_order(k);
        break;
    case 2:
        dg.reverse_edge_order(0, n);
        break;
    case 3:
        dg.reverse_edge_order(n, 2*n-1);
        break;
    case 4:
        // different ordering:
        for (ulong k=0; k<n; ++k)  if ( parity(k) )  dg.reverse_edge_order(k);
        break;
    }
}
// -------------------------


ulong pq = 5;  // whether and what to print with each cycle
//
ulong
pfunc_db(const digraph_paths &dp)
// Function to be called with each cycle.
{
    if ( 0==pq )  return 1;  // just count

    cout << setw(4) << dp.pct_ << ":  ";
    switch ( pq )
    {
    case 1:  // print lowest bits (De Bruijn sequence)
        {
            ulong *rv = dp.rv_, ng = dp.ng_;
            for (ulong k=0; k<ng; ++k)  cout << (rv[k]&1UL ? '1' : '.');
            cout << endl;
            break;
        }
    case 2:
        dp.print_path();
        break;

    case 3:
        dp.print_bin_path();
        break;
    case 4:
        cout << endl;  dp.print_bin_horiz_path();
        break;

    default:
        {
            ulong *rv = dp.rv_, ng = dp.ng_;
            for (ulong k=0; k<ng; ++k)  cout << (rv[k]&1UL ? '1' : '.');
            cout << "    ";
            dp.print_path();
            jjassert( dp.path_is_cycle() );
        }
    }

    return 1;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "size of graph == 2*n");
    NXARG(pq, "what to print with each path:\n"
          "  0==> nothing (just count)\n"
          "  1==> lowest bits (De Bruijn sequence)\n"
          "  2==> path\n"
          "  3==> path binary\n"
          "  4==> path binary, horiz. layout\n"
          "  5==> De Bruijn sequence and path \n");
#ifdef TIMING
    pq = 0;  // no printing with paths
#endif

    ulong maxnp = 0;
    NXARG(maxnp, "stop after maxnp paths (0: never stop)");
    ulong p0 = 0;
    NXARG(p0, "start position <2*n");
    ulong mq = 0;
    NXARG(mq, "special: manipulate graph");

    digraph * dgp = make_debruijn_digraph(n);
    digraph &dg = *dgp;

    digraph_paths dp(dg);

    if ( mq )  db_manip(dg, mq);

    dg.print_horiz("Graph =");


    if ( pq )  cout << "Path(s):" << endl;
    // call pfunc() with each cycle:
    dp.all_paths(pfunc_db, 0, p0, maxnp);

    cout << "n = " << n;
    cout << " (ng=" << dg.ng_ << ")";
//    cout << "   #paths = " << dp.pct_;  // == number of cycles
    cout << "   #cycles = " << dp.cct_;
    cout << endl;

    delete dgp;

    return 0;
}
// -------------------------

/*
Timing:
% time ./bin 28 0
arg 1: 28 == n  [size of graph == 2*n]  default=8
arg 2: 0 == pq  [what to do in pfunc()]  default=1
arg 3: 0 == maxnp  [stop after maxnp paths (0: never stop)]  default=0
arg 4: 0 == p0  [start position <2*n]  default=0
arg 5: 0 == mq  [special: manipulate graph]  default=0
n = 28 (ng=56)   #cycles = 3670016
./bin 28 0  8.02s user 0.04s system 99% cpu 8.066 total
 ==> 3670016/8.066 == 454,998 per second

 % time ./bin 32 0
n = 32 (ng=64)   #cycles = 67108864
./bin 32 0  138.32s user 0.67s system 99% cpu 2:19.00 total
 ==> 67108864/139.0 == 482,797 per second
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/graph-debruijn-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-debruijn-demo.cc DEMOFLAGS=-DTIMING"
/// End:

