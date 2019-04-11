
#include "bits/bin-to-sl-gray.h"

#include "bits/print-bin.h"

#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "jjassert.h"

//% Converting binary numbers to corresponding words in SL-Gray order.
//% Cf. OEIS sequence A217262.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong ldn = 6;
    NXARG(ldn, "Number of bits");
    const ulong n = 1UL << ldn;

#ifdef TIMING
    jjassert( ldn < 32 );  // common error to supply n instead of ldn
    ulong d = 0;
    for (ulong k=0; k<n; ++k)
        d ^= bin_to_sl_gray(k, ldn);
    if ( d==239 )  cout << "can't happen" << endl;
    cout << " ct=" << n << endl;

#else

    ulong xo = bin_to_sl_gray(n-1, ldn);
    for (ulong k=0; k<n; ++k)
    {
        cout << setw(4) << k << ":";

        print_bin("    ", k, ldn);

        ulong x = bin_to_sl_gray(k, ldn);
        print_bin("    ", x, ldn);

        ulong d = x ^ xo;
        print_bin("    ", d, ldn);  // delta sequence
        xo = x;

        cout << endl;

        jjassert( d == (d & -d) );   // exactly one bit changed
        jjassert( k == sl_gray_to_bin( x, ldn ) );

    }
    cout << endl;
#endif

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

# GCC 4.9.0:

 time ./bin 27
arg 1: 27 == ldn  [Number of bits]  default=6
 ct=134217728
./bin 27  6.60s user 0.00s system 99% cpu 6.605 total
 ==> 134217728/6.60 == 20,336,019 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bin-to-sl-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bin-to-sl-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:
