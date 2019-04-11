
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


//% Gray codes through permutations with star transpositions.


bool jcyc;
//ulong pn;

static ulong N;
ulong nf;  // N!
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
        perm2rfact(yy, N, ff);
        print_perm("   ", ff, N-1, true);

        df = 0;
        if ( k>0 )
        {
            for (ulong j=0; j<N; ++j)
                if ( yyo[j]!=yy[j] )  { df |= (1UL<<j); }
        }
        for (ulong j=0; j<N; ++j)  yyo[j]=yy[j];
        print_bin_vec("    ", df, N);


        cout << endl;
}
// -------------------------


ulong
pfunc_permgray(const digraph_paths &dp)
// Function to be called with each path.
{
    // ----- conditions:
    if ( jcyc && (!dp.cq_) )  return 0;  // only cycles


    // ----- actions:
//    dp.pfdone_ = true;

    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;


    cout << "Path #" << dp.pfct_ << ":" << endl;

#if 1
    for (ulong k=0; k<ng; ++k)
    {
        const ulong x = rv[k];
        print_one(k, x);
    }

#else  // short output only:
    print_one(0, rv[0]);
    print_one(1, rv[1]);
    print_one(ng-1, rv[ng-1]);
#endif

    cout << endl;

    return 1;
}
// -------------------------

ulong *perms;
void cond_init()
{
    nf = factorial(N);
    perms = new ulong[nf * N];
    for (ulong k=0; k<nf; ++k)
    {
        num2perm_rfact(k, perms+k*N, N);
    }
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

//    digraph dg( make_perm_gray_digraph(N) );

    digraph * dgp = make_perm_gray_digraph(N, true);
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
    ulong npt = dp.all_paths(pfunc_permgray, 0, 0, maxnp );
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
/// make-target: "1demo DSRC=demo/graph/graph-perm-star-transpositions-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/graph-perm-star-transpositions-demo.cc DEMOFLAGS=-DTIMING"
/// End:

