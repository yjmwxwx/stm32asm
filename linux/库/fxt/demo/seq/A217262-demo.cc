
#include "bits/bit-sl-gray.h"
#include "bits/bit2pow.h"  // ld()

#include "bits/print-bin.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "bits/bitsperlong.h"

#include "nextarg.h"


//% OEIS sequence A217262:
//% Delta sequence for binary words in a minimal-change order (subset-lex Gray code).

// Cf. bits/bitlex-demo.cc for subset-lex order.
// Cf. comb/binary-sl-gray-demo.cc for generation in an array.


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "n-bit binary words");
    bool eq = true;
    NXARG(eq, "whether to print words");  // else just the sequence


    bit_sl_gray G(n);
    ulong ct = 0;

    ulong xo = 1UL;
    if ( n>=2 ) xo <<= (n-2);

    bool sq = false;  // to wait for rightmost change
    do
    {
        const ulong x = G.data();
        const ulong px = ld(x^xo);  // position of change

        if ( eq )
        {
            cout  << setw(4) << ct << ":";
            ++ct;
            print_bin("    ", x, n);  // words of the Gray code
            print_bin("    ", x^xo, n);  // delta sequence
            cout << "  " << px;
            if ( (px==1) && (!sq) )  cout << " <--= sequence starts after here";
            cout << endl;
        }
        else
        {
            if ( sq )  cout << px << ", ";
        }

        if ( px==1 )  sq = true;

        xo = G.data();
    }
    while ( G.next() );

    cout << endl;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A217262-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A217262-demo.cc DEMOFLAGS=-DTIMING"
/// End:

