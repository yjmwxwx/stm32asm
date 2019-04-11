
#include "bits/graycode.h"
#include "bits/parity.h"

#include "bits/bitcount.h"

#include "bits/print-bin.h"
#include "fxttypes.h"

#include "fxtio.h"

#include "nextarg.h"

//% Demo of the binary Gray code.

int
main(int argc, char **argv)
{
    ulong n = 64;
    NXARG(n, "List extends up to n-1 (n<=256)");

    cout << "      v             gray_code(v)    bits/sorted   inverse_gray_code(v)/parity(v)"
         << endl;

    for (ulong v=0; v<n; ++v)
    {
        print_bin("", v, 8);
        cout << " = ";
        cout << setw(3) << v;
        cout << "     ";

        ulong g = gray_code(v);
        cout << setw(3) << g;
        cout << " = ";
        print_bin("", g, 8);
        cout << "     ";

        ulong bc = (1UL<<bit_count(g))-1;
        print_bin("", bc, 8);
        cout << "     ";

        ulong i = inverse_gray_code(v);
        print_bin("", i, 8);
        cout << " = ";
        cout << setw(3) << i;

        cout << "      P= ";
        cout << parity(v);
        cout << endl;
    }

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/graycode-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/graycode-demo.cc DEMOFLAGS=-DTIMING"
/// End:

