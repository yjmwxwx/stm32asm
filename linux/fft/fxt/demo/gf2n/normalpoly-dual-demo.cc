
#include "bpol/normalpoly-dual.h"

#include "bpol/all-irredpoly.h"
#include "bpol/bitpolmod-minpoly.h"
// demo-include "bits/bit-necklace.h"
// demo-include "bpol/necklace2bitpol.h"

#include "bpol/bitpol-print.h"

//// demo-include "bpol/bitpol-normal.cc"
//#include "bmat/bitmat-funcs.h"



#include "bits/print-bin.h"

#include "fxttypes.h"  // ulong
#include "nextarg.h"  // NXARG()

#include "fxtio.h"
#include "jjassert.h"
#include "fxtalloca.h"

//% Find all normal binary polynomials of degree n and their duals.

//#define TIMING  // uncomment to disable printing


#define TEST  // verify alternative method to test normality

#ifdef TEST
#include "bpol/normalbasis.h"
#endif  // TEST

#ifdef TIMING
#undef TEST
#endif

int
main(int argc, char **argv)
{
    ulong n = 9;
    NXARG(n, "Degree of the polynomials");

    ulong wh = 1;
    NXARG(wh, "What to print:\n"
          "    0==> nothing (just count),\n"
          "    1==> binary polynomials and ntrace(),\n"
          "    2==> polynomials."
          );

    bool sd = 0;
    NXARG(sd, "Whether to skip polynomials that are not self-dual");


    all_irredpoly P(n);

#ifndef TIMING
    ulong prct = 0;  // printed polynomials
#endif
    ulong nct = 0;  // count normal polynomials
    ulong pct = 0;  // count primitive normal polynomials
    ulong dct = 0;  // count self-dual normal polynomials
    ulong pdct = 0;  // count self-dual primitive normal polynomials
    ulong C = P.data();

    const ulong xn1 = 1 + (1UL<<n);  // x^n + 1
    if ( sd && ((n%4)==0) )  goto end;  // no self-dual normal polynomials exist
    do
    {
        const ulong T = gf2n_xx2k_trace(C, n);
        const bool dq = (T==1);  // C is normal, its roots are a self-dual (normal) basis
        dct += dq;

        const bool nq2 = ( 1 == bitpol_gcd(T, xn1) );  // C is normal
#ifdef TEST
        jjassert( nq2 ==  bitpol_normal_q(C, n, 1) );
#endif  // TEST

        if ( nq2 )
        {
            ++nct;
            const bool pq = P.is_primitive();  // computes just a gcd
            if ( pq )
            {
                ++pct;
                pdct += dq;
            }

#ifndef TIMING
            if ( 0==wh )  goto next;  // just count
            ulong Cs, D;
            Cs = gf2n_dual_normal(C, n, T, &D);
            if ( sd && (C!=Cs) )  goto next;  // only self-dual

            ++prct;
            cout << setw(3) << prct << ":";
            if ( wh==1 )  { print_bin("  C=", C, n+1);  print_bin("  T=", T, n+1); }
            else          bitpol_print("\n  C=", C);

            if ( pq )  cout << "  P";  // primitive polynomial
            else       cout << "   ";

            if ( dq )  cout << "  S";
            else       cout << "   ";

            if ( dq && (wh==2) )  { cout << endl; goto next; }  // avoid duplicating self-duals

            if ( wh==1 )  { print_bin("  Cs=", Cs, n+1);  print_bin("  D=", D, n+1); }
            else          bitpol_print("\n  Cs=", Cs);

            if ( wh==2 )  cout << endl;
            cout << endl;
#else  // TIMING
            goto next;   // avoid compiler warning about unused label
#endif  // TIMING
        }

    next:
        C = P.next();
    }
    while ( C );

 end:
    cout << "  n=" << n;
    cout << "   #= " << nct;  // normal
    cout << "   #P = " << pct;  // primitive
    cout << "   #N = " << nct-pct;  // non-primitive
    cout << "   #S = " << dct;  // self-dual
    cout << "   #SP = " << pdct;  // self-dual-primitive
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing:
  n=24   #= 262144   #P = 103680   #N = 158464   #S = 0   #SP = 0
./bin 24  15.24s user 0.07s system 99% cpu 15.314 total

  n=23   #= 182183   #P = 178259   #N = 3924   #S = 89   #SP = 87
./bin 23  7.35s user 0.04s system 99% cpu 7.396 total

  n=22   #= 95232   #P = 59986   #N = 35246   #S = 96   #SP = 60
./bin 22  3.50s user 0.02s system 99% cpu 3.543 total
*/

/*
  n=1   #= 1   #P = 1   #N = 0   #S = 1   #SP = 1
  n=2   #= 1   #P = 1   #N = 0   #S = 1   #SP = 1
  n=3   #= 1   #P = 1   #N = 0   #S = 1   #SP = 1
  n=4   #= 2   #P = 1   #N = 1   #S = 0   #SP = 0
  n=5   #= 3   #P = 3   #N = 0   #S = 1   #SP = 1
  n=6   #= 4   #P = 3   #N = 1   #S = 2   #SP = 1
  n=7   #= 7   #P = 7   #N = 0   #S = 1   #SP = 1
  n=8   #= 16   #P = 7   #N = 9   #S = 0   #SP = 0
  n=9   #= 21   #P = 19   #N = 2   #S = 3   #SP = 2
  n=10   #= 48   #P = 29   #N = 19   #S = 4   #SP = 3

  n=11   #= 93   #P = 87   #N = 6   #S = 3   #SP = 3
  n=12   #= 128   #P = 52   #N = 76   #S = 0   #SP = 0
  n=13   #= 315   #P = 315   #N = 0   #S = 5   #SP = 5
  n=14   #= 448   #P = 291   #N = 157   #S = 8   #SP = 4
  n=15   #= 675   #P = 562   #N = 113   #S = 15   #SP = 11
  n=16   #= 2048   #P = 1017   #N = 1031   #S = 0   #SP = 0
  n=17   #= 3825   #P = 3825   #N = 0   #S = 17   #SP = 17
  n=18   #= 5376   #P = 2870   #N = 2506   #S = 48   #SP = 25
  n=19   #= 13797   #P = 13797   #N = 0   #S = 27   #SP = 27
  n=20   #= 24576   #P = 11255   #N = 13321   #S = 0   #SP = 0

  n=21   #= 27783   #P = 23579   #N = 4204   #S = 63   #SP = 57
  n=22   #= 95232   #P = 59986   #N = 35246   #S = 96   #SP = 60
  n=23   #= 182183   #P = 178259   #N = 3924   #S = 89   #SP = 87
  n=24   #= 262144   #P = 103680   #N = 158464   #S = 0   #SP = 0
  n=25   #= 629145   #P = 607522   #N = 21623   #S = 205   #SP = 200
  n=26   #= 1290240   #P = 859849   #N = 430391   #S = 320   #SP = 215
// n=26 takes about one minute
  n=27   #= 1835001   #P = 1551227   #N = 283774   #S = 513   #SP = 428
  n=28   #= 3670016   #P = 1815045   #N = 1854971   #S = 0   #SP = 0
  n=29   #= 9256395   #P = 9203747   #N = 52648   #S = 565   #SP = 562
  n=30   #= 11059200   #P = 5505966   #N = 5553234   #S = 1920   #SP = 997

  n=31   #= 28629151   #P = 28629151   #N = 0   #S = 961   #SP = 961
  n=32   #= 67108864   #P = 33552327   #N = 33556537   #S = 0   #SP = 0
  n=33   #= 97327197   #P = 78899078   #N = 18428119   #S = 3267   #SP = 2660
  n=34   #= 250675200   #P = 167112969   #N = 83562231   #S = 4352   #SP = 2917
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/normalpoly-dual-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/normalpoly-dual-demo.cc DEMOFLAGS=-DTIMING"
/// End:
