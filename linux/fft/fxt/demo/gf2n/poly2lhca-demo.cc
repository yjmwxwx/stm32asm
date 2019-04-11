
// demo-include "bpol/bitpol2lhca.cc"
#include "bpol/bitpolmod-solvequadratic.h"
#include "bpol/lhca.h"

//#include "bpol/bitpol-arith.h"
#include "bpol/bitpol-degree.h"
//#include "bpol/bitpol-deriv.h"
//#include "bpol/bitpol-modarith.h"
#include "bpol/bitpol-print.h"

#include "fxtio.h"
#include "bits/print-bin.h"
#include "nextarg.h"
#include "fxttypes.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()


//% Computation of the LHCA rule corresponding to an irreducible binary polynomial.

int
main(int argc, char **argv)
{
    const ulong e = 1;
//    ulong c = (e<<5) | (e<<2) | (e<<0);
    ulong c = (e<<20) | (e<<3) | (e<<0);
//    ulong c = (e<<40) | (e<<21) | (e<<19) |  (e<<2) |  (e<<0);
//    ulong c = (e<<60) | (e<<1) | (e<<0);

//    ulong c = (e<<18) | (e<<9) | (e<<0);
//    ulong c = (e<<6) | (e<<3) | (e<<0);
//    ulong c = (e<<19) - 1;  // full poly

    RESTARGS("Optionally supply nonzero coefficients of polynomial");
    if ( argc>1 )
    {
        c = 0;
        for (ulong j=1; j<(ulong)argc; ++j)  c |= (e << strtoul(argv[j], 0, 10));
    }



    ulong n = bitpol_deg(c);

    bitpol_print_bin("  c=", c);
    cout << endl;

    ulong r = poly2lhca(c);  // r==0 ==> no rule exists
    print_bin("   r=", r, n);
    cout << endl;

    if ( r )
    {
        ulong t = lhca2poly(r, n);
        if ( t!=c )  // will happen for reducible polynomials
        {
            print_bin("  t=", t, n+1);
            cout << endl;
            jjassert( t==c );
        }
    }

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/poly2lhca-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/poly2lhca-demo.cc DEMOFLAGS=-DTIMING"
/// End:

