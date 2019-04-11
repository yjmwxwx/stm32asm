

#include "bpol/gf2n.h"
//demo-include "bpol/gf2n-minpoly.cc"

#include "bits/bitsperlong.h"
#include "bpol/bitpol-irred.h"
#include "bpol/bitpol-primitive.h"
#include "bits/print-bin.h"
#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()


//% Minimal polynomials in GF(2**n).

#define TEST


//#define TIMING  // uncomment to disable printing
#ifdef TIMING
#undef TEST
#endif

#ifdef TEST
#include "bpol/bitpolmod-minpoly.h"
#endif

int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "The n in GF(2**n).");

    RESTARGS("Optionally supply nonzero coefficients of field poly c.");
    ulong c = 0;
    for (ulong k=2;  (ulong)argc>k;  ++k)  c |= (1UL << strtoul(argv[k], 0, 10));
    if ( 0!=c )  c |= (1UL<<n);

    GF2n::init(n, c);
    c = GF2n::c_;

    GF2n::print_info();
    cout << endl;

    GF2n f(1);
    GF2n g( GF2n::g_ );

#ifdef TIMING

    ulong p, d;  // minpoly, degree(minpoly)
    do
    {
        d = gf2n_minpoly(f, p);
//        d = gf2n_minpoly2(f, p);
        f *= g;
    }
    while ( f!=1 );
    cout << "dummy val:" << (d&p) << endl;
    cout << " ct=" << (1UL<<n) << endl;

#else  // TIMING

    const ulong pn = n;

    cout << "   k          :";
    cout << "    f:=g**k  ord(f) Tr(f)  p:=minpoly(f)  deg(p) " << endl;
    ulong k = 0;
    do
    {
        cout << setw(4) << k;
        print_bin(" = ", k, pn); cout << " : ";
        cout << "    " << f;

        cout << "  " << setw(4) << f.order();
        cout << "    " << f.trace();

        ulong p, d;  // minpoly, degree(minpoly)
//        d = gf2n_minpoly2(f, p);
        d = gf2n_minpoly(f, p);

        print_bin("      ", p, pn+2);
        cout << "      " << setw(2) << d;

#ifdef TEST

        ulong d2, p2;
        d2 = bitpolmod_minpoly(f.v_, c, n, p2);
        ulong d3, p3;
        d3 = bitpolmod_minpoly2(f.v_, c, n, p3);

#if 0
        cout << "     d=" << setw(2) << d;
        print_bin("   p=", p, pn+2);

        cout << "     d2=" << setw(2) << d2;
        print_bin("   p2=", p2, pn+2);

        cout << "     d3=" << setw(2) << d3;
        print_bin("   p3=", p3, pn+2);
#endif

        cout<<flush;
        jjassert( d2==d );
        jjassert( p2==p );
        jjassert( p3==p );
        jjassert( d3==d );
#endif  // TEST

#if 1
        ulong h = 1UL << (d-1);  // == highest_one(p)>>1;
        if ( d < BITS_PER_LONG )
        {
            jjassert( bitpol_irreducible_q(p, h) );
            GF2n v = gf2n_eval_poly(f, p);
            jjassert( 0==v );
        }

        if ( d==n )
        {
            ulong q = test_bitpol_primitive(p, h, GF2n::mfact_);
            if ( 0!=q )  cout << " N";  // Non-primitive
        }
#endif

        f *= g;
        ++k;
        cout << endl;
    }
    while ( f!=1 );

#endif  // TIMING

    return 0;
}
// -------------------------

/*
Timing:

// Routine gf2n_minpoly():
% time ./bin 20
arg 1: 20 == n  [The n in GF(2**n).]  default=6
args 2,3,... : [Optionally supply nonzero coefficients of field poly c.]
  n = 20  GF(2^n)
  c = 1................1..1 == x^20 + x^3 + 1  (polynomial modulus)
dummy val:0
./bin 20  2.69s user 0.00s system 99% cpu 2.703 total
 ==> 2^20/2.69 == 389,805 per second


// Routine gf2n_minpoly2():
time ./bin 20
arg 1: 20 == n  [The n in GF(2**n).]  default=6
  c = 1................1..1 == x^20 + x^3 + 1  (polynomial modulus)
dummy val:0
./bin 20  12.25s user 0.00s system 99% cpu 12.260 total
 ==> 2^20/12.25 == 85,598 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

% time ./bin 20
arg 1: 20 == n  [The n in GF(2**n).]  default=6
args 2,3,... : [Optionally supply nonzero coefficients of field poly c.]
  n = 20  GF(2^n)
  c = 1................1..1 == x^20 + x^3 + 1  (polynomial modulus)
  mm= .11111111111111111111   == 1048575  =  3 * 5^2 * 11 * 31 * 41  (maximal order)
  h = .1................... (aux. bit-mask)
  g = ...................1. (element of maximal order)
  tv= ...1................. (traces of x^i)
tr1e= ...1................. (element with trace=1)

dummy val:0
./bin 20  1.76s user 0.00s system 99% cpu 1.765 total
 ==> 2^20/1.76 == 595,781 per second
*/

/*
BENCHARGS=20
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/gf2n-minpoly-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/gf2n-minpoly-demo.cc DEMOFLAGS=-DTIMING"
/// End:

