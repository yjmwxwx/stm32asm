
#include "comb/fact2perm.h"
// demo-include "comb/fact2perm.cc"
#include "comb/mixedradix-lex.h"

//#include "perm/reverse.h"
//#include "perm/permcomplement.h"
//#include "perm/perminvert.h"

#include "comb/mixedradix-gray.h"
#include "comb/mixedradix-modular-gray.h"
#include "comb/mixedradix-gslex.h"
#include "comb/mixedradix-gslex-alt.h"
#include "comb/mixedradix-endo.h"
#include "comb/mixedradix-endo-gray.h"

#include "comb/comb-print.h"
#include "comb/mixedradix.h"

#include "comb/check-kpermgen.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"  // NXARG()
#include "fxtio.h"


//% Generate all k-permutations of n elements from falling factorial numbers.


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Total of n elements");
    const bool dfz = true;  // whether to print dots for zeros
    const ulong n1 = n - 1;
    ulong k = 3;
    NXARG(k, "Permutations of k elements (1<=k<=n)");
    if ( k<1 )  k = 1;
    if ( k>n )  k = n;

    mixedradix_lex M(n1, 0);  // default
//    mixedradix_gray M(n1, 0);

//    mixedradix_modular_gray M(n1, 0);
//    mixedradix_gslex M(n1, 0);
//    mixedradix_gslex_alt M(n1, 0);
//    mixedradix_endo M(n1, 0);
//    mixedradix_endo_gray M(n1, 0);

//    M.print_nines(" Nines: ");  cout << endl;

    const ulong *a = M.data();  // factorial number
//    ulong *ia = new ulong[n1];  // factorial number for inverse permutation

    ulong *p = new ulong[n];  // permutation
//    ulong *ip = new ulong[n];  // inverse permutation

    check_kpermgen C(n, k);  C.first(p);
    cout << " C.N=" << C.N_ << endl;

    ulong ct = 0;
//    bool q;
    do
    {
        cout << setw(4) << ct << ":";

        print_mixedradix("    ", a, n1, dfz);

        ffact2perm(a, n, p);
        print_perm("    ", p, k, dfz);
        print_perm("", p+k, n-k, dfz);

//        cout << "      ";
//        make_inverse(p, ip, n);
//        print_perm("    ", ip, n, dfz);
//        perm2ffact(ip, n, ia);
//        print_mixedradix("    ", ia, n1, dfz);
//

        cout << endl;
        jjassert( ! C.is_repeat() );

        ++ct;
        if ( ct==C.N_ )  break;

//        q = M.next();
//        if ( M.pos() >= k )  break;  // k-perms
    }
    while ( M.next() );

    jjassert( C.have_all() );

//    delete [] ia;
    delete [] p;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ffact2kperm-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ffact2kperm-demo.cc DEMOFLAGS=-DTIMING"
/// End:

