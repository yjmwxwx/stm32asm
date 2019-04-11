
#include "comb/fact2perm.h"
// demo-include "comb/fact2perm-swp.cc"
#include "perm/perminvert.h"  // make_inverse()
// demo-include "perm/perminvert.cc"
#include "comb/mixedradix-lex.h"

#include "perm/permq.h"  // is_inverse()

#include "comb/mixedradix-modular-gray.h"
#include "comb/mixedradix-gslex.h"
#include "comb/mixedradix-gray.h"
#include "comb/mixedradix-endo.h"
#include "comb/mixedradix-endo-gray.h"
#include "comb/mixedradix-subset-lex.h"
#include "comb/mixedradix-sl-gray.h"

#include "comb/comb-print.h"
#include "comb/mixedradix.h"

#include "comb/check-permgen.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"  // NXARG()
#include "fxtio.h"


//% Generate all permutations from mixed radix (factorial) numbers.


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements to permute");
    bool rq = 0;
    NXARG(rq, "Whether to use rising factorial base.");
    const bool dfz = true;  // whether to print dots for zeros
    const ulong n1 = n - 1;

    mixedradix_lex M(n1, rq);  // default
//    mixedradix_gray M(n1, rq);
//    mixedradix_subset_lex M(n1, rq);
//    mixedradix_sl_gray M(n1, rq);
//    mixedradix_modular_gray M(n1, rq);
//    mixedradix_gslex M(n1, rq);
//    mixedradix_endo M(n1, rq);
//    mixedradix_endo_gray M(n1, rq);
    M.print_nines(" Nines: ");  cout << endl;

    const ulong *fc = M.data();  // factorial number
    ulong *ifc = new ulong[n1];  // factorial number for inverse permutation

    ulong *p = new ulong[n];   // permutation
    ulong *ip = new ulong[n];  // inverse permutation

    ulong *t = new ulong[n];  // aux for testing

    check_permgen C(n);  C.first(p);

    ulong ct = 0;
    do
    {
        cout << " " << setw(3) << ct << ":";

        print_mixedradix("    ", fc, n1, dfz);

        if ( rq )  rfact2perm_swp(fc, n, p);
        else       ffact2perm_swp(fc, n, p);
        print_perm("  ", p, n, dfz);

        cout << "    |  ";

        make_inverse(p, ip, n);
        print_perm("    ", ip, n, dfz);

        if ( rq ) perm2rfact_swp(ip, n, ifc);
        else      perm2ffact_swp(ip, n, ifc);
        print_mixedradix("  ", ifc, n1, dfz);

        cout << endl;

        jjassert( ! C.is_repeat() );
#if 1
        // Testing whether fact2perm_swp() is the inverse of perm2fact_swp():
        if ( rq )  perm2rfact_swp(p, n, t);
        else       perm2ffact_swp(p, n, t);
//        print_mixedradix(" :: ", t, n1, dfz);  cout << endl;
        for (ulong j=0; j<n1; ++j)  { jjassert( t[j]==fc[j] ); }

        // Testing whether fact2invperm_swp() really gives inverse permutation:
        if ( rq )  rfact2invperm_swp(fc, n, t);
        else       ffact2invperm_swp(fc, n, t);
//        print_mixedradix(" :: ", t, n, dfz);  cout << endl;
        jjassert( is_inverse(p, t, n) );
#endif

        ++ct;
    }
    while ( M.next() );

    delete [] ifc;
    delete [] p;
    delete [] ip;
    delete [] t;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/fact2perm-swp-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/fact2perm-swp-demo.cc DEMOFLAGS=-DTIMING"
/// End:

