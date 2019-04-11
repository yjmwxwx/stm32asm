
#include "bits/bit-necklace.h"

#include "fxtio.h"
#include "fxttypes.h"  // ulong

#include "bits/bitsperlong.h"
#include "jjassert.h"

#include "nextarg.h"  // NXARG()

#include "bits/print-bin.h"
//#include "bits/bitcount.h"

//% Binary necklaces and Lyndon words: CAT generation.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Number of bits 0<n<=BITS_PER_LONG");
    jjassert( n>0 );
    jjassert( n<=BITS_PER_LONG );

    bit_necklace N(n);

    ulong nct = 0;  // count necklaces (prime strings)

#ifdef TIMING

    do
    {
        ++nct;
    }
    while ( N.next() );

    cout << "nct=" << nct << endl;

#else // TIMING

    ulong lct = 0;  // count Lyndon words
    do
    {
//        if ( bit_count( N.data() ) != n/2 )  continue;

        ++nct;
        cout << setw(4) << nct << ": ";
        print_bin("  ", N.data(), n);
        cout << "  " << setw(2) << N.period();
        if ( N.is_lyndon_word() )
        {
            ++lct;
            cout << "  L";
        }
        cout << endl;
    }
    while ( N.next() );

    cout << "  # necklaces=" << nct << endl;
    cout << "  # Lyndon words=" << lct << endl;

#endif  // TIMING


    return 0;
}
// -------------------------

/*
Timing:

// with highest_zero_idx() in next():
 time ./bin 32
  # necklaces=134219796
./bin 32  2.91s user 0.00s system 99% cpu 2.909 total
 ==> 134219796/2.91 == 46,123,641 per second
 (using  # pre-necklaces == 277737797 )
 ==> 277737797/2.91 == 95,442,541 pre-necklaces per second

// with explicit bit scan in next():
 time ./bin 32
  # necklaces=134219796
./bin 32  2.47s user 0.01s system 100% cpu 2.483 total
 ==> 134219796/2.47 == 54,339,998 per second
 ==> 277737797/2.47 == 112,444,452 pre-necklaces per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

// with highest_zero_idx() in next():
  time ./bin 32
arg 1: 32 == n  [Number of bits 0<n<=BITS_PER_LONG]  default=8
  # necklaces=134219796
./bin 32  1.43s user 0.00s system 99% cpu 1.427 total
 ==> 277737797/1.43 == 194,222,235 pre-necklaces per second


// with explicit bit scan in next():
 time ./bin 32
arg 1: 32 == n  [Number of bits 0<n<=BITS_PER_LONG]  default=8
  # necklaces=134219796
./bin 32  1.38s user 0.00s system 99% cpu 1.380 total
 ==> 277737797/1.38 == 201,259,273 pre-necklaces per second

*/


/*
BENCHARGS=34
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bit-necklace-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bit-necklace-demo.cc DEMOFLAGS=-DTIMING"
/// End:

