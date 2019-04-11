
#include "sort/symbolify.h"

#include "fxtio.h"
#include "fxttypes.h"


//% Symbolify floating point values.


void print4(const char *bla, const double *f, ulong n)
{
    if ( bla )  cout << bla << ":" << endl;
    cout << setprecision(7);
    for (ulong k=0; k<n; ++k)
    {
        cout << setw(10) << f[k];
        if ( k%4==3 )  cout << endl;
    }
    cout << endl;
}
// -------------------------


int
main()
{
    double f[] = {
        1.3133,     -1.0101,     0.79412,     -0.71544,
        0.29064,     0.99173,   -1.4382,       0.79412,
       -1.1086,      1.2521,     0.99173,     -1.0101,
       -0.18003,    -1.1086,     0.29064,      1.3133 };
    ulong n = 16;

    print4("Input", f, n);
    double eps = 1e-4;
    double g[16];

    symbolify_by_size(f, g, n, eps);
    print4("Symbols by size", g, n);

    symbolify_by_order(f, g, n, eps);
    print4("Symbols by order", g, n);

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/sort"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/sort/symbolify-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/symbolify-demo.cc DEMOFLAGS=-DTIMING"
/// End:

