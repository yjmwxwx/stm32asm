
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


//% Find all paths through the m-ary De Bruijn graph.

//#define TIMING  // uncomment to disable printing


ulong m = 0;  // m-ary De Bruijn graph
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
    case 1:  // print De Bruijn sequence
        {
            ulong *rv = dp.rv_, ng = dp.ng_;
            for (ulong k=0; k<ng; ++k)  cout << rv[k]%m;
            cout << endl;
            break;
        }
    case 2:  // print path
        dp.print_path();
        break;

    default:  // print both DBS and path
        {
            ulong *rv = dp.rv_, ng = dp.ng_;
            for (ulong k=0; k<ng; ++k)  cout << rv[k] % m;
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
    m = 3;
    NXARG(m, "m-ary De Bruijn graph");

    ulong n = 3;
    NXARG(n, "size of graph == m*n");
    NXARG(pq, "what to print with each path:\n"
          "  0==> nothing (just count)\n"
          "  1==> lowest bits (De Bruijn sequence)\n"
          "  2==> path\n"
          "  3==> De Bruijn sequence and path \n");
#ifdef TIMING
    pq = 0;  // no printing with paths
#endif

    ulong maxnp = 0;
    NXARG(maxnp, "stop after maxnp paths (0: never stop)");
    ulong p0 = 0;
    NXARG(p0, "start position <m*n");

    digraph * dgp = make_debruijn_digraph(n, m);
    digraph &dg = *dgp;

    digraph_paths dp(dg);


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
Timing: (AMD Phenom II X4 945 3000MHz)

% time ./bin 2 28 0
./bin 2 28 0  4.74s user 0.00s system 99% cpu 4.741 total
n = 28 (ng=56)   #cycles = 3670016
 ==> 3670016/4.74 == 774,264 per second

% time ./bin 3 11 0
n = 11 (ng=33)   #cycles = 10903552
./bin 3 11 0  6.00s user 0.00s system 99% cpu 6.004 total
 ==> 10903552/6.00 == 1,817,258 per second

*/

/*
Number of cycles through 3-ary graph:
[2, 4, 24, 64, 512, 1728, 13312, 32768, 373248, 1310720, 10903552]
[1, 1, 3, 4, 16, 27, 104, 128, 729, 1280, 5324]  // == v[n]/2^n
[2, 2, 6, 8, 32, 54, 208, 256, 1458, 2560, 10648] // == v[n]/2^(n-1) == OEIS A094678

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/graph-debruijn-m-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-debruijn-m-demo.cc DEMOFLAGS=-DTIMING"
/// End:

