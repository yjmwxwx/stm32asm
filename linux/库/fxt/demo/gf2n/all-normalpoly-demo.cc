
#include "bpol/all-irredpoly.h"
// demo-include "bits/bit-necklace.h"
// demo-include "bpol/necklace2bitpol.h"
#include "bpol/normalbasis.h"
// demo-include "bpol/bitpol-normal.cc"
#include "bmat/bitmat-funcs.h"

#include "bpol/bitpol-print.h"

#include "bpol/gf2n-trace.h"
#include "bits/print-bin.h"

#include "fxttypes.h"  // ulong
#include "nextarg.h"  // NXARG()

#include "fxtio.h"
#include "jjassert.h"
#include "fxtalloca.h"


//% Find all normal binary polynomials of degree n.
//% Print all corresponding multiplier matrices.
//% Cf. OEIS sequences A027362, A107222, and A272033.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 9;
    NXARG(n, "Degree of the polynomials");
#ifndef TIMING
    ulong pp = 3;
    NXARG(pp, "How to print polynomials:\n"
          "    1==>binary, 2==>as poly., 3==> both, 0==>just count");
    ulong mq = 0;
    NXARG(mq, "Whether to print multiplication matrix");
#endif  // TIMING

    ALLOCA(ulong, M, n);  // multiplier matrix
    for (ulong j=0; j<n; ++j)  M[j] = 0;
    all_irredpoly ip(n);
    ulong *Mp = M;

    ulong nct = 0;  // count normal polynomials
    ulong pct = 0;  // count primitive normal polynomials
    ulong p = ip.data();

    do
    {
        const bool nq = bitpol_normal_q(p, n, 1, Mp);
//        const bool nq = true;  // for timing
//        jjassert( nq == bitpol_normal2_q(p, n) );

//        print_bin("neckl:  ", ip.bn_.a_, n );
//        if ( !nq )  cout << endl;

        if ( nq )
        {
            ++nct;
            ulong pq = ip.is_primitive();  // computes just a gcd
//            ulong pq = 1;  // for timing
            if ( pq )  ++pct;

#ifndef TIMING

            if ( 0==pp )  goto next;  // just count

            cout << setw(3) << nct << ":";
            if ( pp )
            {
                cout << " c =";
                if ( pp&1 )  bitpol_print_bin("  ", p);
                if ( pq )  cout << "  P";  // primitive polynomial
                else       cout << "   ";
                if ( pp==3 )  cout << " == ";
                if ( pp&2 )  bitpol_print("  ", p, n+1);
            }

            cout << endl;

            if ( mq )
            {
                bitmat_print("M=", M, n);
                cout << endl;
            }
#endif  // TIMING
            goto next;  // avoid compiler warning with TIMING defined
        }

    next:
        p = ip.next();
    }
    while ( p );

    cout << "  n=" << n;  // A027362
    cout << "   #= " << nct << "   #primitive = " << pct;  // A107222
    cout << "   #non-primitive = " << nct-pct;  // A272033
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)

GCC 4.9.2:

 time ./bin 24
arg 1: 24 == n  [Degree of the polynomials]  default=9
  n=24   #= 262144   #primitive = 103680   #non-primitive = 158464
./bin 24  4.56s user 0.00s system 99% cpu 4.563 total
 ==> 2^24 / 4.56 == 3,679,214 per second

The computation for n==38 took about 38 hours
*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 24
./bin 24  5.66s user 0.00s system 99% cpu 5.662 total
 ==> 2^24/5.66 == 2,964,172 per second

 Omitting test for normality:
./bin 24  2.03s user 0.00s system 99% cpu 2.027 total
 ==> 2^24/2.03 == 8,264,638 per second

 Omitting test for primitivity:
./bin 24  5.62s user 0.00s system 99% cpu 5.619 total
 ==> 2^24/5.62 == 2,985,269 per second

 Omitting test for normality and primitivity:
./bin 24  1.93s user 0.00s system 99% cpu 1.930 total
 ==> 2^24/1.93 == 8,692,858 per second

*/

/*
Timing:

  n=24   #= 262144   #primitive = 103680   #non-primitive = 158464
./bin 24  27.92s user 0.14s system 99% cpu 28.060 total
 ==> 2^24/27.92 == 600,903 per second

  n=23   #= 182183   #primitive = 178259   #non-primitive = 3924
./bin 23  13.27s user 0.07s system 99% cpu 13.344 total
 ==> 2^23/13.27 == 632,148 per second

  n=22   #= 95232   #primitive = 59986   #non-primitive = 35246
./bin 22  6.19s user 0.05s system 99% cpu 6.241 total
 ==> 2^22/6.19 == 677,593 per second

*/


/*

  n=1   #= 1   #primitive = 1   #non-primitive = 0
  n=2   #= 1   #primitive = 1   #non-primitive = 0
  n=3   #= 1   #primitive = 1   #non-primitive = 0
  n=4   #= 2   #primitive = 1   #non-primitive = 1
  n=5   #= 3   #primitive = 3   #non-primitive = 0
  n=6   #= 4   #primitive = 3   #non-primitive = 1
  n=7   #= 7   #primitive = 7   #non-primitive = 0
  n=8   #= 16   #primitive = 7   #non-primitive = 9
  n=9   #= 21   #primitive = 19   #non-primitive = 2
  n=10   #= 48   #primitive = 29   #non-primitive = 19
  n=11   #= 93   #primitive = 87   #non-primitive = 6
  n=12   #= 128   #primitive = 52   #non-primitive = 76
  n=13   #= 315   #primitive = 315   #non-primitive = 0
  n=14   #= 448   #primitive = 291   #non-primitive = 157
  n=15   #= 675   #primitive = 562   #non-primitive = 113
  n=16   #= 2048   #primitive = 1017   #non-primitive = 1031
  n=17   #= 3825   #primitive = 3825   #non-primitive = 0
  n=18   #= 5376   #primitive = 2870   #non-primitive = 2506
  n=19   #= 13797   #primitive = 13797   #non-primitive = 0
  n=20   #= 24576   #primitive = 11255   #non-primitive = 13321
  n=21   #= 27783   #primitive = 23579   #non-primitive = 4204
  n=22   #= 95232   #primitive = 59986   #non-primitive = 35246
  n=23   #= 182183   #primitive = 178259   #non-primitive = 3924
  n=24   #= 262144   #primitive = 103680   #non-primitive = 158464
  n=25   #= 629145   #primitive = 607522   #non-primitive = 21623
  n=26   #= 1290240   #primitive = 859849   #non-primitive = 430391
  n=27   #= 1835001   #primitive = 1551227   #non-primitive = 283774
  n=28   #= 3670016   #primitive = 1815045   #non-primitive = 1854971
  n=29   #= 9256395   #primitive = 9203747   #non-primitive = 52648
  n=30   #= 11059200   #primitive = 5505966   #non-primitive = 5553234
  n=31   #= 28629151   #primitive = 28629151   #non-primitive = 0
  n=32   #= 67108864   #primitive = 33552327   #non-primitive = 33556537
  n=33   #= 97327197   #primitive = 78899078   #non-primitive = 18428119
  n=34   #= 250675200   #primitive = 167112969   #non-primitive = 83562231
  n=35   #= 352149525   #primitive = 333342388   #non-primitive = 18807137
  n=36   #= 704643072   #primitive = 267841392   #non-primitive = 436801680
  n=37   #= 1857283155   #primitive = 1848954877   #non-primitive = 8328278
  n=38   #= 3616800768   #primitive = 2411186731   #non-primitive = 1205614037

OEIS seqs.:  A027362,      A107222,     A272033

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/all-normalpoly-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/all-normalpoly-demo.cc DEMOFLAGS=-DTIMING"
/// End:
