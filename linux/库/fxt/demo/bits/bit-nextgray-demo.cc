
#include "bits/nextgray.h"
#include "bits/graycode.h"

#include "bits/print-bin.h"
#include "fxtio.h"
#include "fxttypes.h"  // ulong
#include "jjassert.h"

#include "nextarg.h"


//% Gray increment/counter.


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Bits in words");
    ulong pn = n + 1;

    ulong n2 = 1UL<<n;
    ulong x = 0;
    for (ulong k=0; k<n2; ++k)
    {
        cout << setw(4) << k;
        print_bin("  ", k , pn);

        print_bin("  ", x , pn);

        ulong g = x>>1;
        print_bin("  ", g , pn);
        x = next_gray2(x);
        cout << endl;

        jjassert( g == gray_code(k) );
    }


    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bit-nextgray-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bit-nextgray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

