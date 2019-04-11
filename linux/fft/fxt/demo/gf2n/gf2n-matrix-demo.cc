
#include "bmat/bitmat-funcs.h"
#include "bmat/bitmat-inline.h"
#include "bpol/poly-tab.h"

#include "bits/print-bin.h"
#include "fxtio.h"
#include "fxtalloca.h"
#include "fxttypes.h"  // ulong
#include "jjassert.h"

#include "nextarg.h"

#include <cstdlib>  // strtoul()


//% Matrix representation of GF(2**n).


#define PRINT_MATPOW  // uncomment to print matrix powers

int
main(int argc, char **argv)
{
//    set_fail_action(JJ_ASSERT_STOP);

    ulong n = 4;
    NXARG(n, "Degree of polynomials");

    ulong c = minweight_primpoly[n];
    c |= (1UL<<n);
    RESTARGS("Optional: give nonzero coefficients of field polynomial");
    for (ulong k=2;  (ulong)argc>k;  ++k)  c |= (1UL << strtoul(argv[k], 0, 10));

    print_bin(" c=", c, n+1);
    cout << endl;

    ALLOCA(ulong, T, n);
    ALLOCA(ulong, G, n);
    bitmat_companion(c, n, G);
//    bitmat_transpose(G, n, T);  bitmat_copy(T, n, G);
    bitmat_print("G=", G, n);

    ALLOCA(ulong, M, n);
    ALLOCA(ulong, Mi, n);
    bitmat_unit(M, n);
    for (ulong k=0; k<(1UL<<n); ++k)
    {
        cout << " k = " << setw(2) << k;

        // c0 and r0 reversed so that print_bin() gives element zero on the left:
        ulong c0 = 0;  // first column
        for (ulong j=0; j<n; ++j)  {  c0<<=1;  c0 |= (M[j] & 1UL); }
        print_bin("   c0 = ", c0, n);
        ulong r0 = M[0];  // first row
        print_bin_vec("   r0 = ", r0, n);

        ulong t = bitmat_trace(M, n);
        cout << "  t = " << ".1"[t];

        cout << endl;

        ulong qi = bitmat_inverse(M, n, Mi);
        jjassert( qi );  // matrices are invertible
        bitmat_mult_MM(M, Mi, n, T);

#ifdef PRINT_MATPOW
        bitmat_print("M_k = M^k =", M, n);
//        bitmat_print("(M_k)^(-1) = ", Mi, n);
//        bitmat_print(" id = ", T, n);
//        ALLOCA(ulong, H, n);
//        bitmat_hessenberg(M, n, H);
//        bitmat_print("H =", H, n);
//        jjassert( bitmat_is_hessenberg(H, n) );
#endif

        ulong cp = bitmat_charpoly(M, n);
        print_bin_vec(" charpoly = ", cp, n+1);  // == minpoly
        cout << endl;
        cout << endl;

        jjassert( bitmat_is_unit(T, n) );  // assert inversion works

        bitmat_mult_MM(M, G, n, T);
        bitmat_copy(T, n, M);
    }

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/gf2n-matrix-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/gf2n-matrix-demo.cc DEMOFLAGS=-DTIMING"
/// End:

