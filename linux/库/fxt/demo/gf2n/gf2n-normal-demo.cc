
#include "bpol/gf2n.h"
//demo-include "bpol/gf2n.cc"

#include "bits/print-bin.h"
#include "bmat/bitmat-funcs.h"
#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "jjassert.h"

#include <cstdlib>  // strtoul()


//% Arithmetics over GF(2**n): conversion to normal basis representation.

void
doit(ulong n)
{
    GF2n::print_info();
    cout << "" << endl;
    bitmat_print("P2N=", GF2n::p2n_tab, n);
    bitmat_print("N2P=", GF2n::n2p_tab, n);

    jjassert( bitmat_inverse_q(GF2n::p2n_tab, n, GF2n::n2p_tab) );

    ulong pn = n;
    GF2n f(1);
    GF2n g( GF2n::g_ );

    cout << "  k = bin(k):   f= g**k   == (normal)    t=trace(f)   " << endl;
    ulong k = 0;
    do
    {
        ulong fn = f.get_normal();
        GF2n fng;  fng.v_ = fn;  // trickery for printing
        ulong t = f.trace();

        cout << setw(3) << k;
        print_bin(" = ", k, pn); cout << " : ";
        cout << "  f= " << f;
        cout << "  ==  " << fng;
        cout << "      t= " << t;
        jjassert( t==parity(fn) );

        ulong u = GF2n::n2p( fn );
        jjassert( f==u );

        cout << endl;

        f *= g;
        ++k;
    }
    while ( f!=1 );
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "degree of field");

    ulong c = 0;
    RESTARGS("Optionally supply nonzero coefficients of field poly c");
    for (ulong k=2;  (ulong)argc>k;  ++k)  c |= (1UL << strtoul(argv[k], 0, 10));
    if ( 0!=c )  c |= (1UL<<n);

    GF2n::init(n, c, 1);
    doit(n);

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/gf2n-normal-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/gf2n-normal-demo.cc DEMOFLAGS=-DTIMING"
/// End:

