
#include "graph/digraph.h"
#include "graph/digraph-paths.h"
// demo-include "graph/search-digraph.cc"
#include "graph/mk-special-digraphs.h"
// demo-include "graph/mk-debruijn-digraph.cc"


#include "bits/print-bin.h"
#include "bits/parity.h"
#include "bits/graycode.h"

#include "nextarg.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"


//% Complement-shift sequence via paths in a directed graph.

ulong pq;  // whether and what to print with each path
ulong
pfunc(const digraph_paths &dp)
// Function to be called with each path.
{
    switch ( pq )
    {
    case 0:  break;  // just count
    case 1:  // print lowest bits
        {
            ulong *rv = dp.rv_, ng = dp.ng_;
            for (ulong k=0; k<ng; ++k)  cout << (rv[k]&1UL ? '1' : '.');
            cout << endl;
            break;
        }
    case 2:  dp.print_bin_path();
        break;
    case 3:  dp.print_bin_path();
        break;
    case 4:  dp.print_bin_horiz_path();
        break;
    case 5:  // print lowest bits
        {
            ulong *rv = dp.rv_, ng = dp.ng_;
            for (ulong k=0; k<ng; ++k)  cout << (rv[k]&1UL ? '1' : '.');
            cout << endl;
            break;
        }
    default:
        {
            ulong *rv = dp.rv_;
            ulong b = dp.ngbits_;
            for (ulong k=0; k<dp.ng_; ++k)
            {
                ulong t = rv[k];
                print_bin("  ", t, b);
                print_bin("  ", gray_code(t), b);
//                print_bin("  ", inverse_gray_code(t), b);
                cout << endl;
            }

//            dp.print_bin_path();
//            ulong *rv = dp.rv_;
//            for (ulong k=0; k<dp.ng_; ++k)  cout << rv[k] << " ";
//            cout << endl;
////            for (ulong k=0,t=~0UL; k<dp.ng_; ++k)
////            { t^=rv[k];  print_bin(" ",t, dp.ngbits_);  cout << endl; }
//            jjassert( dp.path_is_cycle() );
//            break;
        }
    }

    return 1;
}
// -------------------------


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
        dg.reverse_edge_order(0, n-1);
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


int
main(int argc, char **argv)
{
    ulong n = 32;
    NXARG(n, "size of graph == 2*n");
    pq = 2;
    NXARG(pq, "whether and what to print with each path");
    ulong maxnp = 1;
    NXARG(maxnp, "stop after maxnp paths (0: never stop)");
    ulong mq = 0;
    NXARG(mq, "special: manipulate graph");

    digraph * dgp = make_complement_shift_digraph(n);
    digraph &dg = *dgp;
    digraph_paths dp(dg);

    if ( mq )  db_manip(dg, mq);

//    dg.print_horiz("Graph =");

    // call pfunc() with each path:
    dp.all_paths(pfunc, 0, 0, maxnp);

    cout << "n = " << n;
    cout << " (ng=" << dg.ng_ << ")";
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
/// make-target: "1demo DSRC=demo/graph/graph-complementshift-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-complementshift-demo.cc DEMOFLAGS=-DTIMING"
/// End:

