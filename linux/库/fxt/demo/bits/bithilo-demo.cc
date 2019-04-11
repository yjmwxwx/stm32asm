
#include "bits/bit2pow.h"
#include "bits/bitlow.h"
#include "bits/bitlow-edge.h"
#include "bits/bithigh.h"
#include "bits/bithigh-edge.h"

#include "./bitdemos.h"  // ugly, very ugly  (just for the demo)

#include "fxttypes.h"
//#include "bits/bitsperlong.h"

//% Operations on the low and high bits of binary words.

// Output dependent on BITS_PER_LONG

void
do_the_show(ulong v)
{
    ulong t;

    print_sep();

    WORD;


    SHWBIN( highest_one );
    SHWBIN( highest_one_01edge );
    SHWBIN( highest_one_10edge );
    SHWDEC( highest_one_idx );

    SHWDEC( ld );

    SHWBIN( low_zeros );
    SHWBIN( low_ones );

    SHWBIN( lowest_one );
    SHWBIN( lowest_one_01edge );
    SHWBIN( lowest_one_10edge );
    SHWDEC( lowest_one_idx );

    SHWBIN( lowest_block );

    SHWBIN( clear_lowest_one );

    SHWBIN( lowest_zero );
    SHWBIN( set_lowest_zero );

    SHWBIN( high_ones );
    SHWBIN( high_zeros );
    SHWBIN( highest_zero );
    SHWBIN( set_highest_zero );


    cout << endl;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bithilo-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bithilo-demo.cc DEMOFLAGS=-DTIMING"
/// End:

