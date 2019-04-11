
#include "bits/radix-2i.h"
#include "bits/radix-m4.h"
#include "bits/bitzip-pairs.h"

#include "fxttypes.h"  // ulong
#include "bits/bitsperlong.h"

#include "fxtio.h"
#include "nextarg.h"

//% OEIS sequence A177505:
//% Base 2i representation of n reinterpreted in base 4.

// Cf. seq/A212494-demo.cc
// Cf. bits/radix-2i-demo.cc

int
main(int argc, char **argv)
{
    ulong n = 32;
    NXARG(n, "Convert numbers 0,1,2,...,n");
    bool nq = false;
    NXARG(nq, "Whether to convert numbers 0,-1,-2,...,-n");

    for (ulong s=0; s<=n; ++s)
    {
        const ulong k = ( nq ? -s : +s);

        ulong qi = bin_real_to_rad2i(k);
        qi >>= 2;  // note: lowest digit suppressed with purely real numbers

        cout << s;
        cout << " " << qi;

        cout << endl;
    }
//    cout << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A177505-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A177505-demo.cc DEMOFLAGS=-DTIMING"
/// End:
