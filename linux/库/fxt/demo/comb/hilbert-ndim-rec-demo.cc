
#include "comb/hilbert-ndim-rec.h"

#include "fxttypes.h"
#include "jjassert.h"
#include "nextarg.h"

#include "fxtio.h"

//% Fred Lunnon's recursive algorithm for the n-dimensional Hilbert curve


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong d = 4;
    NXARG(d, "Number of dimensions  2<=d<32");
    jjassert( d>=2 );
    jjassert( d<=32 );

    hilbert_ndim_rec H(d);

    ulong n = 256;
    NXARG(n, "Max linear coord");

#ifdef TIMING

    for (ulong k=0; k<=n; ++k)
    {
        H.lin2hilbert(k);
    }

#else  // TIMING

    const ulong *P = H.data();
    ulong tt[32];
    for (ulong k=0; k<=n; ++k)
    {
        H.lin2hilbert(k);

        cout << setw(4) << k << ": [";
        for (ulong i=0; i<d; ++i)  cout << " " << P[i];
        cout << " ]" << endl;

        if ( k>0 )  // check that move is by one unit
        {
            ulong xct = 0;
            for (ulong j=0; j<d; ++j)  xct += (tt[j] != P[j]);
            jjassert( xct==1 );
        }
        for (ulong j=0; j<d; ++j)  tt[j] = P[j];
    }
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
./bin 2 10000000  5.56s user 0.00s system 99% cpu 5.559 total
 ==> 10000000/5.56 == 1,798,561 per second

 time ./bin 3 10000000
arg 1: 3 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 3 10000000  4.74s user 0.00s system 100% cpu 4.740 total
 ==> 10000000/4.74 == 2,109,704 per second

 time ./bin 4 10000000
arg 1: 4 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 4 10000000  4.08s user 0.02s system 99% cpu 4.107 total
 ==> 10000000/4.08 == 2,450,980 per second

 time ./bin 8 10000000
arg 1: 8 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 8 10000000  3.17s user 0.00s system 99% cpu 3.178 total
 ==> 10000000/3.17 == 3,154,574 per second


cf. Butz/Lawder (d==8):
./bin 10000000  26.84s user 0.04s system 99% cpu 26.891 total
 ==> 10000000/26.84 == 372,578 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 2 10000000
arg 1: 2 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 2 10000000  1.91s user 0.00s system 99% cpu 1.909 total
 ==> 10000000/1.91 == 5,235,602 per second

 time ./bin 3 10000000
arg 1: 3 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 3 10000000  1.77s user 0.00s system 99% cpu 1.773 total
 ==> 10000000/1.77 == 5,649,717 per second

 time ./bin 4 10000000
arg 1: 4 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 4 10000000  1.69s user 0.00s system 99% cpu 1.695 total
 ==> 10000000/1.69 == 5,917,159 per second

 time ./bin 8 10000000
arg 1: 8 == d  [Number of dimensions  2<=d<32]  default=4
arg 2: 10000000 == n  [Max linear coord]  default=256
./bin 8 10000000  1.46s user 0.00s system 99% cpu 1.464 total
 ==> 10000000/1.46 == 6,849,315 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/hilbert-ndim-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/hilbert-ndim-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:
