
#include "bits/hilbert.h"  // hilbert_gray_code()

#include "bits/print-bin.h"

#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

//#include "jjassert.h"

//% Gray code from Hilbert curve



int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Number of bits");
    const ulong N = 1UL << n;

    for (ulong t=0; t<N; ++t)
    {
        cout << setw(4) << t << ":";
        ulong hg = hilbert_gray_code(t);
        print_bin("    ", hg, n+1);
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
/// make-target: "1demo DSRC=demo/bits/hilbert-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/hilbert-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:
