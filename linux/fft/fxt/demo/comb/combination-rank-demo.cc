
#include "comb/composition-rank.h"
// demo-include "comb/composition-rank.cc"
#include "comb/comp2comb.h"  // comp2comb()


#include "nextarg.h"

#include "jjassert.h"
#include "fxttypes.h"
#include "fxtio.h"


//% Ranking and unranking combinations in near-perfect order


int
main(int argc, char **argv)
{
    ulong N = 7;
    NXARG(N, "Combinations (N choose K): (n>=1)");
    ulong K = 3;
    NXARG(K, " (1<=K<=N) ");
    bool rq = 0;
//    NXARG(rq, "Option: let combinations start with [0,1,2,...,K-1]");
    ulong zq = 2;
    NXARG(zq, "Option: choose order: 0=lex, 1=gray, 2=near-perfect");

    ulong k = N-K+1,  n = K;
    cout << "\nUsing " << k << "-compositions of " << n << endl;
    ulong *c = new ulong[K];

    composition_rank R(n, k);


    ulong *x = new ulong[k];
    ulong nc = R.num_comp(n, k);
    for (ulong j=0; j<nc; ++j)
    {
        switch ( zq )
        {
        case 0:  R.unrank_lex(x, n, k, j);  break;
        case 1:  R.unrank_gray(x, n, k, j);  break;
        default: R.unrank_enup(x, n, k, j);
        }

        comp2comb(x, k, c);

        if ( rq )  reverse_combination(c, N, K);

        cout << setw(4) << j << ":";

        R.print("    ", x, k);
//        R.print_deltaset("    ", x, k);
        R.print_deltaset_num("    ", x, k);

        cout << "    [ ";
        for (ulong z=0; z<K; ++z)  cout << c[z] << (z<K-1?", ":" ");
        cout << "]";

        cout << endl;


        ulong r;
        switch ( zq )
        {
        case 0:  r = R.rank_lex(x, n, k);  break;
        case 1:  r = R.rank_gray(x, n, k);  break;
        default: r = R.rank_enup(x, n, k);
        }
        jjassert( r == j );
    }

    cout << "  #= " << nc << endl;

    delete [] x;
    delete [] c;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/combination-rank-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/combination-rank-demo.cc DEMOFLAGS=-DTIMING"
/// End:

