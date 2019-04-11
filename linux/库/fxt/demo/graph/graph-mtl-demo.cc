
#include "graph/digraph.h"
#include "graph/digraph-paths.h"
// demo-include "graph/search-digraph.cc"

#include "graph/mk-special-digraphs.h"
// demo-include "graph/mk-mtl-digraph.cc"

#include "bits-all.h"  // for sorting functions

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // srand()


//% Cycles through a directed graph: middle two levels.



static ulong pbn;  //  precision for binary print
static bool dq;  //  whther to only print delta seq

#define DELTA(a, b) lowest_one_idx(a^b)
//
ulong
pfunc_mtl(const digraph_paths &dp)
// Function to be called with each path.
{
    ulong ng = dp.ng_;
    const ulong *rv = dp.rv_;
    const ulong *vn = dp.g_.vn_;

    // ----- conditions:
    if ( ! dp.cq_ )  return 0;  // only cycles

    // ----- actions:

    cout << setw(4) << dp.pfct_ << ":";
//    if ( dp.cq_ )  cout << " (cycle)";

    if ( !dq )
    {
        cout << endl;
        for (ulong k=0; k<ng; k+=1)
        {
            ulong x = vn[rv[k]];
            cout << setw(3) << k;
            print_bin(":  ", x, pbn );
            cout << endl;
        }
    }
    else
    {
        cout << " ";
        for (ulong k=1; k<ng; k+=1)  cout << DELTA(vn[rv[k]], vn[rv[k-1]]);
        cout << DELTA(vn[rv[0]], vn[rv[ng-1]]);
    }
    cout << endl;

    return 1;
}
// -------------------------


int cmp_mtl(const ulong &a, const ulong &b)
{
    if ( a==b )  return  0;
#define CODE(x)  inverse_gray_code(x)
    ulong ca = CODE(a), cb = CODE(b);
#undef CODE
    return (ca<cb ? +1 : -1);
}
// -------------------------


static ulong k2;
//
int cmp_exp(const ulong &a, const ulong &b)  // for experiments
{
    if ( a==b )  return  0;
//#define CODE(x)  bit_cyclic_min(x, k2)
//#define CODE(x)  blue_code(x)
//#define CODE(x)  negidx2lexrev(x)
#define CODE(x)  lexrev2negidx(x)
//#define CODE(x)  (x & (a^b))
//#define CODE(x)  lowest_one(x)
//#define CODE(x)  bit_rotate_right(x, 1, k2)
    ulong ca = CODE(a);  ulong cb = CODE(b);
    if ( ca==cb )  return  0;
#undef CODE
//    return (ca>cb ? +1 : -1);
    return (ca<cb ? +1 : -1);
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong k = 3;
    NXARG(k, "Combinations (k choose 2*k-1) and (k-1 choose 2*k-1), (1<=k<=4)");
    k2 = 2*k - 1;
    ulong maxnp = 1;
    NXARG(maxnp, "Stop after maxnp cycles (0: never stop)");
    bool rq = 1;
    NXARG(rq, "Force path to start as 0000111 --> 0001111");
    ulong sortq = 1;
    NXARG(sortq, "Whether to do edge-sorting 0:no, 1:yes  >1:randomize");
    dq = 0;
    NXARG(dq, "Whether to print only delta sequence");

    pbn = 2*k-1;  // precision for binary printing

//    digraph dg = make_mtl_digraph(k, rq);
    digraph * dgp = make_mtl_digraph(k, rq);
    digraph &dg = *dgp;

//    dg.print_horiz("Graph =");

    if ( 1==sortq )  dg.sort_edges(cmp_mtl);
    if ( 1<sortq )
    {
        srand( (uint)sortq );
        dg.randomize_edge_order();
    }

    digraph_paths dp(dg);
    dp.all_paths(pfunc_mtl, 0, 0, maxnp);


    cout << "k = " << k;
    cout << "   #pfct = " << dp.pfct_;
    cout << endl;
    cout << "   #paths = " << dp.pct_;
    cout << "   #cycles = " << dp.cct_;

    cout << endl;


    delete dgp;

    return 0;
}
// -------------------------


// example for k==3:
//
//  0: ...11
//  1: ..111
//  2: ..1.1
//  3: .11.1
//  4: .11..
//  5: 111..
//  6: 1.1..
//  7: 1.1.1
//  8: 1...1
//  9: 1..11
// 10: 1..1.
// 11: 1.11.
// 12: ..11.
// 13: .111.
// 14: .1.1.
// 15: 11.1.
// 16: 11...
// 17: 11..1
// 18: .1..1
// 19: .1.11

// example for k==4:
//  0: ....111
//  1: ...1111
//  2: ...1.11
//  3: ..11.11
//  4: ..1..11
//  5: 1.1..11
//  6: 1.1..1.
//  7: 1.1.11.
//  8: 1...11.
//  9: 11..11.
// 10: .1..11.
// 11: .1..111
// 12: .1...11
// 13: .11..11
// 14: .11..1.
// 15: 111..1.
// 16: 111....
// 17: 1111...
// 18: .111...
// 19: .1111..
// 20: ..111..
// 21: 1.111..
// 22: 1.1.1..
// 23: 1.1.1.1
// 24: 1...1.1
// 25: 1...111
// 26: 1....11
// 27: 11...11
// 28: 11...1.
// 29: 11.1.1.
// 30: 11.1...
// 31: 11.1..1
// 32: 11....1
// 33: 111...1
// 34: 1.1...1
// 35: 1.11..1
// 36: 1.11...
// 37: 1.11.1.
// 38: ..11.1.
// 39: .111.1.
// 40: .1.1.1.
// 41: .1.1.11
// 42: .1.1..1
// 43: .1.11.1
// 44: ...11.1
// 45: 1..11.1
// 46: 1..1..1
// 47: 1..1.11
// 48: 1..1.1.
// 49: 1..111.
// 50: 1..11..
// 51: 11.11..
// 52: .1.11..
// 53: .1.111.
// 54: ...111.
// 55: ..1111.
// 56: ..1.11.
// 57: .11.11.
// 58: .11.1..
// 59: 111.1..
// 60: 11..1..
// 61: 11..1.1
// 62: .1..1.1
// 63: .11.1.1
// 64: .11...1
// 65: .111..1
// 66: ..11..1
// 67: ..111.1
// 68: ..1.1.1
// 69: ..1.111
//
// k = 4   #pfct = 1
//   #paths = 2   #cycles = 1

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/graph-mtl-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-mtl-demo.cc DEMOFLAGS=-DTIMING"
/// End:

