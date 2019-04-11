
// demo-is-self-contained

#include "bits/print-bin.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Recursive algorithm for the bit-reversed binary words in order.

ulong ldn;
ulong N, ct;
void revbin_rec(ulong f, ulong n)
{
    print_bin("  ", ct, ldn);
    print_bin("  ", f, ldn);
    cout << endl;
    ++ct;
    for (ulong m=N>>1; m>n; m>>=1)  revbin_rec(f+m, m);
}
// -------------------------

int
main(int argc, char **argv)
{
    ldn = 5;
    NXARG(ldn, "Number of bits");
    N = 1UL<<ldn;
    ct = 0;

    revbin_rec(0, 0);

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/revbin-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/revbin-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

