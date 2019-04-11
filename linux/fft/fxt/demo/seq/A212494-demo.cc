
#include "bits/radix-2i.h"
#include "bits/radix-m4.h"
#include "bits/bitzip-pairs.h"
#include "aux1/num2str.h"  // num2str()

#include "fxttypes.h"  // ulong
#include "bits/bitsperlong.h"

#include "fxtio.h"
#include "nextarg.h"

//% OEIS sequence A212494:
//% Base 2i representation of n.
//% Also A212542: base 2i representation of negative numbers.

// Cf. seq/A177505-demo.cc for base 2i representation of n reinterpreted in base 4
// Cf. bits/radix-2i-demo.cc for purely real and imaginary numbers in radix(2*i).


int
main(int argc, char **argv)
{
    ulong n = 44;
    NXARG(n, "Convert numbers 0,1,2,...,n");
    bool nq = false;
    NXARG(nq, "Whether to convert numbers 0,-1,-2,...,-n");
    char str[32];  // for radix conversion

    for (ulong s=0; s<=n; ++s)
    {
        const ulong k = ( nq ? -s : +s);

        ulong qi = bin_real_to_rad2i(k);
        qi >>= 2;  // note: lowest digit suppressed with purely real numbers

        cout << s;
        // cout << " " << qi;  // A177505
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
/// make-target: "1demo DSRC=demo/seq/A212494-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A212494-demo.cc DEMOFLAGS=-DTIMING"
/// End:
