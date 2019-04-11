
#include "bpol/bitpol-factor.h"
// demo-include "bpol/berlekamp.cc"
#include "bmat/bitmat-funcs.h"
#include "bmat/bitmat-inline.h"

#include "bpol/bitpol-print.h"
#include "bpol/bitpol-degree.h"
#include "bits/print-bin.h"

#include "fxtalloca.h"

#include "fxttypes.h"  // ulong
#include "nextarg.h"

//% Q-matrix and nullspace of (Q-id).

int
main(int argc, char **argv)
{
    ulong c = 131;
    NXARG(c, "Polynomial (as number)");

    ulong d = bitpol_deg(c);
    ALLOCA(ulong, ss, d);
    ALLOCA(ulong, nn, d);
    setup_q_matrix(c, d, ss);

    bitpol_print("c=", c);
    print_bin(" = ", c, d+1);
    cout << endl;
    cout << endl;
//    bitpol_print("c=", c, 1);    cout << endl;

    bitmat_print("   Q=", ss, d);
    bitmat_add_unit(ss, d);
    bitmat_print("   Q-id=", ss, d);

    ulong r = bitmat_nullspace(ss, d, nn);
    bitmat_print("nullspace=", nn, d, r);

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/qmatrix-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/qmatrix-demo.cc DEMOFLAGS=-DTIMING"
/// End:

