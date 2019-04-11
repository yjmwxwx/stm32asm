
#include "bits/bit-rll2.h"

#include "bits/print-bin.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

//% Run length limited (RLL) words and Fibonacci Gray code.

// Cf. comb/rll-rec-demo.cc

//#define TIMING // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Generate 2**n words");
    ulong N = 1UL << n;

    bool fq = true;
    NXARG(fq, "Whether to generate in forward order.");

    bit_rll2 B;
    B.middle();

#ifdef TIMING
    ulong d = 0;
    if ( fq )
    {
        cout << "forward:" << endl;
        for (ulong k=0; k<N; ++k)  d ^= B.next_fib();
    }
    else
    {
        cout << "backward:" << endl;
        for (ulong k=0; k<N; ++k)  d ^= B.prev_fib();
    }
    cout << "ct=" << N << endl;
    if ( d == 239 )  return 1;  // dummy

#else

    const ulong pn = n + n/2 + n/8 + 2;
    ulong ct = 0;
    for (ulong k=0; k<N; ++k)
    {
        cout << setw(4) << ct << ":";
        ++ct;
        ulong w = B.data();
        print_bin("    ", w, pn);

        ulong f = B.fib();
        print_bin("    ", f, pn);
        cout << endl;

        ( fq ? B.next() : B.prev() );
    }
    cout << endl;
#endif  // Timing

    return 0;
}
// -------------------------



/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 1
arg 1: 30 == n  [Generate 2**n words]  default=5
arg 2: 1 == fq  [Whether to generate in forward order.]  default=1
forward:
ct=1073741824
./bin 30 1  3.57s user 0.00s system 99% cpu 3.569 total
==> 1073741824/3.57 == 300,768,017 per second

 time ./bin 30 0
arg 1: 30 == n  [Generate 2**n words]  default=5
arg 2: 0 == fq  [Whether to generate in forward order.]  default=1
backward:
ct=1073741824
./bin 30 0  3.92s user 0.00s system 99% cpu 3.926 total
==> 1073741824/3.92 == 273,913,730 per second

GCC 4.8.0:
same performance

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bit-rll2-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bit-rll2-demo.cc DEMOFLAGS=-DTIMING"
/// End:
