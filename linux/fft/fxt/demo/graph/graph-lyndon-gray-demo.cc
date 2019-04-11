
#include "graph/digraph.h"
#include "graph/digraph-paths.h"
// demo-include "graph/search-digraph.cc"
// demo-include "graph/search-digraph-cond.cc"
#include "graph/mk-special-digraphs.h"
// demo-include "graph/mk-lyndon-gray-digraph.cc"
// demo-include "graph/lyndon-cmp.cc"

// for the comparison function my_lyndon_cmp():
#include "bits/bitcount.h"
#include "bits/graycode.h"
#include "bits/bitlex.h"
#include "bits/revbin.h"
#include "bits/bitlow.h"
#include "bits/bithigh.h"
#include "bits/bitsequency.h"
#include "bits/bittransforms.h"

#include "bits/bit2pow.h"


#include "nextarg.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"


//% Paths through a directed graph: Gray paths through Lyndon words.


lyngray_dat *ldat;

void
print(const digraph_paths &dp)
{
    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;

    lyndon_gray_rot_delta(rv, ng, ldat);

    cout << setw(4) << dp.pfct_ << ":  ";

//    // print delta sequence:
//    const char dd[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ@";
//    // enough w/base: "_23456789.123456789.123456789.123456789";
//    cout << endl;
//    for (ulong k=0; k<ng; ++k)
//    {
//        cout << dd[(ulong)(ldat->dd[k])];
//        if ( 0==((k+1)%100) )  cout << endl;
//    }

    cout << endl;

    // detailed print:
    print_lyndon_gray_path(dp, ldat);

    int shortq = 1;
    dp.print_turns( shortq );
    cout << endl;
}
// -------------------------


ulong
pfunc_lyndon_gray(const digraph_paths &dp)
// Function to be called with each path.
{
//    return 0;  // just count

//    if ( dp.cq_ )  return 0;  // select NON-cycles  e.g. for monotonic paths

    print(dp);

    return 1;
}
// -------------------------

ulong
pfunc_lyndon_gray_cyc(const digraph_paths &dp)
// Function to be called with each path.
{
//    return 0;  // just count

    if ( ! dp.cq_ )  return 0;  // select cycles

    print(dp);

    return 1;
}
// -------------------------



bool cfunc_rot0(digraph_paths &dp, ulong ns)
{
//    if ( 1>=ns )  return true;
    ulong p  = dp.rv_[ns],  p1 = dp.rv_[ns-1];
    ulong *vn = dp.g_.vn_;
    p = vn[p];  p1 = vn[p1];
    if ( one_bit_q( p ^ p1 ) )  return true;
    return false;
}
// -------------------------

bool cfunc_monotonic(digraph_paths &dp, ulong ns)
{
    if ( 1>=ns )  return true;
    ulong p  = dp.rv_[ns],  p2 = dp.rv_[ns-2];
    ulong *vn = dp.g_.vn_;
    p = vn[p];  p2 = vn[p2];
    if ( bit_count(p) >= bit_count(p2) )  return true;
    return false;
}
// -------------------------

bool cfunc_both(digraph_paths &dp, ulong ns)
{
    return  ( cfunc_rot0(dp, ns) && cfunc_monotonic(dp, ns) );
}
// -------------------------

static int my_lyndon_cmp(const ulong &a, const ulong &b)
// Playground.
// Works as given for n<=13
{
//    return 0;  // do not sort
    if ( a==b )  return 0;

    int bc = bit_count_cmp(a, b);
    if ( bc )  return  -bc;

//#define CODE(x) (x)
//#define CODE(x) inverse_gray_code(x)
//#define CODE(x) blue_code(x)
#define CODE(x) bit_sequency(x)
    ulong ta = CODE(a),  tb = CODE(b);
    if ( ta==tb )  return 0;
//    return  ( ta<tb ? +1 : -1);
    return  ( ta>tb ? +1 : -1);
#undef CODE
}
// -------------------------

static int mon_cmp(const ulong &a, const ulong &b)
{
    int bc = bit_count_cmp(a, b);
    if ( bc )  return  bc;
    return ( a<b ? +1 : -1 );
}
// -------------------------


