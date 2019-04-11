

#include "comb/fact2perm.h"
// demo-include "comb/fact2cyclic.cc"
#include "comb/mixedradix-modular-gray.h"
#include "perm/perminvert.h"  // make_inverse()
#include "perm/permq.h"  // is_cyclic()

#include "perm/printcycles.h"
#include "comb/comb-print.h"

//#include "comb/perm-gray-ffact.h"
#include "comb/mixedradix-lex.h"
//#include "comb/mixedradix-gslex.h"
//#include "comb/mixedradix-gslex-alt.h"
#include "comb/mixedradix-gray.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"  // NXARG()
#include "fxtio.h"


//% Generate all cyclic permutations from mixed radix numbers.

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of elements to permute");
    bool rq = 0;
    NXARG(rq, "Whether to use rising base with mixed radix counting");
    bool dfz = true;  // whether to print dots for zeros

    ulong n2 = n - 2;
//    ulong *m = new ulong[n2];
//
//    if ( rq )  for (ulong k=0; k<n2; ++k)  m[k] = k+2;  // factorial base
//    else       for (ulong k=0; k<n2; ++k)  m[k] = n-1-k;  // reversed factorial base
//
//    print_mixedradix(" Radix == ", m, n2);  cout << endl;

    mixedradix_lex M(n2, rq);
//    mixedradix_gray M(n2, rq);
//    mixedradix_modular_gray M(n2, rq);
//    mixedradix_gslex M(n2, rq);

    M.print_nines(" Nines: ");  cout << endl;

    const ulong *a = M.data();  // factorial number

    ulong *p = new ulong[n];  // permutation
    ulong *ip = new ulong[n];  // inverse permutation
    ulong ct = 0;
    do
    {
//        cout << " " << setw(3) << ct << ":";

        if ( rq )  rfact2cyclic(a, n, p);
        else       ffact2cyclic(a, n, p);

        print_mixedradix("    ", a, n2, dfz);
        print_perm("    ", p, n);
        cout << "    ";   print_cycle(p, 0);

//        cout << "    |  ";
        make_inverse(p, ip, n);
        print_perm("    ", ip, n);

        ++ct;
        cout << endl;

        jjassert( is_cyclic(p, n) );
//        jjassert( is_cyclic(ip, n) );
    }
    while ( M.next() );

    delete [] p;
    delete [] ip;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/fact2cyclic-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/fact2cyclic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

