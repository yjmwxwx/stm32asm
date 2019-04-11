
#include "bits/kolakoski-seq.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

//% Sequence A042942 of the OEIS,
//% related to the Oldenburger-Kolakoski sequence (A000002).
//% Cf. https://en.wikipedia.org/wiki/Kolakoski_sequence
//% Algorithm by David Eppstein,
//%   see http://11011110.livejournal.com/336374.html


int main(int argc, char **argv)
{
    ulong n = 30;
    NXARG(n, "Compute n terms of A042942");
    --n;  // because we get the last term for free


    kolakoski_seq K;

    K.next();  // drop the first '1'
    ulong c = K.next();
    ulong nc = 1;  // num characters seen
    ulong sm = c;  // num of characters seen
    ulong ct = 0;

    while ( true )
    {
        cout << ++ct << ":  " << nc << endl;

        if ( --n == 0 )  break;

        ulong ad = 0;
        while ( nc < sm )
        {
            c = K.next();
            ad += c;
            nc += 1;
        }

        sm += ad;
    }
    cout << ++ct << ":  " << sm << endl;  // one term for free

    return 0;
}
// -------------------------

/*

% time ./bin 50
arg 1: 50 == n  [Compute n terms of A042942]  default=30
1:  1
2:  2
3:  4
4:  6
[...]
49:  556582009
50:  834871315

./bin 50  1.32s user 0.00s system 99% cpu 1.329 total

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A042942-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A042942-demo.cc DEMOFLAGS=-DTIMING"
/// End:
