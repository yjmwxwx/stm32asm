
// demo-is-self-contained

#include "bits/bitxtransforms.h"

#include "bits/print-bin.h"
#include "bits/revbin.h"
#include "fxtio.h"
#include "fxttypes.h"
#include "bits/bitsperlong.h"

#include "nextarg.h"  // NXARG()

#include "jjassert.h"

//% Matrices corresponding to symbolic powers of the 'color' transforms.

// Output dependent on BITS_PER_LONG

int
main(int argc, char **argv)
{
    ulong x = 13;
    NXARG(x, "Exponent of transform");
    ulong t = 1;
    NXARG(t, "Type of transform: 0==>Blue 1==>Yellow, 2==>Red, 3==>Green");
    t %= 4;

    ulong pn = BITS_PER_LONG;
    for (ulong z=1, k=0;  k<pn;  ++k, z<<=1)
    {
        ulong a = z;
        switch ( t )
        {
        case 0:  a = blue_xcode(a, x);  break;
        case 1:  a = yellow_xcode(a, x);  break;
        case 2:  a = red_xcode(a, x);  break;
        case 3:  a = green_xcode(a, x);  break;
        }
        a = revbin(a);  // so identity == diagonal
        print_bin("  ", a , 0);
        cout << endl;
    }
    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitxtransforms-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitxtransforms-demo.cc DEMOFLAGS=-DTIMING"
/// End:

