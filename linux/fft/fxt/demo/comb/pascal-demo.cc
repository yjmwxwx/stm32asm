
// demo-is-self-contained

#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"

//% Pascal triangle.
//% Cf. OEIS sequence A007318.

int
main(int argc, char **argv)
{
    ulong n = 15;
    NXARG(n, "Compute first n rows");

    ulong *p = new ulong[n];
    for (ulong k=0; k<n; ++k)  p[k] = 0;
    p[0] = 1;

    for (ulong k=0; k<n; ++k)
    {
        cout << setw(3) << k << ":  ";

        ulong s = 0;
        for (ulong j=0; j<k; ++j)  s += p[j];  // S(k) = 2^k
        cout << "  s=" << setw(5) << s << "   ";

        for (ulong j=0; j<k; ++j)   cout << setw(4) << p[j] << " ";
        cout << endl;

        // next k:
        for (ulong j=k; j!=0; --j)  p[j] = p[j] + p[j-1];
    }
    cout << endl;

    delete [] p;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/pascal-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/pascal-demo.cc DEMOFLAGS=-DTIMING"
/// End:

