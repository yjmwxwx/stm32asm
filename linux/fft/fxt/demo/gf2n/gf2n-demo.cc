
#include "bpol/gf2n.h"
//demo-include "bpol/gf2n.cc"

#include "bits/print-bin.h"
#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "jjassert.h"

#include <cstdlib>  // strtoul()


//% Arithmetics over GF(2**n).

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "degree of field (n>=2)");
    jjassert( n>=2 );

    ulong c = 0;
    RESTARGS("Optionally supply nonzero coefficients of field poly c");
    for (ulong k=2;  (ulong)argc>k;  ++k)  c |= (1UL << strtoul(argv[k], 0, 10));
    if ( 0!=c )  c |= (1UL<<n);

//    bitmat_print("NT=", p2n_tab, n);

    GF2n::init(n, c);

    GF2n::print_info();
    cout << "" << endl;

    GF2n f(1);
    GF2n g( GF2n::g_ );

#ifndef TIMING
    cout << "      k  :    f:=g**k  Tr(f)    ord(f)     f*f    sqrt(f)" << endl;
#endif
    ulong k = 0;
    do
    {
        ulong t = f.trace();
        ulong r = f.order();
        GF2n s = f.sqr();
        GF2n q = f.sqrt();

#ifndef TIMING
        const ulong pn = n;
        print_bin("    ", k, pn); cout << " : ";
        cout << "     " << f;
        cout << "     " << t;
        cout << "     " << setw(4) << r;
        cout << "    ";
        cout << "    " << s;
        cout << "    " << q;
#endif
        jjassert( q*q==f );
        jjassert( f*f==s );
        jjassert( t<=1 );
        jjassert( r<=GF2n::mm_ );

        GF2n i = f.inv();
//        cout << "    ";
//        cout << "  i= " << i;
        jjassert( i.inv() == f );

        GF2n e = f.pow(GF2n::mm_);
        jjassert( 1==e );

#ifndef TIMING
        cout << endl;
#endif
        f *= g;
        ++k;
    }
    while ( f!=1 );

#ifdef TIMING
    cout << " ct=" << (1UL<<n) << endl;  // todo: fold out asserts with timing
#endif

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 20
arg 1: 20 == n  [degree of field]  default=4
args 2,3,... : [Optionally supply nonzero coefficients of field poly c]

------------------------------------------------------------
  n = 20  GF(2^n)
  c = 1................1..1 == x^20 + x^3 + 1  (polynomial modulus)
  mm= .11111111111111111111   == 1048575  =  3 * 5^2 * 11 * 31 * 41  (maximal order)
  h = .1................... (aux. bitmask)
  g = ...................1. (element of maximal order)
  tv= ...1................. (traces of x^i)
tr1e= ...1................. (element with trace=1)
./bin 20  13.37s user 0.00s system 99% cpu 13.372 total

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 20
arg 1: 20 == n  [degree of field (n>=2)]  default=4
args 2,3,... : [Optionally supply nonzero coefficients of field poly c]
  n = 20  GF(2^n)
  c = 1................1..1 == x^20 + x^3 + 1  (polynomial modulus)
  mm= .11111111111111111111   == 1048575  =  3 * 5^2 * 11 * 31 * 41  (maximal order)
  h = .1................... (aux. bit-mask)
  g = ...................1. (element of maximal order)
  tv= ...1................. (traces of x^i)
tr1e= ...1................. (element with trace=1)
./bin 20  9.77s user 0.00s system 99% cpu 9.771 total

*/

/*
BENCHARGS=20
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/gf2n-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/gf2n-demo.cc DEMOFLAGS=-DTIMING"
/// End:

