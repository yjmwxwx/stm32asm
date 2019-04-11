
#include "bits/bitcombcolex.h"

#include "aux0/binomial.h"

#include "bits/print-bin.h"

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "jjassert.h"
#include "nextarg.h"

#include "fxtio.h"


//% Generating combinations of bits (as binary words) in co-lexicographic order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 7, k = 4;
    NXARG(n, "Colex combinations (n over k):  n  (n>0)");
    NXARG(k, "  (0<=k<=n)");

    jjassert( n>0 );
    jjassert( n>=k );
    jjassert( n<BITS_PER_LONG );

    const ulong last = last_comb(k, n);
    ulong g = first_comb(k);
    ulong gg = 0;
    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        print_bin("    ", g, n);
        print_bit_set(" = ", g);
        cout << endl;
#endif  // TIMING
        gg = g;
        g =  next_colex_comb(g);
    }
    while ( gg!=last );

    cout << " ct=" << ct << endl;
    jjassert( ct == binomial(n, k) );

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 32 20
arg 1: 32 == n  [Colex combinations (n over k):  n  (n>0)]  default=7
arg 2: 20 == k  [  (0<k<=n)]  default=4
./bin 32 20  1.59s user 0.00s system 99% cpu 1.594 total
 ==> binomial(32,20)/1.59 == 142,008,075 per second

 time ./bin 32 12
arg 1: 32 == n  [Colex combinations (n over k):  n  (n>0)]  default=7
arg 2: 12 == k  [  (0<k<=n)]  default=4
./bin 32 12  1.88s user 0.00s system 100% cpu 1.888 total
 ==> binomial(32,12)/1.88 == 120,102,574 per second

// very sparse:
./bin 60 7  5.53s user 0.02s system 99% cpu 5.551 total
 ==> binomial(60,7)/5.53 == 69,838,502 per second

// very dense:
./bin 60 53  2.42s user 0.01s system 99% cpu 2.440 total
 ==> binomial(60,53)/2.42 == 159,589,636 per second

 time ./bin 33 16
arg 1: 33 == n  [Colex combinations (n over k):  n  (n>0)]  default=7
arg 2: 16 == k  [  (0<=k<=n)]  default=4
./bin 33 16  9.08s user 0.00s system 100% cpu 9.080 total
 ==> binomial(33,16)/9.08 == 128,502,545 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 33 16
arg 1: 33 == n  [Colex combinations (n over k):  n  (n>0)]  default=7
arg 2: 16 == k  [  (0<=k<=n)]  default=4
./bin 33 16  6.29s user 0.00s system 99% cpu 6.294 total
 ==> binomial(33,16)/6.29 == 185,501,289 per second

*/

 /*
BENCHARGS=33 16
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitcombcolex-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitcombcolex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

