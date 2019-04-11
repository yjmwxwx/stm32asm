
#include "bits/bin2naf.h"  // for naf2bin()
#include "bits/print-bin.h"
// demo-include "bits/print-bindiff.cc"

#include "bits/bit2pow.h"
#include "aux0/swap.h"

#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"


#include "nextarg.h"  // NXARG()


//% Signed binary representation (not a nonadjacent form in general).

int
main(int argc, char **argv)
{
    ulong n = 32;
    NXARG(n, "Max");
    ulong pn = ld(n)+2;
    ulong n0 = 0;
    NXARG(n0, "Min");
    if ( n0>n )  swap2(n, n0);

    bool q = 1;
    NXARG(q, "Whether to print sum");

    for (ulong k=n0; k<=n; ++k)
    {
        ulong x = k;
        cout << setw(3) << x << ":";
        print_bin("    ", x, pn);

        ulong np, nm;
//        bin2naf(x, np, nm);
        bin2sbin(x, np, nm);
//        print_bin("    ", np, pn);
//        print_bin("    ", nm, pn);
        print_bin_diff("    ", nm, np, pn, "..PM");

        if ( q )
        {
            cout << "    " << setw(3) << x << " = ";
            ulong xp = np, xm = nm;
            while ( xm|xp )
            {
                ulong m = highest_one(xm|xp);
                cout << ' ' << (m&xp?'+':'-') << m;
                xm &= ~m;  xp &= ~m;
                m >>= 1;
            }
        }

        cout << endl;

        jjassert( naf2bin(np, nm)==x );
    }

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bin2sbin-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bin2sbin-demo.cc DEMOFLAGS=-DTIMING"
/// End:

