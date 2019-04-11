
#include "bits/fibrep.h"  // fibrep2bin()
#include "aux0/fibonacci.h"  // fibonacci()
#include "graph/digraph.h"
#include "graph/digraph-paths.h"
// demo-include "graph/search-digraph-cond.cc"
#include "graph/mk-special-digraphs.h"
// demo-include "graph/mk-fibrep-gray-digraph.cc"

#include "bits/print-bin.h"  // print_bin()
#include "bits/bitlow.h"  // lowest_one_idx()
//#include "comb/comb-print.h"  // print_gray()

#include "bits-all.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray codes through Fibonacci representations.

uint64 gct;
bool cfunc_max(digraph_paths &dp, ulong /*ns*/)
{
    if ( 0 == --gct )  dp.pfdone_ = true;
    return true;
}
// -------------------------

ulong pn;
bool jcyc;
ulong
pfunc_fibrepgray(const digraph_paths &dp)
// Function to be called with each path.
{
    // ----- conditions:
    if ( jcyc && (!dp.cq_) )  return 0;  // only cycles

    // ----- actions:
//    dp.pfdone_ = true;

    cout << "Path #" << dp.pfct_ << ":" << endl;
    const ulong *vn = dp.g_.vn_;
    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;
    for (ulong k=0; k<ng; ++k)
    {
        cout << setw(2) << k << ": ";
        ulong fk = vn[rv[k]];
//        cout << setw(8) << fk;
        print_bin("  ", fk, pn);
        cout << " == " << setw(4) << fibrep2bin(fk);
        if ( k>0 )
        {
            ulong df = fk^vn[rv[k-1]];
            print_bin("   ^= ", df, pn);
            cout << " == " << setw(4) << fibonacci(2+lowest_one_idx(df));
        }
        cout << endl;
    }
//    dp.print_turns( 0 );
//    cout << endl;


    return 1;
}
// -------------------------


static int my_cmp(const ulong &a, const ulong &b)
// Playground.
{
//#define CODE(x) (x)
//#define CODE(x) gray_code(x)
#define CODE(x) inverse_gray_code(x)
//#define CODE(x) blue_code(x)
//#define CODE(x) bit_sequency(x)
    ulong ta = CODE(a),  tb = CODE(b);
    if ( ta==tb )  return 0;
//    return  ( ta<tb ? +1 : -1);
    return  ( ta>tb ? +1 : -1);
#undef CODE
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 34;
    NXARG(n, "Number of nodes (a Fibonacci number)");
    pn = 1;  while ( fibonacci(pn)<n )  ++pn;  // global, used in pfunc_fibrepgray()

    jcyc = true;
    NXARG(jcyc, "Whether only cycles are output");

    ulong maxnp = 1;
    NXARG(maxnp, "stop after maxnp paths (0: never stop)");

    ulong maxt = 0;
    NXARG(maxt, "stop after maxt*(2^20) steps (0: never stop)");
    gct = ((uint64)maxt) << 20;

    digraph * dgp = make_fibrepgray_digraph(n);
    digraph &dg = *dgp;

    cout << "Graph has "
         << dg.num_nodes() << " nodes, "
         << dg.num_edges() << " edges."
         << endl;

    dg.sort_edges(my_cmp);
//    dg.print();

    digraph_paths dp(dg);
    ulong first = 0;
    ulong npt = dp.all_cond_paths(pfunc_fibrepgray, cfunc_max, 0, first, maxnp );
    cout << " % n=" << n << "  npt=" << npt << endl;

    delete dgp;

    return 0;
}
// -------------------------

// With at most 100*2^20 calls to pfunc a path is found for
// the following n<=135:
//  1 2 8 11 13 15 21 23 29 31 32 34 37 39 41 42 43 44 48
// cycles are found for 2, 8, 32, 34, 42, 44, 48

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/graph-fibrepgray-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-fibrepgray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

