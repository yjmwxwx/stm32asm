
#include "bits/bit-necklace.h"
#include "bits/bitrotate.h"
#include "bits/bitcount.h"

#include "fxtio.h"
#include "fxttypes.h"  // ulong

#include "bits/bitsperlong.h"
#include "jjassert.h"

#include "nextarg.h"  // NXARG()

#include "bits/print-bin.h"
//#include "bits/bitcount.h"


//% OEIS sequence A226893:
//% Number of binary Lyndon words of length n having a conjugate at Hamming distance 2.

// Cf. bits/bit-necklace-demo.cc


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Number of bits 0<n<=BITS_PER_LONG");
    jjassert( n>0 );
    jjassert( n<=BITS_PER_LONG );

    bit_necklace N(n);

    ulong ct = 0;  // count necklaces (prime strings)

    do
    {
        if ( N.is_lyndon_word() )
        {
            const ulong w = N.data();
            ulong wr;
            bool q = false;
            for (ulong r=1; r<n; ++r)
            {
                wr =  bit_rotate_right(w, r, n);
                if ( 2 == bit_count( w ^ wr ) )
                {
                    q = true;
                    break;
                }
            }

            if ( q )
            {
                ++ct;

#ifndef TIMING
                cout << setw(4) << ct << ": ";
                print_bin("  ", w, n);
                print_bin("  ", wr, n);
                print_bin("  ", w^wr, n);
//                cout << "  " << setw(2) << N.period();
                cout << endl;
#endif  // TIMING

            }
        }
    }
    while ( N.next() );

    cout << " ct=" << ct << endl;


    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A226893-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A226893-demo.cc DEMOFLAGS=-DTIMING"
/// End:

