
#include "bits/thue-morse.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Generate the Thue-Morse sequence

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 64;
    NXARG(n, "Print this many values of the sequence.");
    ulong k = 0;
    NXARG(k, "Start point of the sequence.");

    thue_morse S(k);

#ifdef TIMING
    ulong x = 0;  // dummy
    for (ulong j=0; j<n; ++j)  x ^= S.next();
    cout << "dummy=" << x << endl;

#else
    for (ulong j=0; j<n; ++j)
    {
        cout << (S.data() ? '1' : '.');
        S.next();
    }
    cout << endl;
#endif

    return 0;
}
// -------------------------

/*
Timing:

%  time ./bin $(( 2**30 ))
arg 1: 1073741824 == n  [Print this many values of the sequence.]  default=64
arg 2: 0 == k  [Start point of the sequence.]  default=0
dummy=1
./bin $(( 2**30 ))  2.93s user 0.00s system 100% cpu 2.930 total
 ==> 1073741824/2.93 == 366,464,786 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/thue-morse-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/thue-morse-demo.cc DEMOFLAGS=-DTIMING"
/// End:
