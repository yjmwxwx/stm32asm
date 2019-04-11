

#include "comb/fact2perm.h"
// demo-include "comb/fact2perm-rot.cc"
#include "perm/perminvert.h"  // make_inverse()
// demo-include "perm/perminvert.cc"
#include "comb/mixedradix-lex.h"

//#include "perm/printcycles.h"

#include "comb/mixedradix-modular-gray.h"
#include "comb/mixedradix-gslex.h"
#include "comb/mixedradix-gslex-alt.h"
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
//    mixedradix_gslex_alt M(n1, rq);
//    mixedradix_endo M(n1, rq);
//    mixedradix_endo_gray M(n1, rq);
    M.print_nines(" Nines: ");  cout << endl;

    const ulong *a = M.data();  // factorial number
    ulong *ia = new ulong[n1];  // factorial number for inverse permutation

    ulong *p = new ulong[n];  // permutation
    ulong *ip = new ulong[n];  // inverse permutation

    ulong *t = new ulong[n1];  // aux for testing

    check_permgen C(n);  C.first(p);

    ulong ct = 0;
    do
    {
        cout << " " << setw(3) << ct << ":";

        print_mixedradix("    ", a, n1, dfz);

        if ( rq )  rfact2perm_rot(a, n, p);
        else       ffact2perm_rot(a, n, p);
        print_perm("    ", p, n, dfz);
//        print_cycles("    ", p, n);

        cout << "      ";

        make_inverse(p, ip, n);
        print_perm("    ", ip, n, dfz);
//        print_cycles("    ", ip, n);

//        if ( rq ) perm2rfact_rot(ip, n, ia);
//        else      perm2ffact_rot(ip, n, ia);
//        print_mixedradix("    ", ia, n1, dfz);

#if 1  // Testing that Xfact2perm() is inverse of perm2Xfact():
        if ( rq )  perm2rfact_rot(p, n, t);
        else       perm2ffact_rot(p, n, t);
//        print_mixedradix("   :: ", t, n1, dfz);
        for (ulong j=0; j<n1; ++j)  { jjassert( t[j]==a[j] ); }
#endif

        ++ct;
        cout << endl;

//        if ( ct>6 ) return 0;

        jjassert( ! C.is_repeat() );
    }
    while ( M.next() );

    delete [] ia;
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
/// make-target: "1demo DSRC=demo/comb/fact2perm-rot-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/fact2perm-rot-demo.cc DEMOFLAGS=-DTIMING"
/// End:

