
#include "comb/subset-monotone.h"

#include "comb/comb-print.h"
#include "fxttypes.h"

#include "fxtio.h"
#include "comb/comb-print.h"
#include "nextarg.h"


//% Generate all subsets in monotone order.

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Size of the set");

    subset_monotone so(n);
    const ulong *x = so.data();

    ulong idx = 0;
    ulong num;
    do
    {
        num = so.next();
        ++idx;
        cout << setw(2) << idx << ":  ";

        // print as bit set:
        for (ulong k=0; k<n; ++k)  cout << (x[k]?'1':'.');  // << " ";
        cout << "   #=" << num;

        // print as set:
        print_deltaset_as_set("   set=", x, n);

        cout << endl;
    }
    while ( num );

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/subset-monotone-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/subset-monotone-demo.cc DEMOFLAGS=-DTIMING"
/// End:

