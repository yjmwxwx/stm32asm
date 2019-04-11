
#include "bits/bit2adic.h"

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/print-bin.h"

#include "nextarg.h"
#include "jjassert.h"

#include "fxtio.h"


//% 2-adic inverse and square root.

//#define TIMING  // uncomment to disable printing


ulong pn = 32;  // Number of bits shown, pn<=BITS_PER_LONG


void
show2adic(ulong x)
{
    print_bin("    x   = ", x, pn);
    cout << "  = " << setw(4) << (long)x;

    if ( x&1 )
    {
        ulong i = inv2adic(x);  // inverse
        cout << endl;
        print_bin("    inv = ", i, pn);
        jjassert( 1UL == x*i );
    }

    do
    {
        ulong r = sqrt2adic(x);
        if ( r*r != x )   break;

        cout << endl;
        print_bin("   sqrt = ", r, pn);
//        print_bin("   x = ", x, pn);
    }
    while ( 0 );

    cout << endl;
    cout << endl;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong ldn = 6;
    NXARG(ldn, "max n:=2**ldn-1");
    NXARG(pn, "Number of bits shown");
    ulong mq = 3;
    NXARG(mq, "");

    const ulong n = 1UL << ldn;

#ifdef TIMING
    ulong x = 0;
    for (ulong k=1; k<n; k+=2)  x |= inv2adic(k);
    cout << " ct=" << n << endl;
    if ( x==0 )  return 1;

#else
    for (ulong k=1; k<n; ++k)
    {
        ulong x = k;
        if ( mq & 1 )  show2adic(x);
        if ( mq & 2 )  show2adic(-x);
    }
#endif

    cout << endl;
    return 0;
}
// -------------------------

/*
Timing:

time ./bin 30
arg 1: 30 == ldn  [max n:=2**ldn-1]  default=6
arg 2: 32 == pn  [Number of bits shown]  default=32
arg 3: 3 == mq  []  default=3
./bin 30  14.51s user 0.02s system 100% cpu 14.532 total
 ==> 2^30/14.51 == 74,000,125 per second

BENCHARGS=30

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bit2adic-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bit2adic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

