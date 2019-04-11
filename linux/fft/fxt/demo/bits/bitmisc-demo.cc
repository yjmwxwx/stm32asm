
#include "bits/bitswap.h"
#include "bits/zerobyte.h"
#include "bits/bit-isolate.h"
#include "bits/bitcount.h"

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


//    SHWBIN( revbin );

    SHWBIN( single_ones );
    SHWBIN( single_zeros );
    SHWBIN( single_zeros_xi );
    SHWBIN( single_values );
    SHWBIN( single_values_xi );

    SHWBIN( border_ones );
    SHWBIN( border_values );
    SHWBIN( high_border_ones );
    SHWBIN( low_border_ones );
    SHWBIN( block_border_ones );
    SHWBIN( low_block_border_ones );
    SHWBIN( high_block_border_ones );

    SHWBIN( block_ones );
    SHWBIN( block_values );
    SHWBIN( interior_ones );
    SHWBIN( interior_values );

    SHWBIN( contains_zero_byte );

    SHWDEC( bit_count );
//    SHWDEC( bit_count_sparse );  // same result as bit-count()
    SHWDEC( bit_block_count );
    SHWDEC( bit_block_ge2_count );

//    SHWDEC( 0!=contains_zero_byte );


    cout << endl;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitmisc-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitmisc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

