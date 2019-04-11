
// demo-is-self-contained

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"

//% Aitken's array and Bell numbers.
//% Cf. OEIS sequence A011971: Aitken's array,
//% also called Bell triangle or Peirce triangle.

int
main(int argc, char **argv)
{
    ulong N = 11;
    NXARG(N, "Show N rows");

    ulong *b = new ulong[N+1];
    b[0] = 1;

    for (ulong n=0; n<N; ++n)
    {
        cout << setw(2) << n << ":  ";
        for (ulong k=0; k<=n; ++k)  cout << " " << setw(6) << b[k];
        cout << endl;

        ulong t = b[0];
        b[0] = b[n];
        for (ulong k=1; k<=n+1; ++k)
        {
            ulong y = b[k-1] + t;
            t = b[k];
            b[k] = y;
        }
    }

    delete [] b;
    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/bell-number-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/bell-number-demo.cc DEMOFLAGS=-DTIMING"
/// End:

