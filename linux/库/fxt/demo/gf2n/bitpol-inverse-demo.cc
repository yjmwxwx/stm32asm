
#include "bpol/bitpol-gcd.h"  // bitpol_egcd()
#include "bpol/bitpol-arith.h"  // bitpol_div(), bitpol_rem()
#include "bpol/bitpolmod-arith.h"  // bitpolmod_mult(),  bitpol_inverse()

#include "bits/print-bin.h"

#include "nextarg.h"
#include "jjassert.h"
#include "fxttypes.h"

//% Modular inversion of binary polynomials via extended gcd (EGCD).

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong D = 23;
    NXARG(D, "Degree of polynomial moduli ( d < D < BITS_PER_LONG )");
    ulong d = 15;
    NXARG(d, "Degree of polynomials to invert");
    if ( d>=D )  d = D - 1;
    const ulong N1 = 1UL<<d;
    const ulong N2 = 1UL<<D;
    ulong pn = D+1;  // print precision
#ifndef TIMING
    const ulong h = 1UL<<(D-1);  // aux for modular multiplication
#endif

    ulong n = 5;
    NXARG(n, "Will invert all coprime polynomials out of n*n candidates");
    if ( n>=N1/2 )  n = N1/2-1;

    for (ulong j=0; j<n; ++j)
    {
        const ulong p2 = N2 | j;
        for (ulong k=0; k<n; ++k)
        {
            ulong p1 = N1 | k;

#ifdef TIMING
//            pn ^= bitpol_inverse(p1, p2);
            pn ^= bitpol_binary_gcd(p1, p2);
//            pn ^= bitpol_gcd(p1, p2);
//            jjassert( bitpol_gcd(p1, p2) == bitpol_binary_gcd(p1, p2) );
#else  // TIMING
            ulong i1 = bitpolmod_inverse(p1, p2);

            if ( i1 )
            {
                print_bin("  p2= ", p2, pn);
                cout << endl;
                print_bin("  p1= ", p1, pn);
                cout << endl;
                print_bin("  i1= ", i1, pn);
                cout << "  == p1^{-1} mod p2";
                cout << endl;
                cout << endl;

                ulong x1 = bitpolmod_mult(p1, i1, p2, h);  // p1*i1 mod p2
                jjassert( x1 == bitpol_rem(x1, p2) );
                jjassert( 1==x1 );
            }
#endif  // TIMING
        }
    }

    return 0;
}
// -------------------------

/*

Timing ( 63 == D,  53 == d,  5000 == n ):

bitpol_gcd():
 ./bin 63 53 5000  12.61s user 0.07s system 100% cpu 12.683 total

bitpol_binary_gcd():
 ./bin 63 53 5000  13.70s  // no bitscan
 ./bin 63 53 5000  10.60s  // with bitscan
 ./bin 63 53 5000   9.35s  // bitscan and swap via xor
 ./bin 63 53 5000   9.35s  // bitscan and swap via cswap_lt()

bitpol_inverse():
 ./bin 63 53 5000  23.42s  // no divrem
 ./bin 63 53 5000  20.02s  // with divrem

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/bitpol-inverse-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/bitpol-inverse-demo.cc DEMOFLAGS=-DTIMING"
/// End:

