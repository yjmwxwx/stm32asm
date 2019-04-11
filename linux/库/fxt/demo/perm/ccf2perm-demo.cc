
#include "perm/perm2ccf.h"
// demo-include "perm/perm2ccf.cc"

#include "comb/perm-lex.h"
#include "comb/perm-trotter.h"

#include "ds/bitarray.h"
#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

#include "jjassert.h"

//% Convert permutations to and from canonical cycle form (CCF).

//#define TIMING  // uncomment to disable printing


static inline bool same_q(const ulong *f, const ulong *g, ulong n)
{
    bool q = 1;
    for (ulong k=0; k<n; ++k)  q &= (f[k]==g[k]);
    return q;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements.");

    perm_lex P(n);
//    perm_trotter P(n);
    const ulong *x = P.data();

    bitarray B(n);

    ulong *t = new ulong[n];  // aux
    ulong *c = new ulong[n];  // aux

    ulong ct = 0;
    do
    {
        ccf2perm(x, n, t, &B);
        perm2ccf(x, n, c, &B);
#ifndef TIMING
        const bool dfz= true;  // whether to print dots for zeros
        cout << setw(4) << ct << ":";
        print_perm("    ", x, n, dfz);  // x[] as array form
        print_ccf("    ", x, n, &B);    // x[] read as CCF
        print_perm("    ", t, n, dfz);  // x[] as CCF converted to array form
        print_ccf("    ", c, n, &B);    // x[] (as array form) converted to CCF
        cout << endl;
#endif
        ++ct;

        // testing:
        ccf2perm(x, n, t, &B);
        perm2ccf(t, n, c, &B);
        jjassert( same_q( c, x, n) );
        perm2ccf(x, n, c, &B);
        ccf2perm(c, n, t, &B);
        jjassert( same_q( t, x, n) );
    }
    while ( P.next() );


    delete [] t;
    delete [] c;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/ccf2perm-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/ccf2perm-demo.cc DEMOFLAGS=-DTIMING"
/// End:

