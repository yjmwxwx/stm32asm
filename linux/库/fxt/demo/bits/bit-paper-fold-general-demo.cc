
#include "bits/bit-paper-fold.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "jjassert.h"


//% Generate (a general) paper-folding sequence.


int
main(int argc, char **argv)
{
    ulong n = 65;
    NXARG(n, "Number of bits generated");
    ulong w = 0;
    NXARG(w, "Word whose bits encode the direction of the folds");

    for (ulong k=1; k<=n; ++k)  // note start with k==1
    {
        bool p = bit_paper_fold_general(k, w);
        cout << (p==0 ? '.' : '1' );
//        cout << (p==0 ? '0' : '1' ) << ", ";


        jjassert( bit_dragon_rot(k) == bit_paper_fold_general_rot(k, 0UL) );
        jjassert( bit_paper_fold_alt_rot(k) == bit_paper_fold_general_rot(k, 0xaaaaaaaa) );
        jjassert( 0 == (bit_paper_fold_general_rot(k, w) + bit_paper_fold_general_rot(k, ~w)) % 4 );
    }
    cout << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bit-paper-fold-general-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bit-paper-fold-general-demo.cc DEMOFLAGS=-DTIMING"
/// End:

