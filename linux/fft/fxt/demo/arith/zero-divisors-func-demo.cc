
#include "aux0/cayley-dickson-mult.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "jjassert.h"


//% Simple zero divisors of Cayley-Dickson algebras.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of bits");
    const ulong N = 1UL << n;

    ulong ct = 0;  // count zero divisors

    for (ulong r=0; r<N; ++r)
    {
        for (ulong c=0; c<N; ++c)
        {
            bool q = CD_zerodiv_q(r, c);
#ifndef TIMING
            cout << (q?'1':'.');
#endif
            ct += q;
        }
#ifndef TIMING
        cout << endl;
#endif
    }
    cout << endl;

    cout << "ct/2=" << ct/2 << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)
% time ./bin 14
arg 1: 14 == n  [Number of bits]  default=5

ct/2=133885950
./bin 14  2.24s user 0.00s system 99% cpu 2.239 total
 ==> 2^28/2.24 == 119,837,257 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/arith"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/arith/zero-divisors-func-demo.cc"
/// make-target2: "1demo DSRC=demo/arith/zero-divisors-func-demo.cc DEMOFLAGS=-DTIMING"
/// End:

