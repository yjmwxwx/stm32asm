
#include "comb/composition-nz-carlitz.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A218694:
//% Compositions of n where adjacent parts are distinct (Carlitz compositions)
//% and all parts are odd.

// Cf. comb/composition-nz-carlitz-demo.cc for all carlitz compositions.
// Cf. comb/composition-nz-demo.cc for compositions into nonzero parts.
// Cf. seq/A062200-demo.cc for compositions where adjacent parts have different parity.


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 15;
    NXARG(n, "Carlitz compositions of n into odd parts");

    composition_nz_carlitz P(n);

    ulong ct = 0;
    const ulong *x = P.data();
    ulong m = P.num_parts();
    do
    {
#if 1
        bool q = true;
        for (ulong j = 0; j<m; ++j)  // only odd parts
            if ( 0 == (x[j] & 1UL) )  { q=false; break; }
        if ( !q )  continue;
#endif

        ++ct;

#ifndef TIMING
        cout << setw(3) << ct << ": ";
//        cout << " [" << m << "]  ";
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
/// make-target: "1demo DSRC=demo/seq/A218694-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A218694-demo.cc DEMOFLAGS=-DTIMING"
/// End:
