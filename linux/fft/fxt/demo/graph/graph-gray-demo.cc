
#include "graph/digraph.h"
#include "graph/digraph-paths.h"
#include "graph/mk-special-digraphs.h"
// demo-include "graph/search-digraph.cc"
// demo-include "graph/mk-gray-digraph.cc"

//#include "comb/gray.h"

#include "comb/comb-print.h"

#include "graph/print-path.h"
#include "bits/bitcount.h"
#include "bits/graycode.h"
#include "bits/bitlex.h"
#include "bits/bittransforms.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "fxtio.h"


//% Paths through a directed graph: Gray paths.


ulong
pfunc_gray(const digraph_paths &dp)
// Function to be called with each path.
{
    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;

    // ----- conditions:
//    if ( ! dp.cq_ )  return 0;  // only cycles
//    if ( dp.cq_ )  return 0;  // no cycles  (monotonic are never cycles)

//    if ( ! is_canonical_gray(rv, ng) )  return 0;
//    if ( ! is_complementary_gray(rv, ng) )  return 0;

    // ----- actions:

    cout << dp.pfct_ << ":" << endl;
    print_gray(rv, ng);
//    print_gray_delta(rv, ng);
//    cout << endl;

    int shortq = 1;
    dp.print_turns( shortq );
    cout << endl;


//    static ulong ct = 0;  ++ct;
//    if ( 0==(ct&1023) )  { cout << "\r" << ct; cout.flush(); }

    return 1;
}
// -------------------------


int cmp_lex(const ulong &a, const ulong &b)
{
    if ( a==b )  return  0;
#define CODE(x) lexrev2negidx(x)
    ulong ca = CODE(a),  cb = CODE(b);
#undef CODE
    return (ca<cb ? +1 : -1);
}
// -------------------------


int cmp_blue(const ulong &a, const ulong &b)
{
    if ( a==b )  return  0;
#define CODE(x) blue_code(x)
    ulong ca = CODE(a), cb = CODE(b);
#undef CODE
    return (ca>cb ? +1 : -1);
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "word size in bits, n>=2");
    if ( n<2 )  n = 2;

    ulong rq = 0;
//    NXARG(rq, "force path to start as 0 1 3");

    ulong maxnp = 1;
    NXARG(maxnp, "stop after maxnp paths (0: never stop)");

    ulong sortq = 1;
    NXARG(sortq, "whether to do edge-sorting 0:no, 1:lex 2:blue, >2:randomize");

    ulong erevq = 0;
    NXARG(erevq, "whether to reverse edge-order");

    digraph * dgp = make_gray_digraph(n, rq);
    digraph &dg = *dgp;

    if ( 1==sortq )  dg.sort_edges(cmp_lex);
    if ( 2==sortq )  dg.sort_edges(cmp_blue);
    srand( (uint)sortq );
    if ( 3<=sortq )  dg.randomize_edge_order();

    if ( erevq )  dg.reverse_edge_order();

//    dg.print("Graph =");


    digraph_paths dp(dg);

    // All the work is done here:
    // (pfunc_gray() is called with each path)
    dp.all_paths(pfunc_gray, 0, 0, maxnp);

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

// n=4:
//    #paths = 5712   #cycles = 2688
// canonical:  238
// canonical cycles:  112
// canonical complementary: 92

// complementary cycles for n = 4:
//
//n = 4   #pfct = 4
//   #paths = 5712   #cycles = 2688
//
//  0:  .... 0   0
//  1:  ...1 1   1    0  ...1
//  2:  ..11 2   3    1  ..1.
//  3:  ..1. 1   2    0  ...1
//  4:  .11. 2   6    2  .1..
//  5:  .1.. 1   4    1  ..1.
//  6:  .1.1 2   5    0  ...1
//  7:  .111 3   7    1  ..1.
//  8:  1111 4  15    3  1...
//  9:  111. 3  14    0  ...1
// 10:  11.. 2  12    1  ..1.
// 11:  11.1 3  13    0  ...1
// 12:  1..1 2   9    2  .1..
// 13:  1.11 3  11    1  ..1.
// 14:  1.1. 2  10    0  ...1
// 15:  1... 1   8    1  ..1.
//
//  0:  .... 0   0
//  1:  ...1 1   1    0  ...1
//  2:  ..11 2   3    1  ..1.
//  3:  .111 3   7    2  .1..
//  4:  .11. 2   6    0  ...1
//  5:  .1.. 1   4    1  ..1.
//  6:  .1.1 2   5    0  ...1
//  7:  11.1 3  13    3  1...
//  8:  1111 4  15    1  ..1.
//  9:  111. 3  14    0  ...1
// 10:  11.. 2  12    1  ..1.
// 11:  1... 1   8    2  .1..
// 12:  1..1 2   9    0  ...1
// 13:  1.11 3  11    1  ..1.
// 14:  1.1. 2  10    0  ...1
// 15:  ..1. 1   2    3  1...
//
//  0:  .... 0   0
//  1:  ...1 1   1    0  ...1
//  2:  ..11 2   3    1  ..1.
//  3:  .111 3   7    2  .1..
//  4:  .11. 2   6    0  ...1
//  5:  ..1. 1   2    2  .1..
//  6:  1.1. 2  10    3  1...
//  7:  1.11 3  11    0  ...1
//  8:  1111 4  15    2  .1..
//  9:  111. 3  14    0  ...1
// 10:  11.. 2  12    1  ..1.
// 11:  1... 1   8    2  .1..
// 12:  1..1 2   9    0  ...1
// 13:  11.1 3  13    2  .1..
// 14:  .1.1 2   5    3  1...
// 15:  .1.. 1   4    0  ...1
//
//  0:  .... 0   0
//  1:  ...1 1   1    0  ...1
//  2:  ..11 2   3    1  ..1.
//  3:  .111 3   7    2  .1..
//  4:  .1.1 2   5    1  ..1.
//  5:  11.1 3  13    3  1...
//  6:  1..1 2   9    2  .1..
//  7:  1.11 3  11    1  ..1.
//  8:  1111 4  15    2  .1..
//  9:  111. 3  14    0  ...1
// 10:  11.. 2  12    1  ..1.
// 11:  1... 1   8    2  .1..
// 12:  1.1. 2  10    1  ..1.
// 13:  ..1. 1   2    3  1...
// 14:  .11. 2   6    2  .1..
// 15:  .1.. 1   4    1  ..1.
//

// monotonic:
//   0:  .... 0   0
//   1:  ...1 1   1    0  ...1
//   2:  ..11 2   3    1  ..1.
//   3:  ..1. 1   2    0  ...1
//   4:  .11. 2   6    2  .1..
//   5:  .1.. 1   4    1  ..1.
//   6:  11.. 2  12    3  1...
//   7:  1... 1   8    2  .1..
//   8:  1.1. 2  10    1  ..1.
//   9:  1.11 3  11    0  ...1
//  10:  1..1 2   9    1  ..1.
//  11:  11.1 3  13    2  .1..
//  12:  .1.1 2   5    3  1...
//  13:  .111 3   7    1  ..1.
//  14:  1111 4  15    3  1...
//  15:  111. 3  14    0  ...1

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/graph-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