typedef int (*CF)(const ulong &, const ulong &);
CF cf[] = {
    lyndon_cmp0,  // [0]
    lyndon_cmp1,  // [1]
    lyndon_cmp2,  // [2]
    lyndon_cmp3,  // [3]
    lyndon_cmp4,  // [4]
    lyndon_cmp5,  // [5]
    lyndon_cmp6,  // [6]
    lyndon_cmp7,  // [7]

    mon_cmp,       // [8]
    my_lyndon_cmp,  // [9]
    0  // [10]==end
};
// -------------------------

// ==================================
// These values for cn quickly lead to Gray codes
//  for size-p Lyndon words:
// cn:  p =
//  0:  3 5 7 11 13
//  1:  3 5 7 11    17 19
//  2:  3 5 7 11 13 17
//  3:  3 5 7 11 13 17 19 23
//  4:  3 5 7 11 13
//  5:  3 5 7 11 13    19 23
//  6:  3 5 7 11 13 17 19
//  7:  3 5 7 11 13 17 19 23 (29 31)
// ==================================


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "a prime <=23");
    if ( n<3 )  n = 3;

    ulong maxnp = 1;
    NXARG(maxnp, "stop after maxnp paths (0: never stop)");


    ulong cn = 0;
    NXARG(cn, "choose comparison function for sorting edges");
    ulong mcn = 0;  while ( cf[mcn+1] )  ++mcn;
    ulong erevq = 0;
    NXARG(erevq, "whether to reverse edge-order");

    ulong condn = 0;
    NXARG(condn, "choose condition: 0==>cycles, 1==>rot0, 2==>monotonic, 3==>1&2, 4==>nil");

    ulong rot0q =  condn & 1;
    digraph * dgp = make_lyndon_gray_digraph(n, ldat, rot0q);
    digraph &dg = *dgp;

    if ( cn<=mcn )
    {
        cout << "Using comparison function #" << cn << endl;
        dg.sort_edges(cf[cn]);
        jjassert( dg.is_edge_sorted(cf[cn]) );
    }

    if ( erevq )  dg.reverse_edge_order();
//    dg.print("Graph =");  return 0;

//    cout << "Graph (binary values) =" << endl;
//    print_lyndon_gray_digraph(dg, ldat);
    cout << "  #nodes=" << dg.num_nodes();
    cout << "  #edges=" << dg.num_edges();
    cout << endl;

    digraph_paths dp(dg);

    // All the work is done here:
    // (pfunc_lyndon_gray() is called with each path)
    switch ( condn )
    {
    case 0: dp.all_paths(pfunc_lyndon_gray_cyc, 0, 0, maxnp);  break;
    case 1: dp.all_paths(pfunc_lyndon_gray, 0, 0, maxnp);  break;
    case 2: dp.all_cond_paths(pfunc_lyndon_gray, cfunc_monotonic, 0, 0, maxnp);  break;
        // monotonic rot0 only for 3 and 5:
    case 3: dp.all_cond_paths(pfunc_lyndon_gray, cfunc_monotonic, 0, 0, maxnp);  break;

    default: dp.all_paths(pfunc_lyndon_gray, 0, 0, maxnp);  break;
    }

    cout << "n = " << n;
    cout << "   #pfct = " << dp.pfct_;
    cout << endl;
    cout << "   #paths = " << dp.pct_;
    cout << "   #cycles = " << dp.cct_;
    cout << endl;

    delete ldat;
    delete dgp;

    return 0;
}
// -------------------------


// n:       pathes       cycles   zero-rot-seq    lowest-one-seq    monotonic
//                                tot. / cycles   tot. / cycles
// 3:         1              1      1 / 1           1 / 1                 0
// 5:         8              4      3 / 2           5 / 3                 4
// 7:   1022148         294144    395 / 112    108901 / 26256            3180


// ./bin 13 1 8 1
// ./bin 9 1 7
// ./bin 25 1 7  # takes a moment
// ./bin 6 999999 7 0 2

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/graph-lyndon-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-lyndon-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

