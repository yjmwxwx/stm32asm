
#include "bits/revbin.h"

//#include "bits/bitzip.h"

#include "bits/bitsperlong.h"

#include "bits/print-bin.h"
#include "nextarg.h"

#include "fxtio.h"
#include "jjassert.h"
#include "fxttypes.h"  // ulong

//% Table lookup routine for reversing the bits of a word.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong ldn = 5;
    NXARG(ldn, "Reverse the first 2**n binary words.");
    const ulong n = 1UL<<ldn;

#ifdef TIMING
    ulong x = 0;
    for (ulong k=0; k<n; ++k)
    {
        x ^= revbin(k);  // ./bin 30  4.40s user 0.02s system 100% cpu 4.422 total

//        x ^= revbin_t(k);  // ./bin 30  11.11s user 0.06s system 99% cpu 11.170 total

        // cf.:
//        x ^= bit_zip(k);  // ./bin 30  10.75s user 0.05s system 99% cpu 10.805 total
    }

    cout << " ct=" << n << endl;

    return x & 1;

#else
    const ulong s = BITS_PER_LONG - ldn;
    for (ulong k=0; k<n; ++k)
    {
        ulong r1 = revbin(k);
        ulong r2 = revbin_t(k);
        print_bin("  ", k, ldn);
        print_bin("  :  ", r1>>s, ldn);
        cout << endl;
//        print_bin("  ", r2>>s, ldn);  cout << endl;
        jjassert( r1==r2 );
    }
#endif  // TIMING

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 30
arg 1: 30 == ldn  [Reverse the first 2**n binary words.]  default=5
./bin 30  4.40s user 0.00s system 100% cpu 4.398 total
 ==> 2^30/4.40 == 244,032,232 per second
*/

/*
BENCHARGS=30
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/revbin-tab-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/revbin-tab-demo.cc DEMOFLAGS=-DTIMING"
/// End:

