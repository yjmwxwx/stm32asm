
#include "bpol/normalbasis.h"
#include "bpol/normal-solvequadratic.h"
// demo-include "bpol/bitpol-normal.cc"
// demo-include "bpol/normal-mult.cc"
// demo-include "bpol/normal-primpoly.cc"
// demo-include "bpol/normal-irredpoly.cc"
#include "bmat/bitmat-funcs.h"

#include "bpol/bitpol-print.h"

#include "bits/parity.h"
#include "bits/bitrotate.h"
#include "bits/print-bin.h"

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"  // ulong
#include "fxtio.h"
#include "fxtalloca.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()


//% Multiplication with a normal basis for GF(2**n).

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "The n in GF(2**n)");

    ulong c = highbit_normal_primpoly[n];  // 'x' is always a generator
    RESTARGS("Optionally supply nonzero coefficients of normal poly c");
    if ( argc>2 )  c = (1UL<<n);
    for (ulong k=2; k<(ulong)argc; ++k)  c |= (1UL << strtoul(argv[k], 0, 10));

    cout << endl;
    print_bin("Normal poly:  c=", c, n+1);
    bitpol_print(" == ", c);
    cout << endl;

    ALLOCA(ulong, M, n);  // multiplication matrix
    const bool q = bitpol_normal_q(c, n, 0, M);
    jjassert( q );
    jjassert( q==bitpol_normal2_q(c, n) );
//    bitmat_print("Multiplication matrix:  M=", M, n);
//    cout << endl;

    const ulong pn = n;
    const ulong nn = (1UL << n) - 1;

    ulong g = 1UL;  // 'x'
//    ulong g = 7UL;  // '1+x+x^2'  // for type-1 bases and n=4, n=10
    print_bin("  g=", g, pn);
    cout << endl;
    cout << endl;

    cout << "   k =       :";
    cout << "   f=g**k";
    cout << "  Tr(f)";
    cout << "   x^2+x==f";
    cout << endl;
    const ulong one = (1UL<<n)-1;  // one in normal basis representation
    ulong f = one;

    ulong k = 0;
    do
    {
        cout << setw(4) << k;
        print_bin(" = ", k, pn);  cout << " : ";
        print_bin("   ", f, pn);


        ulong x;  // solution to reduced quadratic equation
        ulong t = normal_solve_reduced_quadratic_q(f, x);  // trace is returned
        cout << "    " << ".1"[t];

        if ( 0==t )  // solve x^2+x==f
        {
//            ulong x = normal_solve_reduced_quadratic(f);
            print_bin("      x=", x, n);
        }

        f = normal_mult(f, g, M, n);  // f *= g

        ++k;
        cout << endl;
    }
    while ( f!=one );

    --k;
    cout << " k = " << k << endl;
    cout << " (2**n-1)/k = " << nn/k << endl;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/normalbasis-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/normalbasis-demo.cc DEMOFLAGS=-DTIMING"
/// End:

