
#include "perm/permapplyfunc.h"
#include "perm/graypermute.h"
#include "bits/graycode.h"
#include "aux1/copy.h"  // set_seq()

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "fxtio.h"
#include "fxtalloca.h"


//% Demo of apply_permutation(func, ...).

int
main(int argc, char **argv)
{
    ulong n = 16;
    NXARG(n, "size of sequence (a power of 2)");
    if ( n<2 )  n = 2;

    ALLOCA(ulong, f, n);
    ALLOCA(ulong, g, n);

    set_seq(f, n);
    set_seq(g, n);
    apply_permutation(gray_code, f, n);
//    apply_inverse_permutation(inverse_gray_code, f, n);  // same effect
    gray_permute(g, n);

    for (ulong k=0; k<n; ++k)
    {
        cout << setw(3) << k << ":";
        cout << setw(3) << f[k] << " ";
        cout << setw(3) << g[k];
        cout << endl;
    }
    cout << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/permfunc-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/permfunc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

