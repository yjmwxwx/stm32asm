
#include "bits/negbin.h"
#include "aux1/num2str.h"  // num2str()

#include "fxttypes.h"  // ulong

#include "fxtio.h"
#include "nextarg.h"

//% OEIS sequence A005351:
//% Base -2 representation for n reinterpreted as binary.
//% Also sequence A005352:
//% Base -2 representation of -n reinterpreted as binary.

// Cf. seq/A039724-demo.cc
// Cf. seq/A007608-demo.cc


int
main(int argc, char **argv)
{
    ulong n = 66;
    NXARG(n, "Convert numbers 0,1,2,...,n");
    bool nq = false;
    NXARG(nq, "Whether to convert numbers 0,-1,-2,...,-n");  // A005352

    for (ulong s=0; s<=n; ++s)
    {
        const ulong k = ( nq ? -s : +s );
        ulong x = bin2neg(k);

        cout << x << ", ";
//        cout << s << " " << x << endl;  // b-file
    }
    cout << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A005351-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A005351-demo.cc DEMOFLAGS=-DTIMING"
/// End:
