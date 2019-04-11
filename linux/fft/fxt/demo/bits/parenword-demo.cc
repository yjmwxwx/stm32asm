
#include "bits/parenwords.h"  // is_parenword(), parenword2str()

#include "bits/print-bin.h"  // print_bin()
#include "bits/graycode.h"  // gray_code()

#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"  // ulong
#include "nextarg.h"

//% Binary words that are "parentheses words".
//% Cf. OEIS sequence A036991.

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Scan words 0 ... 2^n-1");
    ulong n2 = 1UL<<n;

    ulong pwo = 0;
    NXARG(pwo, "Whether to print only parentheses words");
    ulong pn = n;
    char *str = new char[n2+1];  str[n2] = 0;

    ulong gcq = 0;
    NXARG(pwo, "Whether to scan words in Gray code order");

    ulong pct = 0;
    for (ulong k=0; k<n2; ++k)
    {
        ulong g;
        if ( gcq )  g = gray_code(k);
        else        g = k;

        bool vp = is_parenword(g);

        if ( pwo && (!vp) )  continue;

        print_bin("  ", g, pn);
//        print_bin("  ", inverse_gray_code(g), pn);
        if ( vp )
        {
            ++pct;
            cout << " P";
            parenword2str(g, str);
            cout << "   " << str;
        }
        cout << endl;
    }
    cout << "  pct=" << pct << endl;
    cout << endl;

    delete [] str;

    return 0;
}
// -------------------------

// parenwords < 256 (OEIS sequence A036991):
// 0, 1, 3, 5, 7, 11, 13, 15, 19, 21, 23, 27, 29, 31, 39, 43, 45, 47,
// 51, 53, 55, 59, 61, 63, 71, 75, 77, 79, 83, 85, 87, 91, 93, 95, 103,
// 107, 109, 111, 115, 117, 119, 123, 125, 127, 143, 151, 155, 157, 159,
// 167, 171, 173, 175, 179, 181, 183, 187, 189, 191, 199, 203, 205, 207,
// 211, 213, 215, 219, 221, 223, 231, 235, 237, 239, 243, 245, 247, 251,
// 253, 255

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/parenword-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/parenword-demo.cc DEMOFLAGS=-DTIMING"
/// End:

