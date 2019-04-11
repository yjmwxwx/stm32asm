
// demo-is-self-contained

#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"

//% Number of integer partitions.


int
main(int argc, char **argv)
{
    ulong n = 17;
    NXARG(n, "Compute first n rows (n<=416)");
    if ( n>416 )  n = 416;
    ++n;

    bool tq = false;
    NXARG(tq, "Option: whether to only show totals");


    uint64 *x = new uint64[n*n];
    uint64 **p = new uint64*[n];
    for (ulong k=0; k<n; ++k)  p[k] = x + (k*n);
    for (ulong k=0; k<n*n; ++k)  x[k] = 0;
    p[0][0] = 1;

    for (ulong k=1; k<n; ++k)
    {
        cout << setw(3) << k << ":  ";
        // p[N][M] == numpart of N with max summand M
        //         == numpart of N into M parts

        // next k:
        for (ulong j=1; j<=k; ++j)  p[k][j] = p[k-1][j-1] + p[k-j][j];

        uint64 s = 0;
        for (ulong j=1; j<=k; ++j)  s += p[k][j];  // S(k) = numpart(n)
        cout << "  s=" << setw(4) << s << "   ";

        if ( !tq ) for (ulong j=1; j<=k; ++j)   cout << setw(3) << p[k][j] << " ";
        cout << endl;
    }
    cout << endl;

    delete [] x;
    delete [] p;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/num-partitions-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/num-partitions-demo.cc DEMOFLAGS=-DTIMING"
/// End:

