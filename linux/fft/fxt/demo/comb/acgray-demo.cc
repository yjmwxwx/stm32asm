
#include "comb/acgray.h"
#include "comb/delta2gray.h"
// demo-include "comb/acgray.cc"

#include "comb/comb-print.h"

#include "nextarg.h"
#include "fxtalloca.h"  // ALLOCA
#include "fxttypes.h"  // ulong

//% Adjacent changes (AC) Gray codes for n<=6

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "size in bits");
    ulong n2 = 1UL<<n;
    //    ulong f[n2];
    ALLOCA(ulong, f, n2);

    ac_gray(f, n);
    print_gray(f, n2);
    ulong nac = test_ac_gray(f, n2);
    cout << " # non-AC transitions = " << nac << endl;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/acgray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/acgray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

