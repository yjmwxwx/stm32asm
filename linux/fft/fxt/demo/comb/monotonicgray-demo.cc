
#include "comb/monotonic-gray.h"
//demo-include "comb/monotonic-gray.cc"

#include "bits/print-bin.h"
#include "bits/bitcount.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "jjassert.h"

#include "nextarg.h"

//% Monotonic Gray path (Savage/Winkler), as given by Knuth.


int
main(int argc, char **argv)
{
    ulong ldn = 6;
    NXARG(ldn, "Use ldn-bit words");

    const ulong n = 1UL << ldn;
    ulong *g = new ulong[n];

    monotonic_gray(g, ldn);

#if 1  // print path:
    const ulong pd = ldn;
    for (ulong k=0; k<n; ++k)
    {
        cout << setw(4) << k << ":  ";
        print_bin(" ", g[k], pd);
        cout << setw(3) << bit_count(g[k]);
        if ( 0!=k )  print_bin("    ", g[k]^g[k-1], pd);
        cout << endl;
    }

#else  // test:

    // check that the path is monotonic:
    ulong bc1 = 0;
    for (ulong k=1; k<n; ++k)  // done for n<=30
    {
        ulong bc0 = bit_count(g[k]);
        jjassert( bc1 <= bc0 + 1 );
        bc1 = bc0;
    }

#endif

    delete [] g;
    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/monotonicgray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/monotonicgray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

