
#include "bits/negbin.h"

#include "bits/print-bin.h"  // print_bin()
#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "jjassert.h"


//% radix(-2) representations: successive generation.


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of bits");
    bool fq = 1;
    NXARG(fq, "Whether to use increasing order");

    ulong ct = 0;

    const ulong N = 1UL << n;
    ulong t = 0;

#ifdef TIMING
    if ( fq )
    {
        do
        {
            t ^= next_negbin(t);
            ++ct;
        }
        while ( ct<N );
    }
    else
    {
        do
        {
            t ^= prev_negbin(t);
            ++ct;
        }
        while ( ct<N );
    }

#if 1
    // without this things get optimized away
    cout << "dummy=" << t << endl;
#endif

#else  // TIMING

    const ulong pn = n+3;

    if ( fq )
    {
        do
        {
            cout << setw(4) << ct;
            print_bin(": ", t, pn);
            cout << endl;
            t = next_negbin(t);
            ++ct;
        }
        while ( ct<N );
    }
    else
    {
        do
        {
            print_bin(": ", t, pn);
            cout << endl;
            t = prev_negbin(t);
            ++ct;
        }
        while ( ct<N );
    }

#endif  // TIMING

    cout << "ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

forward:

 time ./bin 32 1
arg 1: 32 == n  [Number of bits]  default=5
arg 2: 1 == fq  [Whether to use increasing order]  default=1
ct=4294967296
dummy=4294967296
./bin 32 1  5.85s user 0.00s system 100% cpu 5.850 total
 ==> 4294967296/5.85 == 734,182,443 per second

backward: (same rate)
forward (version without masks): (same rate)

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32 0
arg 1: 32 == n  [Number of bits]  default=5
arg 2: 0 == fq  [Whether to use increasing order]  default=1
ct=4294967296
dummy=1
./bin 32 0  7.13s user 0.00s system 99% cpu 7.136 total
 ==> 4294967296/7.13 ==602,379,704  per second

 time ./bin 32 1
arg 1: 32 == n  [Number of bits]  default=5
arg 2: 1 == fq  [Whether to use increasing order]  default=1
ct=4294967296
dummy=3
./bin 32 1  7.14s user 0.00s system 99% cpu 7.139 total
 ==> 4294967296/7.14 == 601,536,035 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/negbin2-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/negbin2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

