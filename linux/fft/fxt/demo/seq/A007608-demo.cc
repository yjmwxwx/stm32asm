
#include "bits/radix-m4.h"
#include "aux1/num2str.h"  // num2str()

#include "fxttypes.h"  // ulong

#include "fxtio.h"
#include "nextarg.h"

//% OEIS sequence A007608:
//% Numbers in base -4.
//% Also A212526: negative numbers in base -4.

// Cf. seq/A212494-demo.cc


int
main(int argc, char **argv)
{
    ulong n = 44;
    NXARG(n, "Convert numbers 0,1,2,...,n");
    bool nq = false;
    NXARG(nq, "Whether to convert numbers 0,-1,-2,...,-n");  // A212526
    char str[32];  // for radix conversion

    for (ulong s=0; s<=n; ++s)
    {
        const ulong k = ( nq ? -s : +s);

        ulong qi = bin_to_radm4(k);

        cout << s;
        num2str(qi, 4, str);
        cout << " " << str;

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
/// make-target: "1demo DSRC=demo/seq/A007608-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A007608-demo.cc DEMOFLAGS=-DTIMING"
/// End:
