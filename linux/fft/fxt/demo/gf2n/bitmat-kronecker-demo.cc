
#include "bmat/bitmat-funcs.h"
#include "bmat/bitmat-inline.h"
#include "bpol/bitpol-irred.h"
#include "bpol/bitpol-primitive.h"
#include "bpol/bitpol-order.h"
#include "bpol/all-irredpoly.h"
#include "mod/factor.h"
#include "mod/mersenne.h"

#include "aux0/gcd.h"
#include "bits/print-bin.h"

#include "bits/bitsperlong.h"
#include "fxttypes.h"  // ulong

#include "fxtio.h"
#include "fxtalloca.h"

#include "nextarg.h"

//% Irreducible polynomials and Kronecker products of their companion matrices.

// Option: whether only primitive polynomials are used:
//#define NEXT next_primitive
#define NEXT next


int
main(int argc, char **argv)
{
    ulong n1 = 5;
    NXARG(n1, "degree 1");

    ulong n2 = 6;
    NXARG(n2, "degree 2");

    ulong nk = n1 * n2;
    cout << "  n1=" << n1;
    cout << "  n2=" << n2;
    cout << "  nk=n1*n2=" << nk;
    cout << endl;

//    if ( 1 != gcd(n1, n2) )
//    {
//        cout << "gcd(n1, n2) should equal 1." << endl;
//        return 1;
//    }

    if ( nk > BITS_PER_LONG )
    {
        cout << "Kronecker products won't fit into type ulong." << endl;
        return 2;
    }



    all_irredpoly ip1(n1);
    all_irredpoly ip2(n2);

    ALLOCA(ulong, M1, n1);
    ALLOCA(ulong, M2, n2);
    ALLOCA(ulong, K, nk);
    ALLOCA(ulong, H, nk);  // Hessenberg form of K

    ulong hk = 1UL << (nk-1);  // mask for testing irreducibility
    factorization F;
    ulong mers = (hk<<1) - 1;
    F.make_factorization( mers , mersenne_prime_factor_tab);
    cout << " F = " << F << " == mers = " << mers << endl;

    ulong p1 = ip1.data();
    do
    {
        print_bin_vec(" +++++++ p1 = ", p1, n1+1);
        cout << endl;
        bitmat_companion(p1, n1, M1);

        ip2.init(n2);
        ulong p2 = ip2.data();
        do
        {
            print_bin_vec("p2 = ", p2, n2+1);
            bitmat_companion(p2, n2, M2);

            bitmat_kronecker(M1, n1, M2, n2, K);
            ulong pk;

//            pk = bitmat_charpoly(K, nk);  // =^=
            bitmat_hessenberg(K, nk, H);
            pk = bitmat_hessenberg2charpoly(H, nk);
//            bitmat_print(" K=", K, nk);
//            bitmat_print(" H=", H, nk);

            print_bin_vec("  pk = ", pk, nk+1);
            cout << "  ";
            ulong iq = bitpol_irreducible_q(pk, hk);
            cout << ( iq ? "I" : "R" );

            if ( iq )
            {
                // Resulting polynomials are never primitive:
                // ulong pq = 0;
                // pq = (0==test_bitpol_primitive(pk, hk, F));
                // cout << ( pq ? "P" : " " );
                ulong r = bitpol_order(pk, hk, F);
                cout << "  r=" << r << " = mers/" << mers/r;
            }

            cout << endl;

            p2 = ip2.NEXT();
        }
        while ( p2 );

        p1 = ip1.NEXT();
    }
    while ( p1 );

    cout << endl;


    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/bitmat-kronecker-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/bitmat-kronecker-demo.cc DEMOFLAGS=-DTIMING"
/// End:

