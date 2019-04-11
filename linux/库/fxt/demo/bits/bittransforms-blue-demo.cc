
#include "bits/bittransforms.h"

#include "bits/bit2pow.h"
#include "bits/bitcount.h"
#include "bits/bitsperlong.h"
#include "fxttypes.h"
#include "bits/print-bin.h"

#include "nextarg.h"

#include "fxtio.h"


//% Transforms of binary words that are involutions: blue code and yellow code.

//#define TIMING  // uncomment to disable printing

// Output dependent on BITS_PER_LONG

int
main(int argc, char **argv)
{
    ulong ldn = 5;
    NXARG(ldn, "List transforms of first 2**ldn numbers");
    const ulong n = 1UL<<ldn;
    ulong pn = 32;
    NXARG(pn, "Number of bits to print, pn <= BITS_PER_LONG");

#ifdef TIMING
    ulong x = 0;
    for (ulong k=1; k<n;  ++k)  x |= blue_code(k);
    cout << " ct=" << n << endl;
    if ( x==0 )  return 1;

#else
    ulong pns = ld(n)+1;
    for (ulong k=0; k<n;  ++k)
    {
        cout << setw(4) << k << ":";
        print_bin("   k=", k , pns);
        cout << " " << setw(2) << bit_count(k);

        ulong b = blue_code(k);
        print_bin("   b=", b , pns);
        cout << " " << setw(2) << bit_count(b);
        cout << ( b == k ? "*" : " ");

        ulong y = yellow_code(k);
//        y = bit_rotate_right(y, 1);  y = yellow_code(y);  // ==> gray^shift
        print_bin("   y=", y , pn);
        cout << " " << setw(2) << bit_count(y);

        cout << endl;
    }
#endif

    cout << endl;

    return 0;
}
// -------------------------

/*
Timing:

time ./bin 30
arg 1: 30 == ldn  [List transforms of first 2**ldn numbers]  default=5
arg 2: 32 == pn  [Number of bits to print, pn <= BITS_PER_LONG]  default=32
./bin 30  12.19s user 0.03s system 99% cpu 12.232 total
 ==> 2^30/12.19 == 88,083,824 per second

BENCHARGS=30

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bittransforms-blue-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bittransforms-blue-demo.cc DEMOFLAGS=-DTIMING"
/// End:

