

#include "bits/grsnegative.h"
#include "bits/parity.h"

#include "bits/print-bin.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% The Golay-Rudin-Shapiro (GRS) sequence.


int
main(int argc, char **argv)
{
    ulong n =5;
    NXARG(n, "Number of bits");

    ulong nn = 1UL << n;
    const ulong pd = n + 2;
    const int pdi = (int)n + 2;

    cout << setw(4) << "k" << ":  ";
    cout << setw(pdi+4) << "bin(k) ";
    cout << "  GRS(k) ";
    cout << setw(pdi+4) << "k&(k>>1) ";
    cout << setw(pdi+4) << "inverse_gray(k&(k>>1)) ";
    cout << endl;

    for (ulong k=0; k<nn; ++k)
    {
        const ulong ka = k & (k>>1);
        cout << setw(4) << k << ":  ";
        print_bin("    ", k, pd);
        cout << "    " << grs_negative_q(k) << " ";
        print_bin("     ", ka, pd);
        print_bin("     ", inverse_gray_code(ka) , pd);

        cout << endl;
    }

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/grs-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/grs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

