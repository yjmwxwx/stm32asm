
#include "aux0/cayley-dickson-mult.h"

#include "bits/graycode.h"
#include "bits/parity.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"

#include "jjassert.h"

//% Multiplication table with hypercomplex numbers (Cayley-Dickson construction)
//% See OEIS sequence A118685.

//#define TIMING  // uncomment to disable printing

//#define USE_REC_OPT  // define to use optimization with recursive version
// note: makes routine slower with large n

int
main(int argc, char **argv)
{
//    gen_table();

    ulong ldn = 5;
    NXARG(ldn, "Multiplication table for (2**ldn)-ions");
    const ulong n = 1UL << ldn;

#ifdef TIMING
    bool q = 0;
    NXARG(q, "Whith benchmark: wether to use iterative routine");

    int x = 0;
    if ( q )  // here: iterative vs. recursive
    {
        cout << "iterative routine:" << endl;
        for (ulong r=0; r<n; ++r)
            for (ulong c=0; c<n; ++c) { x ^= CD_sign_it(r, c, n); }
    }
    else
    {
        cout << "recursive routine:" << endl;
        for (ulong r=0; r<n; ++r)
            for (ulong c=0; c<n; ++c) { x ^= CD_sign_rec(r, c, n); }
    }

    cout << "ct=" << (1UL<<(2*ldn)) << endl;

    return x;

#else
    bool q = 0;
    NXARG(q, "Whether to include indices of components");

    for (ulong r=0; r<n; ++r)
    {
        cout << setw(4) << r << ":  ";
        for (ulong c=0; c<n; ++c)
        {
            int s = CD_sign_it(r, c, n);
            if ( 0==q )  cout << " " << (s<0 ? '-' : '+');
            else
            {
                cout << setw(4)
                     << (r^c)
                     << (s<0 ? '-' : '+');
            }

            jjassert( s == CD_sign_rec(r, c, n) );
        }
        cout << endl;
    }

    return 0;
#endif
}
// -------------------------

/*

Timing:

%  time ./bin 12 1
arg 1: 12 == ldn  [Multiplication table for (2**ldn)-ions]  default=5
arg 2: 1 == q  [Whether to include indices of components]  default=0
iterative routine:
./bin 12 1  1.44s user 0.00s system 99% cpu 1.441 total
 ==> 2^24/1.44 == 11,650,844 per second

%  time ./bin 12 0
arg 1: 12 == ldn  [Multiplication table for (2**ldn)-ions]  default=5
arg 2: 0 == q  [Whether to include indices of components]  default=0
recursive routine:
./bin 12 0  1.35s user 0.00s system 99% cpu 1.351 total
 ==> 2^24/1.35 == 12,427,567 per second

% time ./bin 13 1
arg 1: 13 == ldn  [Multiplication table for (2**ldn)-ions]  default=5
arg 2: 1 == q  [Whether to include indices of components]  default=0
iterative routine:
./bin 13 1  6.36s user 0.00s system 100% cpu 6.353 total
 ==> 2^26/6.36 == 10,551,708 per second

%  time ./bin 13 0
arg 1: 13 == ldn  [Multiplication table for (2**ldn)-ions]  default=5
arg 2: 0 == q  [Whether to include indices of components]  default=0
recursive routine:
./bin 13 0  5.92s user 0.00s system 99% cpu 5.921 total
 ==> 2^26/5.92 == 11,335,956 per second

%  time ./bin 14 1
arg 1: 14 == ldn  [Multiplication table for (2**ldn)-ions]  default=5
arg 2: 1 == q  [Whether to include indices of components]  default=0
iterative routine:
./bin 14 1  27.83s user 0.02s system 99% cpu 27.845 total
 ==> 2^28/27.83 == 9,645,542 per second

%  time ./bin 14 0
arg 1: 14 == ldn  [Multiplication table for (2**ldn)-ions]  default=5
arg 2: 0 == q  [Whether to include indices of components]  default=0
recursive routine:
./bin 14 0  25.79s user 0.02s system 99% cpu 25.816 total
 ==> 2^28/25.79 == 10,408,509 per second

*/

/*
BENCHARGS=13 1
BENCHARGS=13 0
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/arith"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/arith/cayley-dickson-demo.cc"
/// make-target2: "1demo DSRC=demo/arith/cayley-dickson-demo.cc DEMOFLAGS=-DTIMING"
/// End:

