
#include "bits/revbin.h"
#include "bits/bitswap.h"
#include "bits/graycode.h"
#include "bits/revgraycode.h"
#include "bits/bitsequency.h"
#include "bits/bitrotate.h"
#include "bits/bitcyclic-minmax.h"

#include "./bitdemos.h"  // ugly, very ugly (just for the demo)

#include "fxttypes.h"
//#include "bits/bitsperlong.h"

//% Miscellaneous operations on binary words.

// Output dependent on BITS_PER_LONG

void
do_the_show(ulong v)
{
    ulong t;

    print_sep();

    WORD;

    SHWBIN( revbin );

    SHWBIN( gray_code );
    SHWBIN( inverse_gray_code );
    SHWBIN( rev_gray_code );
    SHWBIN( inverse_rev_gray_code );

    SHWBIN( bit_swap_4 );
    SHWBIN( bit_swap_8 );

    SHWBIN2( bit_rotate_right, 3 );

    SHWBIN( next_sequency );

    SHWBIN( bit_cyclic_min );
    SHWBIN( bit_cyclic_max );

    cout << endl;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitmisc2-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitmisc2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

