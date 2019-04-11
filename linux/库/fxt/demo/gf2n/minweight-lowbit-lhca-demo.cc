
#include "bpol/lhca.h"
#include "bits/bitcombcolex.h"
#include "bpol/bitpol-irred.h"
#include "bpol/bitpol-primitive.h"
#include "bpol/gf2n.h"  // for factorization of mersenne numbers

#include "bits/print-bin.h"

#include "fxtio.h"
#include "fxttypes.h"  // ulong
#include "bits/bitsperlong.h"

#include "nextarg.h"  // NXARG()


//% Generate minimal-weight low-bit LHCA rules (LHCA:= Linear Hybrid Cellular Automaton).

// Output dependent on BITS_PER_LONG


void
print_rules(ulong rr, ulong cc, ulong pn)
{
//    print_bin("  r=", rr, pn);
    print_bin("  c=", cc, pn);
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

    ulong m = 3;
    NXARG(m, "Search rules of weight 1,2,...,m");

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
        ulong nb;  // Number of Bits
        for (nb=1; nb<=m; ++nb)
        {
            c = 0;
            r = first_comb(nb);
            do  // Try all combinations of nb bits
            {
                c = lhca2poly(r, n);
                if ( 0==bitpol_irreducible_q(c, h) )  goto next;
                if ( 0!=test_bitpol_primitive(c, h, GF2n::mfact_ ) )  goto next;

                goto print;  // (minimal weight rule only)

            next:
                r = next_colex_comb(r);
            }
            while ( r<n2 );
        }

    print:
        if ( nb<=m )  print_rules(r, c, pn);
        else          cout << "  (none)" << endl;
    }

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/minweight-lowbit-lhca-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/minweight-lowbit-lhca-demo.cc DEMOFLAGS=-DTIMING"
/// End:

