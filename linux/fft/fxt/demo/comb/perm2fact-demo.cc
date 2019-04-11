
#include "comb/fact2perm.h"
// demo-include "comb/fact2perm.cc"
// demo-include "comb/fact2perm-rev.cc"
// demo-include "comb/fact2perm-rot.cc"
// demo-include "comb/fact2perm-swp.cc"

#include "comb/perm-lex.h"
#include "perm/perminvert.h"

//#include "comb-all.h"  // all permutation generators

#include "comb/comb-print.h"
#include "comb/mixedradix.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Show factorial representations (Lehmer, rev, rot, and swap) of permutations.


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements.");
    const bool dfz= true;  // whether to print dots for zeros
    bool rq = false;
    NXARG(rq, "Whether to compute rising factorial representations");
    bool iq = false;
    NXARG(iq, "Whether to convert inverse permutations");

    perm_lex P(n);  // default
//    perm_colex P(n);
//    perm_trotter P(n);
//    perm_heap P(n);
//    perm_star P(n);

    ulong *pi = new ulong[n];  // inverse permutation

    const ulong *x;
    if ( iq )   x = pi;
    else        x = P.data();

    ulong *fc = new ulong[n];  // factorrial representation

    cout << "         permutation     inv. perm.";
    cout << "     Lehmer         rev          swap         rot" << endl;

    ulong ct = 0;
    do
    {
        cout << setw(4) << ct << ":";
        ++ct;

        P.print("    ", dfz);

        make_inverse(P.data(), pi, n);
        print_perm("    ", pi, n, dfz);

        if ( rq )
        {
            perm2rfact(x, n, fc);
            print_mixedradix("    ", fc, n-1, dfz);
//            ulong ni = 0;  // number of inversions
//            for (ulong j=0; j<n-1; ++j)  ni += fc[j];
//            cout << ni;

            perm2rfact_rev(x, n, fc);
            print_mixedradix("    ", fc, n-1, dfz);
            perm2rfact_swp(x, n, fc);
            print_mixedradix("    ", fc, n-1, dfz);
            perm2rfact_rot(x, n, fc);
            print_mixedradix("    ", fc, n-1, dfz);
        }
        else
        {
            perm2ffact(x, n, fc);
            print_mixedradix("    ", fc, n-1, dfz);
            perm2ffact_rev(x, n, fc);
            print_mixedradix("    ", fc, n-1, dfz);
            perm2ffact_swp(x, n, fc);
            print_mixedradix("    ", fc, n-1, dfz);
            perm2ffact_rot(x, n, fc);
            print_mixedradix("    ", fc, n-1, dfz);
        }

        cout << endl;
    }
    while ( P.next() );

    delete [] pi;
    delete [] fc;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm2fact-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm2fact-demo.cc DEMOFLAGS=-DTIMING"
/// End:

