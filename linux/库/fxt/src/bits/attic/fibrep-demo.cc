

#include "bits/fibrep.h"

#include "bits/print-bin.h"  // print_bin()
#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "jjassert.h"


//% Find Fibonacci words via exhaustive search.

int
main(int argc, char **argv)
{
    ulong nb = 7;
    NXARG(nb, "Max number of bits");

    ulong m = (1UL<<nb);
    ulong ct = 0;
    for (ulong k=0; k<m; ++k)
    {
        if ( is_fibrep(k) )
        {
            ++ct;
            cout << setw(4) << k << ": ";
            print_bin(" ", k, nb);
            cout << "  " << setw(4) << fibrep2bin(k);
            cout << endl;
        }
    }
    cout << "ct=" << ct << endl;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/fibrep-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/fibrep-demo.cc DEMOFLAGS=-DTIMING"
/// End:

