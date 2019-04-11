
#include "comb/composition-rank.h"
// demo-include "comb/num-compositions.h"

// demo-include "comb/composition-rank.cc"

#include "nextarg.h"

#include "jjassert.h"
#include "fxttypes.h"
#include "fxtio.h"


//% Ranking and unranking compositions
//% in lexicographic, Gray, and enup (two-close) order


int
main(int argc, char **argv)
{
    ulong k = 5, n = 3;
    NXARG(k, "k-compositions of n (k>=1) ");
    NXARG(n, " (n>=1)");
    ulong rd = 2;
    NXARG(rd, " Order: 0==>lex,  1==>Gray,  2==>enup (two-close)");

    composition_rank C(n, k);

    ulong *x = new ulong[k];
    ulong nc = C.num_comp(n, k);
    for (ulong j=0; j<nc; ++j)
    {
        cout << setw(4) << j << ":";

        switch ( rd )
        {
        case 1:  C.unrank_gray(x, n, k, j);  break;
        case 2:  C.unrank_enup(x, n, k, j);  break;
        default: C.unrank_lex(x, n, k, j);
        }

        C.print("    ", x, k);
        C.print_deltaset_num("    ", x, k);
        C.print_deltaset("    ", x, k);
        cout << endl;

        ulong r = 0;
        switch ( rd )
        {
        case 1:  r = C.rank_gray(x, n, k);  break;
        case 2:  r = C.rank_enup(x, n, k);  break;
        default: r = C.rank_lex(x, n, k);
        }

        jjassert( r == j );
        jjassert( C.is_comp(x, n, k) );
    }

    cout << "  #= " << nc << endl;

    delete [] x;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-rank-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-rank-demo.cc DEMOFLAGS=-DTIMING"
/// End:

