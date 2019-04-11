
#include "comb/composition-nz.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A062200:
//% Compositions of n where adjacent parts have different parity.

// Cf. comb/composition-nz-demo.cc for compositions into nonzero parts.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "compositions of n");

    composition_nz P(n);

    ulong ct = 0;
    const ulong *x = P.data();
    ulong m = n;
    do
    {
        // adjacent parts must have different parity:
        bool q = true;
        for (ulong j = 1; j<m; ++j)
            if ( 0 == ( 1UL & (x[j]^x[j-1]) ) )  { q=false; break; }
        if ( !q )  continue;

        ++ct;

#ifndef TIMING
        cout << setw(3) << ct << ": ";
        for (ulong k=0; k<m; ++k)  cout << " " << x[k];
        cout << endl;
#endif  // TIMING
    }
    while ( (m=P.next()) );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A062200-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A062200-demo.cc DEMOFLAGS=-DTIMING"
/// End:
