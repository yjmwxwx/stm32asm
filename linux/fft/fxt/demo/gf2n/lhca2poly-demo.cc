
#include "bpol/lhca.h"
#include "bpol/bitpol-irred.h"
//#include "bpol/minweightlhcarule.cc"

#include "bpol/bitpol-primitive.h"  // test needs factorization
#include "bpol/gf2n.h"  // for factorization of mersenne numbers

#include "bits/print-bin.h"

#include "jjassert.h"
#include "fxtio.h"

#include "fxttypes.h"
#include "bits/bitsperlong.h"

#include "nextarg.h"  // NXARG()

//% Convert minimum-weight LHCA rules to binary polynomials.

// Output dependent on BITS_PER_LONG

void
print_rules(ulong rr, ulong cc, ulong pn)
{
    print_bin("  c=", cc, pn);
//    print_bin("  r=", rr, pn);
    print_idx_seq("  r= ", rr);
//    print_idx_seq("  c= ", cc);
    cout << endl;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = BITS_PER_LONG - 1;
    NXARG(n, "Max number of bits");
    ulong pn  = n + 1;

    cout << setw((int)pn) << "c = polynomial";
    cout << "           r = LHCA rule";
    cout << endl;

    ulong h = 1;
    for (ulong k=1; k<=n; ++k)
    {
        GF2n::init(k);  // for factorization of Mersenne number
        cout << setw(4) << k << ":";

        ulong r = minweight_lhca_rule[k];

        ulong c = lhca2poly(r, k);
        print_rules(r, c, pn);

        jjassert( bitpol_irreducible_q(c, h) );
        jjassert( 0==test_bitpol_primitive(c, h, GF2n::mfact_) );

//        ulong c2 = lhca2poly(~r, k);
//        jjassert( c2==bitpol_compose_xp1(c) );

        h <<= 1;
    }

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/lhca2poly-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/lhca2poly-demo.cc DEMOFLAGS=-DTIMING"
/// End:

