
#include "bpol/bitpol-srp.h"
#include "bpol/all-irredpoly.h"

#include "mod/factor.h"
#include "mod/mersenne.h"
#include "bpol/bitpol-order.h"
#include "bpol/bitpol-print.h"

//#include "bpol/bitpol-irred.h"  // bitpol_irreducible_q()
#include "bpol/bitpol-print.h"

//#include "bits/bitcount.h"
#include "bits/revbin.h"
#include "bits/print-bin.h"

#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"  // ulong

#include "nextarg.h"  // NXARG()



//% Generate all irreducible self-reciprocal binary polynomials of given degree.
//% Cf. OEIS sequences A000048, A175390, and A069925.

//#define TIMING  // uncomment to disable printing

#define ORDER  // whether to compute orders of SRPs

#ifdef TIMING
#undef ORDER
#endif

int
main(int argc, char **argv)
{
    ulong nh = 9;
    NXARG(nh, "Degree of polynomials 2 <= n < BITS_PER_LONG");
    jjassert( nh >= 2 );
    ulong n = 2*nh;
    bool cq = 0;
    NXARG(cq, "Whether to print the SRPs as coefficient vectors.");

    cout << "Degree of self-reciprocal polynomials (SRP) is n=" << n << endl;

    all_irredpoly ip( nh );

#ifdef ORDER
    factorization F;
    const ulong M = (1UL<<nh) - 1;
    F.make_factorization( M , mersenne_prime_factor_tab);
    cout << " F = " << F << " == M = " << M << endl;
    const ulong mr = (1UL<<(nh))-1;  // max order of polys
    const ulong h = (1UL<<(nh-1));  // aux for order with polys

    factorization Fs;
    const ulong mrs = (1UL<<nh)+1;  // max order of SRPs
    Fs.make_factorization( mrs , mersenne_prime_factor_tab);
    cout << " Fs = " << Fs << " == mrs = " << mrs << endl;
    const ulong hs = (1UL<<(n-1));  // aux for order with SRP

//    ulong mct = 0;  // count irreducible SRP maximal order
#endif  // ORDER

    ulong ict = 0;  // count irreducible SRP
//    ulong lct = 0;  // count irreducible SRP with linear coefficient one
    ulong p = ip.data();
    do
    {
        bool q = (p>>1) & 1;  // linear coefficient
        // q == bitpol_irreducible_q(s, h);
//        if ( p != revbin(p,nh+1) )  continue;

        if ( q )
        {
            ++ict;
#ifndef TIMING

            ulong s = bitpol_pol2srp(p, nh);
//            lct += ( (s>>1)&1 );
            cout << setw(4) << ict << ":";
            print_bin("    ", p, nh+1);

#ifdef ORDER
            ulong r = bitpol_order(p, h, F);
            cout << "  " << setw(3) << (mr/r);
#endif  // ORDER


            if ( cq )  bitpol_print_coeff("    ", s);
            else       print_bin("    ", s, n+1);
#ifdef ORDER
            ulong rs = bitpol_order(s, hs, Fs);
//            cout << "  " << setw(3) << (mrs/rs);
            cout << " % " << (mrs/rs);
//            mct += (mrs==rs);

#endif  // ORDER

            ulong t = bitpol_srp2pol(s, nh);
//            print_bin("    ", t, nh+1);

//            bitpol_print_coeff("  ", p);

            cout << endl;

            jjassert( t==p );
            jjassert( q==( (p>>1) & 1 ) );
#else  //  TIMING


            ulong s = bitpol_pol2srp(p, nh);
            jjassert( s != 0 );
//            ict += (s>>(BITS_PER_LONG-1));  // dummy

#endif  // TIMING
        }
    }
    while ( (p = ip.next()) );


    cout << " ict=" << ict << endl;
//    cout << " lct=" << lct << endl;
//    cout << " mct=" << mct << endl;
    cout << endl;

    return 0;
}
// -------------------------

/*
Timing:
 time ./bin 22
arg 1: 22 == nh  [Degree of polynomials 1 <= n < BITS_PER_LONG]  default=7
Degree of self-reciprocal polynomials (SRP) is n=44
 ict=95325
./bin 22  3.13s user 0.03s system 99% cpu 3.159 total
 ==> 95325/3.13 == 30,455 per second (slow, limited by all_irredpoly)
*/

/*
 OEIS sequence A000048:
 for n in $(seq 1 32) ; do echo -n "$n: " ; ./bin $n | g ict | cut -d= -f2 ; done
1: 1
2: 1
3: 1
4: 2
5: 3
6: 5
7: 9
8: 16
9: 28
10: 51
11: 93
12: 170
13: 315
14: 585
15: 1091
16: 2048
17: 3855
18: 7280
19: 13797
20: 26214
21: 49929
22: 95325
23: 182361
*/

/*
 OEIS sequence A175390:
 irreducible SRP with linear coefficient one

1: 1
2: 1
3: 0
4: 1
5: 2
6: 2
7: 4
8: 9
9: 14
10: 24
11: 48
12: 86
13: 154
14: 294
15: 550
16: 1017
17: 1926
18: 3654
19: 6888
20: 13092
21: 24998
22: 47658
23: 91124
*/

/*
OEIS sequence A069925, phi(2^n+1)/2n.
max order SRP

1: 1
2: 1
3: 1
4: 2
5: 2
6: 4
7: 6
8: 16
9: 18
10: 40
11: 62
12: 160
13: 210
14: 448
15: 660
16: 2048
17: 2570
18: 5184
19: 9198
20: 24672
21: 32508
22: 76032
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/bitpol-srp-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/bitpol-srp-demo.cc DEMOFLAGS=-DTIMING"
/// End:

