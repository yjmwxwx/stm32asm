
#include "comb/hilbert-ndim.h"

#include "fxttypes.h"
#include "jjassert.h"
#include "nextarg.h"

#include "fxtio.h"

//% Fred Lunnon's iterative algorithm for the n-dimensional Hilbert curve


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong d = 4;
    NXARG(d, "Number of dimensions  2<=d<32");
    jjassert( d>=2 );
    jjassert( d<=32 );

    hilbert_ndim H(d);
    const ulong *P = H.data();

    ulong n = 256;
    NXARG(n, "Max linear coord");

#ifndef TIMING
    ulong tt[32];
#endif

    for (ulong k=0; k<=n; ++k)
    {
        H.lin2hilbert(k);

#ifndef TIMING
        cout << setw(4) << k << ": [";
        for (ulong i=0; i<d; ++i)  cout << " " << P[i];
        cout << " ]" << endl;

        if ( k>0 )
        {
            ulong xct = 0;
            for (ulong j=0; j<d; ++j)  xct += (tt[j] != P[j]);
            jjassert( xct==1 );
        }
        for (ulong j=0; j<d; ++j)  tt[j] = P[j];
#endif  // TIMING
    }

#ifdef TIMING
    ulong y = 0;
    for (ulong k=0; k<d; ++k)  y ^= P[k];
    if ( y==239 )  cout << "";
#endif  // TIMING

    return 0;
}
// -------------------------

/*
test Gray property:
 for d in $(seq 2 10); do ./bin $d 100000 > /dev/null; done
*/



/*
Timing:

 time ./bin 2 10000000
arg 1: 2 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 2 10000000  1.50s user 0.01s system 99% cpu 1.512 total
 ==> 10000000/1.50 == 6,666,666 per second

 time ./bin 3 10000000
arg 1: 3 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 3 10000000  1.43s user 0.00s system 99% cpu 1.432 total
 ==> 10000000/1.43 == 6,993,006 per second

 time ./bin 4 10000000
arg 1: 4 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 4 10000000  1.43s user 0.01s system 99% cpu 1.437 total
 ==> 10000000/1.43 == 6,993,006 per second

 time ./bin 8 10000000
arg 1: 8 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 8 10000000  1.53s user 0.00s system 100% cpu 1.532 total
 ==> 10000000/1.53 == 6,535,947 per second


cf. Butz/Lawder (d==8):
./bin 10000000  26.84s user 0.04s system 99% cpu 26.891 total
 ==> 10000000/26.84 == 372,578 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 2 10000000
arg 1: 2 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 2 10000000  0.81s user 0.00s system 99% cpu 0.809 total
 ==> 10000000/0.81 == 12,345,679 per second


 time ./bin 3 10000000
arg 1: 3 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 3 10000000  0.82s user 0.00s system 99% cpu 0.827 total
 ==> 10000000/0.82 == 12,195,121 per second

 time ./bin 4 10000000
arg 1: 4 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 4 10000000  0.87s user 0.00s system 99% cpu 0.875 total
 ==> 10000000/0.87 == 11,494,252 per second

 time ./bin 8 10000000
arg 1: 8 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 8 10000000  0.90s user 0.00s system 99% cpu 0.906 total
 ==> 10000000/0.90 == 11,111,111 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/hilbert-ndim-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/hilbert-ndim-demo.cc DEMOFLAGS=-DTIMING"
/// End:
