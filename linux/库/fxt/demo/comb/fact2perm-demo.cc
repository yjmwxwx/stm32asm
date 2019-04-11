
#include "comb/fact2perm.h"
// demo-include "comb/fact2perm.cc"
#include "comb/mixedradix-lex.h"
#include "perm/reverse.h"
#include "perm/permcomplement.h"
#include "perm/perminvert.h"

#include "comb/mixedradix-modular-gray.h"
#include "comb/mixedradix-gslex.h"
#include "comb/mixedradix-subset-lex.h"
#include "comb/mixedradix-gray.h"
#include "comb/mixedradix-sl-gray.h"
#include "comb/mixedradix-endo.h"
#include "comb/mixedradix-endo-gray.h"

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
    bool rq = 1;
    NXARG(rq, "Whether to use rising factorial base.");
    const bool dfz = true;  // whether to print dots for zeros
    const ulong n1 = n - 1;
    bool iq = 0;
    NXARG(iq, "Whether to generate inverse permutation for right columns (else reversed complement).");

    mixedradix_lex M(n1, rq);  // default
//    mixedradix_subset_lex M(n1, rq);
//    mixedradix_sl_gray M(n1, rq);
//    mixedradix_gray M(n1, rq);
//    mixedradix_modular_gray M(n1, rq);
//    mixedradix_gslex M(n1, rq);
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
        if ( rq )  rfact2perm(a, n, p);
        else       ffact2perm(a, n, p);
        print_perm("    ", p, n, dfz);

        cout << "      ";


        if ( iq )
        {
            make_inverse(p, ip, n);
            print_perm("    ", ip, n, dfz);
            if ( rq )  perm2rfact(ip, n, ia);
            else       perm2ffact(ip, n, ia);
            print_mixedradix("    ", ia, n1, dfz);
        }
        else
        {
            make_complement(p, ip, n);
            reverse(ip, n);
            print_perm("    ", ip, n, dfz);
            if ( ! rq )  perm2rfact(ip, n, ia);
            else         perm2ffact(ip, n, ia);
            print_mixedradix("    ", ia, n1, dfz);
        }


#if 1  // Testing that Xfact2perm() is inverse of perm2Xfact():
        if ( rq )  perm2rfact(p, n, t);
        else       perm2ffact(p, n, t);
//        print_mixedradix(" :: ", t, n1, dfz);
        for (ulong j=0; j<n1; ++j)  { jjassert(t[j]==a[j]); }
#endif

        cout << endl;


        ++ct;
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
/// make-target: "1demo DSRC=demo/comb/fact2perm-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/fact2perm-demo.cc DEMOFLAGS=-DTIMING"
/// End:

