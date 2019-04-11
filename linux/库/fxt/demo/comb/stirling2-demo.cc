
// demo-is-self-contained

#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"

//% Stirling numbers of the second kind (set numbers) and Bell numbers.


int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "Compute first n rows");

    ulong *s = new ulong[n+1];
    for (ulong k=0; k<n; ++k)  s[k] = 0;
    s[0] = 1;

    for (ulong k=1; k<=n; ++k)
    {
        cout << setw(3) << k << ":  ";
        ulong b = 0;
        for (ulong j=0; j<k; ++j)  b += s[j];  // B(k)

        cout << "  b=" << setw(8) << b << "   ";
        for (ulong j=0; j<k; ++j)   cout << setw(5) << s[j] << " ";
        cout << endl;

        // next k:
        for (ulong j=k; j!=0; --j)  s[j] = (j+1)*s[j] + s[j-1];
    }
    cout << endl;

    delete [] s;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/stirling2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/stirling2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

