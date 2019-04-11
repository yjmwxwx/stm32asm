
#include "bits/bit-paper-fold.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong


//% Moves of the dragon curve: +==right, -==left, ^==up, v==down

int
main(int argc, char **argv)
{
    ulong n = 65;
    NXARG(n, "Number of bits generated");

//    cout << 0;
    for (ulong k=0; k<=n; ++k)
    {
        ulong m = bit_dragon_rot(k);
//        cout << m << ", ";
        cout << ("+^-v")[m];
    }
    cout << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/dragon-curve-moves-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/dragon-curve-moves-demo.cc DEMOFLAGS=-DTIMING"
/// End:

