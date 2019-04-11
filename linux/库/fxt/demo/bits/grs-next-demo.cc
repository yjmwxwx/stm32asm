

#include "bits/grsnegative.h"
#include "bits/bitlow.h"

#include "fxttypes.h"
#include "nextarg.h"
#include "jjassert.h"


//% Generate the Golay-Rudin-Shapiro (GRS) sequence.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 65;
    NXARG(n, "Print this many values of the sequence.");
    ulong k0 = 0;
    NXARG(k0, "Start point of the sequence.");

    cout << endl;
    ulong g = grs_negative_q(k0);
    for (ulong k=k0;  k<k0+n;  ++k)
    {
#ifndef TIMING
        cout << ( g ? '1' : '.' );
        jjassert( g == grs_negative_q(k) );
#endif
        g = grs_next(k, g);       // ver.1: update
//        g = grs_negative_q(k+1);  // ver.2: recompute
    }
    cout << endl;

    return  g & 2UL;  // always 0
}
// -------------------------

/*
Timing:

ver.1:
% time ./bin $(( 2**30 ))
arg 1: 1073741824 == n  [Print this many values of the sequence.]  default=65
arg 2: 0 == k0  [Start point of the sequence.]  default=0
./bin $(( 2**30 ))  3.09s user 0.01s system 100% cpu 3.096 total
 ==> 1073741824/3.09 == 347,489,263 per second

ver.2:
% time ./bin $(( 2**30 ))
arg 1: 1073741824 == n  [Print this many values of the sequence.]  default=65
arg 2: 0 == k0  [Start point of the sequence.]  default=0
./bin $(( 2**30 ))  3.42s user 0.01s system 99% cpu 3.427 total
 ==> 1073741824/3.42 == 313,959,597 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/grs-next-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/grs-next-demo.cc DEMOFLAGS=-DTIMING"
/// End:
