
// demo-is-self-contained

#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"

//% Stirling numbers of the first kind (Stirling cycle numbers).


int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Compute first n rows");
    ++n;

    ulong *s = new ulong[n+1];
    for (ulong k=0; k<n; ++k)  s[k] = 0;
    s[1] = 1;

    cout << endl;
    ulong k=1;
    while ( k<n )
    {
        cout << setw(3) << k << ":  ";

        ulong b = 0;
        for (ulong j=0; j<=k; ++j)  b += s[j];  // b==k!
        cout << "  b=" << setw(8) << b << "   ";

        for (ulong j=1; j<=k; ++j)   cout << setw(6) << s[j] << " ";
        cout << endl;

        // next k:
        ++k;   // here k==n in last step!
//        for (ulong j=k; j>0; --j)  s[j] = (k-1)*s[j-1] + s[j];
        for (ulong j=k; j>0; --j)  s[j] = s[j-1] + (k-1)*s[j];
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
/// make-target: "1demo DSRC=demo/comb/stirling1-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/stirling1-demo.cc DEMOFLAGS=-DTIMING"
/// End:

