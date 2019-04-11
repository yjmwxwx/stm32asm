
// demo-is-self-contained

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"

//% Catalan numbers and ballot numbers.
//% Cf. OEIS sequences A009766 (Catalan's triangle) and A033184.

int
main(int argc, char **argv)
{
    ulong N = 11;
    NXARG(N, "Show N rows");

    ulong *c = new ulong[N+1];

#if 0  // A009766

    c[0] = 1;
    for (ulong k=1; k<=N; ++k)  c[k] = 0;

    for (ulong n=0; n<N; ++n)
    {
        for (ulong k=1; k<=n; ++k)  c[k] += c[k-1];

        cout << setw(2) << n << ":";
        for (ulong k=0; k<=n; ++k)  cout << " " << setw(6) << c[k];
        cout << endl;
    }

#else  // A033184

    c[0] = 1;
    for (ulong k=1; k<=N; ++k)  c[k] = 0;

    for (ulong n=0; n<N; ++n)
    {
        cout << setw(2) << n << ":";
        for (ulong k=0; k<=n; ++k)  cout << " " << setw(6) << c[k];
        cout << endl;

        ulong s = 0;  // partial sum
        ulong k = n+1;
        do
        {
            s += c[k-1];
            c[k] = s;
        }
        while ( --k );
//        c[0] = 0;  // show column 0
        c[0] = c[1] ;
//        c[0] = c[1] - 1;  // A114277
//        c[0] = c[1] + 1;  // A014137
    }
#endif

    delete [] c;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-number-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-number-demo.cc DEMOFLAGS=-DTIMING"
/// End:

