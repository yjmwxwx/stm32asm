
#include "bits/negbin.h"
#include "aux1/num2str.h"  // num2str()

#include "fxttypes.h"  // ulong

#include "fxtio.h"
#include "nextarg.h"

//% OEIS sequence A039724:
//% Numbers in base -2.
//% Also A212529: negative numbers in base -2.

// Cf. seq/A007608-demo.cc


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
        const ulong k = ( nq ? -s : +s );

        ulong x = bin2neg(k);
        num2str(x, 2, str);

//        cout << str << ", ";
        cout << s << " " << str << endl;  // b-file
    }

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A039724-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A039724-demo.cc DEMOFLAGS=-DTIMING"
/// End:
