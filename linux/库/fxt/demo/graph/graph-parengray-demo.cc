
#include "bits/parenwords.h"  // parenword2str()
#include "graph/digraph.h"
#include "graph/digraph-paths.h"
// demo-include "graph/search-digraph.cc"
#include "graph/mk-special-digraphs.h"
// demo-include "graph/mk-paren-gray-digraph.cc"

#include "bits/print-bin.h"  // print_bin()

//#include "include/bits-all.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray codes through valid parentheses strings

bool jcyc;
ulong pn;
ulong
pfunc_parengray(const digraph_paths &dp)
// Function to be called with each path.
{
    // ----- conditions:
    if ( jcyc && (!dp.cq_) )  return 0;  // only cycles


    // ----- actions:
//    dp.pfdone_ = true;

    const ulong *vn = dp.g_.vn_;
    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;


//    if ( 0xaaaaaaaa & vn[rv[ng-1]] )  return 0;  // allow last=="()()()()" only

//    ulong x1 = vn[rv[0]]^vn[rv[1]];   // AC condition
//    for (ulong k=2; k<ng; ++k)
//    {
//        ulong x2 =  vn[rv[k]]^vn[rv[k-1]];
//        if ( 0==(x1&x2) )  return 0;
//        x1 = x2;
//    }

//    ulong x1 = vn[rv[0]]^vn[rv[1]];  // condition
//    for (ulong k=2; k<ng; ++k)
//    {
//        x1 &=  vn[rv[k]]^vn[rv[k-1]];
//        if ( 0==x1 )  return 0;
//    }


    cout << "Path #" << dp.pfct_ << ":" << endl;

    char str[65];
    for (ulong k=0; k<ng; ++k)
    {
        cout << setw(4) << k << ": ";
        ulong fk = vn[rv[k]];

        // show bitstring:
        print_bin("  ", fk, pn);

        // show parens:
        parenword2str(fk, str);
        cout << " == " << str;

        // show changes:
        if ( k>0 )
        {
            ulong df = fk^vn[rv[k-1]];
            print_bin("   ^= ", df, pn);
        }
        else
        {
            print_bin("      ", 0, pn);
        }

        // show restricted growth string:
        cout << "  [ ";
        for (ulong i=0, z=0;  str[i];  ++i)
        {
            if ( ')'==str[i] )  continue;
            cout << (2*z-i) << ", ";
            ++z;
        }
        cout << "]";

        cout << endl;
    }


    return 1;
}
// -------------------------


//static int my_cmp(const ulong &a, const ulong &b)
//// Playground.
//{
////#define CODE(x) (x)
////#define CODE(x) inverse_gray_code(x)
////#define CODE(x) blue_code(x)
//#define CODE(x) bit_sequency(x)
//    ulong ta = CODE(a),  tb = CODE(b);
//    if ( ta==tb )  return 0;
////    return  ( ta<tb ? +1 : -1);
//    return  ( ta>tb ? +1 : -1);
//#undef CODE
//}
//// -------------------------

int
main(int argc, char **argv)
{
    ulong npp = 6;
    NXARG(npp, "Number of paren pairs");
    pn = 2*npp;  // for printing

    jcyc = false;
    NXARG(jcyc, "Whether only cycles are output");

    ulong maxnp = 1;
    NXARG(maxnp, "stop after maxnp paths (0: never stop)");

    ulong pcd = 2;
    NXARG(pcd, "Condition on path (XOR-pattern):\n"
          "     0:none,   1:'101' or '11',   2: just '11'");

    if ( npp & 1 )  // npp odd ==> (no result for conditions 2 or 3)
    {
        if ( pcd>1 )
        {
            cout << "npp odd ==> setting condition to 1." << endl;
            pcd = 1;
        }
    }

//    digraph dg( make_parengray_digraph(npp, pcd) );
    digraph * dgp = make_parengray_digraph(npp, pcd);
    digraph &dg = *dgp;
//    dg.sort_edges(my_cmp);
//    dg.print();
    cout << "Graph has "
         << dg.num_nodes() << " nodes, "
         << dg.num_edges() << " edges."
         << endl;

    digraph_paths dp(dg);
    ulong npt = dp.all_paths(pfunc_parengray, 0, 0, maxnp );
    cout << " % npp=" << npp << "  npt=" << npt << endl;

    delete dgp;

    return 0;
}
// -------------------------

// Try also:
// ./bin 6 0 1 3
// ./bin 5 1 1 0
// ./bin 8 0 1 0

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/graph-parengray-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-parengray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

