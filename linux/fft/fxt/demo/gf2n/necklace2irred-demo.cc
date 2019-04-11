
#include "bpol/necklace2bitpol.h"
#include "bits/bitcyclic-minmax.h"
#include "bits/bitcyclic-period.h"

#include "aux0/gcd.h"

#include "bpol/poly-tab.h"
#include "bpol/bitpol-print.h"
#include "bpol/bitpol-irred.h"

#include "bits/print-bin.h"

//#include "jjassert.h"
#include "fxttypes.h"  // ulong
#include "fxtio.h"

#include "nextarg.h"  // NXARG()

#include <cstdlib>  // strtoul()


//% Convert necklaces to binary polynomials, especially irreducible and primitive ones.


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Degree of polynomials");

    ulong c = 0;  // 0==> default primpoly
//    c = lowbit_primpoly[n];
    c = rand_primpoly[n];
//    c = (1UL<<n)+1+ (1UL<<(1));
//    c = minweight_primpoly[n];

    RESTARGS("Optionally supply nonzero coefficients of field poly c");
    if ( argc>2 )
    {
        c = 1UL<<n;
        for (ulong j=2; j<(ulong)argc; ++j)  c |= (1UL << strtoul(argv[j], 0, 10));
        n = highest_one_idx(c);
    }

    bitpol_print("modulus= ", c);

    ulong h = highest_one(c) >> 1;
    if ( bitpol_irreducible_q(c, h) )  cout << " Irreducible." << endl;

    const ulong a = 2;  // 'x'
    necklace2bitpol n2b(n, c, a);
    const ulong mers = (1UL<<n)-1;
    for (ulong b = 1; b<(h<<1); ++b)
    {
//        cout << a << ": --------- " << endl;
        ulong per = bit_cyclic_period(b, n);
        ulong bm = bit_cyclic_min(b, n);
//        if ( b != bm )  continue;
//        if ( per<n )  continue;

        ulong p2 = n2b.poly(b);

        print_bin("    b=", b, n+2);
        cout << " " << per;
        cout << " " << (b==bm?'m':' ');
        print_bin("    e=", n2b.e_, n+1);
        print_bin("    p=", p2, n+2);
        if ( 0==bitpol_irreducible_q(p2, h) )  cout << " reducible";
        if ( 1UL==gcd(b, mers) )  cout << " P";  // only true for primitive c
        cout << endl;
    }
    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/necklace2irred-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/necklace2irred-demo.cc DEMOFLAGS=-DTIMING"
/// End:

