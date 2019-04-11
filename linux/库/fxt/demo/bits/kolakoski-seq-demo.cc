
#include "bits/kolakoski-seq.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

//% Oldenburger-Kolakoski sequence.
//% See OEIS sequence A000002.
//% Cf. https://en.wikipedia.org/wiki/Kolakoski_sequence
//% Algorithm by David Eppstein,
//%   see http://11011110.livejournal.com/336374.html

//#define TIMING  // uncomment to disable printing

int main(int argc, char **argv)
{
    ulong n = 64;
    NXARG(n, "Compute n terms of the Kolakoski sequence");
    kolakoski_seq K;
#ifdef TIMING
    ulong d = 0;
    while ( n-- )  d ^= K.next();
    cout << d << endl;
#else

#if 1

    while ( n-- )  cout << K.next() << ", ";

#else // A022292:

    ulong ct = 0;
    ulong st[3];
    st[1] = st[2] = 0;
    cout << "0, ";
    while ( n-- )
    {
        ++ct;
        st[ K.next() ] += 1;
        if ( st[1] == st[2] )  cout << ct << ", ";
    }

#endif

    cout << endl;

#endif
    return 0;
}
// -------------------------

/*

Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)

GCC 4.9.2:

arg 1: 1000000000 == n  [Compute n terms of the Kolakoski sequence]  default=64
3
./bin 1000000000  2.04s user 0.00s system 99% cpu 2.048 total
 ==> 1000000000 / 2.04 == 490,196,078 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/kolakoski-seq-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/kolakoski-seq-demo.cc DEMOFLAGS=-DTIMING"
/// End:
