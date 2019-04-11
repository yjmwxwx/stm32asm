
#include "bits/bit-sl-gray.h"

#include "bits/bin-to-sl-gray.h"

#include "bits/print-bin.h"

//#include "comb/composition-nz-rank.h"
//#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "bits/bitsperlong.h"

#include "nextarg.h"
#include "jjassert.h"


//% Binary words in SL-Gray order, the minimal-change order
//% corresponding to subset-lex order.
//% Cf. OEIS sequence A217262.

// Cf. bits/bitlex-demo.cc for subset-lex order.
// Cf. comb/binary-sl-gray-demo.cc for generation in an array.
// Cf. comb/mixedradix-subset-lex-demo.cc for subset-lex order for mixed radix numbers
// Cf. comb/mixedradix-sl-gray-demo.cc for SL-Gray order for mixed radix numbers


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "n-bit binary words");


    bit_sl_gray G(n);
    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( G.next() );

#else  // TIMING

    ulong xo = 1UL;
    if ( n>=2 )  xo <<= (n-2);
    do
    {
        ulong x = G.data();
        cout  << setw(4) << ct << ":";
        print_bin("    ", x, n);  // words of the Gray code
        print_bin("    ", x^xo, n);  // delta sequence
        xo = x;
//        print_bin("    ", G.tr_, n);  // internal data: track

        ulong z = bin_to_sl_gray(ct, n);
//        print_bin("    ", z, n);

#if 0
        ulong C[64];
        ulong m = composition_nz_unrank(~x, C, n+1);
        print_vec("    ", C, m);
#endif

        ++ct;
        cout << endl;

        jjassert( x == z );
    }
    while ( G.next() );
#endif  // TIMING
    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32
arg 1: 32 == n  [n-bit binary words]  default=5
 ct=4294967296
./bin 32  9.60s user 0.00s system 99% cpu 9.601 total
 ==> 2^32/9.60 == 447,392,426 per second

*/

/*
BENCHARGS=32
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bit-sl-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bit-sl-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

