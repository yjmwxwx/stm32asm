
#include "graph/digraph.h"
#include "graph/digraph-paths.h"
// demo-include "graph/search-digraph.cc"
#include "graph/mk-special-digraphs.h"
// demo-include "graph/mk-perm-gray-digraph.cc"

#include "aux0/factorial.h"
#include "comb/num2perm.h"
#include "comb/fact2perm.h"
#include "comb/comb-print.h"
#include "perm/perminvert.h"
#include "bits/print-bin.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray codes through permutations with only adjacent interchanges and
//% successive transpositions overlapping (doubly-adjacent Gray codes).

//#define TIMING  // uncomment to disable printing

bool jcyc;
//ulong pn;

ulong N;
ulong nf;  // N!
ulong n1f;  // (N-1)!
ulong xx[32];  // aux (permutation)
ulong xxo[32];  // aux (last permutation)
ulong yy[32];  // aux (inverse permutation)
ulong yyo[32];  // aux (last inverse permutation)
ulong ff[32];  // aux (factorial number)

inline void print_one(ulong k, ulong x)
{
        cout << setw(4) << k << ": " << setw(6) << x;

        // show permutations:
        num2perm_rfact(x, xx, N);
        print_perm(" == ", xx, N, true);

        ulong df = 0;
        if ( k>0 )
        {
            for (ulong j=0; j<N; ++j)
                if ( xxo[j]!=xx[j] )  { df |= (1UL<<j); }
        }
        for (ulong j=0; j<N; ++j)  xxo[j]=xx[j];
        print_bin_vec("    ", df, N);

        make_inverse(xx, yy, N);
        print_perm("       ", yy, N, true);

        df = 0;
        if ( k>0 )
        {
            for (ulong j=0; j<N; ++j)
                if ( yyo[j]!=yy[j] )  { df |= (1UL<<j); }
        }
        for (ulong j=0; j<N; ++j)  yyo[j]=yy[j];
        print_bin_vec("    ", df, N);

        cout << "    ";
        perm2ffact(yy, N, ff);
        print_perm("   ", ff, N-1, true);
        perm2rfact(yy, N, ff);
        print_perm("   ", ff, N-1, true);
#if 0
        perm2ffact(xx, N, ff);
        print_perm("   ", ff, N-1, true);
        perm2rfact(xx, N, ff);
        print_perm("   ", ff, N-1, true);
#endif

        cout << endl;
}
// -------------------------


ulong
pfunc_permgray(const digraph_paths &dp)
// Function to be called with each path.
{
    // ----- conditions:
    if ( jcyc && (!dp.cq_) )  return 0;  // only cycles

#if 0  // test: (apparently no such path for N>=5)
    for (ulong k=0, m=0, d=1;  k<dp.ng_;  ++k)
    {
        const ulong x = dp.rv_[k];
        num2perm_rfact(x, xx, N);
        make_inverse(xx, yy, N);
        if ( yy[0] != m )  return 0;
        m += d;
        if ( m > N-1 )  { m-=d; d=-d; }
    }
#endif
#if 0  // test: (apparently no such path for N>=5)
    for (ulong k=0; k<dp.ng_/2; ++k)
    {
        const ulong x1 = dp.rv_[k];
        const ulong x2 = dp.rv_[k + dp.ng_/2];
        num2perm_rfact(x1, xx, N);
        num2perm_rfact(x2, yy, N);
        for (ulong j=0; j<N; ++j)  if ( xx[j] != yy[N-1-j] )  return 0;
    }
#endif

#ifndef TIMING
    // ----- actions:
//    dp.pfdone_ = true;

    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;

    cout << "Path #" << dp.pfct_ << ":" << endl;

    for (ulong k=0; k<ng; ++k)
    {
        const ulong x = rv[k];
        print_one(k, x);
    }

    cout << endl;
#endif  // TIMING

    return 1;
}
// -------------------------

ulong *perms;
void cond_init()
{
    nf = factorial(N);
    n1f = nf / N;
    perms = new ulong[nf * N];
    for (ulong k=0; k<nf; ++k)
    {
        num2perm_rfact(k, perms+k*N, N);
    }
}
// -------------------------


bool cfunc_adj(digraph_paths &dp, ulong ns)
// Condition: successive transpositions must overlap
{
//    return true;

    if ( ns<2 )  return  true;


    if ( ns==nf-1 )
    {
        if ( jcyc )  // cycle also wrt. double adjacent condition
        {
            ulong ct = 0;
            ulong p0 = N * dp.rv_[ns], p2 = N * dp.rv_[1];
            for (ulong j=0; j<N; ++j)  ct += ( perms[p0+j] != perms[p2+j] );
            if ( ct != 3 )  return false;
        }
    }

    ulong ct = 0;
    ulong p0 = N * dp.rv_[ns], p2 = N * dp.rv_[ns-2];

    // force first (N-1)! permutations to have same last element:
//    if ( (ns < n1f) && (perms[p0+N-1]!=N-1) )  return false;

    for (ulong j=0; j<N; ++j)  ct += ( perms[p0+j] != perms[p2+j] );
    return (ct==3);
}
// -------------------------


int
main(int argc, char **argv)
{
    N = 4;
    NXARG(N, "Number of elements in permutations");

    jcyc = true;
    NXARG(jcyc, "Whether only cycles are output");

    ulong maxnp = 1;
    NXARG(maxnp, "stop after maxnp paths (0: never stop)");

    uint  rnds = 0;
    NXARG(rnds, "if set, edge order is randomized and rnds is used as random seed");

    cond_init();

    digraph * dgp = make_perm_gray_digraph(N, false);
    digraph & dg = *dgp;

    dg.sort_edges(1);
    if ( rnds )
    {
        srand(rnds);
        dg.randomize_edge_order();
    }

//    dg.print();

    cout << "Graph has "
         << dg.num_nodes() << " nodes, "
         << dg.num_edges() << " edges."
         << endl;

    digraph_paths dp(dg);
    ulong npt = dp.all_cond_paths(pfunc_permgray, cfunc_adj, 0, 0, maxnp );
    cout << " % N=" << N << "  npt=" << npt << endl;

    delete [] perms;

    delete dgp;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/graph-perm-doubly-adjacent-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-perm-doubly-adjacent-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

