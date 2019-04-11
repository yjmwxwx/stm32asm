
#include "bits/bitcombminchange.h"

#include "aux0/binomial.h"

#include "bits/print-bin.h"

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "jjassert.h"
#include "nextarg.h"

#include "fxtio.h"

//% Generating all combinations of bits (as binary words) in minimal-change order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 7, k = 4;
    NXARG(n, "Minchange combinations (n over k):  n  (n>0)");
    NXARG(k, "  (0<k<=n)");

    jjassert( n>0 );
    jjassert( k>0 );
    jjassert( n>=k );
    jjassert( n<BITS_PER_LONG );

    ulong last = igc_last_comb(k, n);
    ulong c, nc = first_sequency(k);
    ulong ct = 0;

#ifdef TIMING
    do
    {
        ++ct;
        c = nc;
        nc = igc_next_minchange_comb(c);  // 1-arg version
//        nc = igc_next_minchange_comb(c, k);  // 2-arg version
    }
    while ( c!=last );

#else  // TIMING

    const ulong pd = n;
    ulong g, gg = 0;
    do
    {
        ++ct;
        c = nc;
        nc = igc_next_minchange_comb(c);  // 1-arg version
//        nc = igc_next_minchange_comb(c, k);  // 2-arg version

        print_bin("    ", c, pd);
        print_bin("    ", nc-c, pd);
        g = gray_code(c);
        print_bin("    ", g, pd);
        if ( gg )
        {
            print_bin_diff("    ", gg, g, pd, ".1+-");
//            print_bin_diff("    ", gg, g, pd, "..11");
//            ulong a = ((g) & (~c)) << 1;
////            ulong b = (g^gg) & (a);
//            ulong b = (~g) & (c);
//            print_bin("    ", a, pd);
//            print_bin("    ", b, pd);
//            print_bin("    ", c^nc, pd);
        }
        gg = g;
        cout << endl;
    }
    while ( c!=last );
#endif  // TIMING

    cout << " ct=" << ct << endl;
    jjassert( ct == binomial(n, k) );

    return 0;
}
// -------------------------

/*
Timing:

 time bin 33 16
arg 1: 33 == n  [Minchange combinations (n over k):  n  (n>0)]  default=7
arg 2: 16 == k  [  (0<k<=n)]  default=4
 ct = 1166803110
bin 33 16  12.22s user 0.03s system 99% cpu 12.250 total
 ==> binomial(33, 16)/12.22 == 95,483,069 per second


 time ./bin 32 12
-------- 1-arg igc_next_minchange_comb() jj:
 ct = 225792840
./bin 32 12  2.34s user 0.02s system 99% cpu 2.369 total
 ==> 225792840/2.34 == 96,492,666 per second

 time ./bin 32 20
./bin 32 20  2.71s user 0.00s system 99% cpu 2.712 total
 ct = 225792840
 ==> 225792840/2.71 == 83,318,391 per second

check symmetry:
 time ./bin 63 6   ct = 67945521
./bin 63 6  1.83s user 0.00s system 99% cpu 1.838 total
 ==> 67945521/1.83 == 37,128,700 per second

 time ./bin 63 57  ct = 67945521
./bin 63 57  2.31s user 0.02s system 99% cpu 2.337 total
 ==> 67945521/2.31 == 29,413,645 per second

-------- 1-arg igc_next_minchange_comb() Doug Moore:
 time ./bin 32 12
./bin 32 12  3.48s user 0.02s system 99% cpu 3.506 total
 ==> 225792840/3.48 == 64,883,000 per second

 time ./bin 32 20
./bin 32 20  2.84s user 0.02s system 99% cpu 2.863 total
 ==> 225792840/2.84 == 79,504,521  per second

------ 2-arg igc_next_minchange_comb():
 time ./bin 32 12
./bin 32 12  3.65s user 0.02s system 99% cpu 3.674 total
 ==> 225792840/3.65 == 61,861,052 per second

 time ./bin 32 20
./bin 32 20  3.43s user 0.02s system 100% cpu 3.445 total
 ==> 225792840/3.43 == 65,828,816 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 33 16
arg 1: 33 == n  [Minchange combinations (n over k):  n  (n>0)]  default=7
arg 2: 16 == k  [  (0<k<=n)]  default=4
 ct = 1166803110
./bin 33 16  6.81s user 0.00s system 99% cpu 6.817 total
 ==> 1166803110/6.81 == 171,336,726 per second
*/

/*
BENCHARGS=33 16
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitcombminchange-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitcombminchange-demo.cc DEMOFLAGS=-DTIMING"
/// End:

