

#include "aux0/binomial.h"

#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"


//% Print the Pascal triangle (binomial coefficients).

int
main(int argc, char **argv)
{
    ulong n = 15;
    NXARG(n, "Compute first n rows of Pascal's triangle");
    ++n;

    cout << "      ";
    for (ulong j=0; j<n; ++j)   cout << setw(4) << j << " ";
    cout << endl;
    for (ulong k=0; k<n; ++k)
    {
        cout << setw(3) << k << ":  ";
        for (ulong j=0; j<=k; ++j)   cout << setw(4) << binomial(k, j) << " ";
        cout << endl;
    }
    cout << endl;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/binomial-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/binomial-demo.cc DEMOFLAGS=-DTIMING"
/// End:

