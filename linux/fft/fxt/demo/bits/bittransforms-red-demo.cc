
#include "bits/bittransforms.h"

//#include "bits/graycode.h"
//#include "bits/bitlex.h"

#include "bits/bitcount.h"
#include "bits/bit2pow.h"
#include "bits/bitsperlong.h"
#include "fxttypes.h"
#include "bits/print-bin.h"

#include "nextarg.h"
#include "jjassert.h"

#include "fxtio.h"


//% Transforms of binary words that are involutions: red code and green code.

// Output dependent on BITS_PER_LONG

int
main(int argc, char **argv)
{
    ulong ldn = 5;
    NXARG(ldn, "List transforms of first 2**ldn numbers");
    ulong n = 1UL<<ldn;
    ulong pn = 32;
    NXARG(pn, "Number of bits to print, pn <= BITS_PER_LONG");
    jjassert( pn <= BITS_PER_LONG );

    for (ulong k=0; k<n;  ++k)
    {
        cout << setw(4) << k << ":";

        ulong r = red_code(k);
        r >>= (BITS_PER_LONG-pn);
        print_bin("   r=", r , pn);
        cout << " " << setw(2) << bit_count(r);

        ulong e = k;
        e = green_code(e);
        print_bin("   e=", e , pn);
        cout << " " << setw(2) << bit_count(e);

        cout << endl;
    }

    cout << endl;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bittransforms-red-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bittransforms-red-demo.cc DEMOFLAGS=-DTIMING"
/// End:

