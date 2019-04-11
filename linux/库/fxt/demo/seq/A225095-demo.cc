
#include "comb/mixedradix-lex.h"

#include "jjassert.h"
#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

//% OEIS sequence A225095:
//% Number of maximums over all length-n sequences on {1,2,...,n}.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "length of strings.");
    ulong m = n;
    NXARG(m, "number of letters (radix, >=2).");

    mixedradix_lex M(n, m);
    const ulong *x = M.data();

    ulong mct = 0;
    ulong ct = 0;
    do
    {
        ++ct;
        ulong c = 1;
        for (ulong j=1,mx=x[0]; j<n; ++j)
        {
            if ( x[j] > mx )
            {
                mx = x[j];
                c += 1;
            }
        }
        mct += c;
#ifndef TIMING
        cout << setw(4) << ct << ":";
        M.print("  ", false);
        cout << setw(4) << c;
        cout << endl;
#endif  // TIMING
    }
    while ( M.next() );

    cout << "mct=" << mct << endl;

    return 0;
}
// -------------------------

/*
for n in $(seq 1 10); do ./bin $n $n | g mct=; done
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A225095-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A225095-demo.cc DEMOFLAGS=-DTIMING"
/// End:
