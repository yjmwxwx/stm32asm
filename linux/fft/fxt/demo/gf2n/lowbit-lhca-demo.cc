
#include "bpol/lhca.h"
#include "bpol/bitpol-irred.h"
#include "bpol/bitpol-primitive.h"
#include "bpol/gf2n.h"  // for factorization of mersenne numbers

#include "bits/print-bin.h"

#include "fxtio.h"
#include "fxttypes.h"  // ulong
#include "bits/bitsperlong.h"

#include "nextarg.h"  // NXARG()


//% Generate low-bit LHCA rules (LHCA:= Linear Hybrid Cellular Automaton).

// Output dependent on BITS_PER_LONG

void
print_rules(ulong rr, ulong cc, ulong pn)
{
    print_bin("  c=", cc, pn);
    print_bin("  r=", rr, 10);
    print_idx_seq("  r= ", rr);
//    print_idx_seq("  c= ", cc);
    cout << endl;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong nn = BITS_PER_LONG - 1;
    NXARG(nn, "Max number of bits");
    ulong pn = nn + 1;

    cout << setw((int)pn) << "c = polynomial";
    cout << "           r = LHCA rule";
    cout << endl;

    for (ulong n=1; n<=nn; ++n)
    {
        ulong r=0, c=0;
        cout << setw(4) << n << ":";
        ulong h = 1UL << (n-1);
        ulong n2 = h<<1;
        GF2n::init(n);  // for factorization of Mersenne number
        for (r=1; r<n2; ++r)
        {
            c = lhca2poly(r, n);
            if ( 0==bitpol_irreducible_q(c, h) )  continue;
            if ( 0!=test_bitpol_primitive(c, h, GF2n::mfact_ ) )  continue;
            break;
        }

        print_rules(r, c, pn);
    }

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/lowbit-lhca-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/lowbit-lhca-demo.cc DEMOFLAGS=-DTIMING"
/// End:

