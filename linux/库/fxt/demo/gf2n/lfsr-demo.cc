
#include "bpol/lfsr.h"
#include "bpol/poly-tab.h"

#include "fxttypes.h"
#include "bits/print-bin.h"
#include "jjassert.h"
#include "fxtio.h"
#include "nextarg.h"

#include <cstdlib>  // strtoul()


//% Linear feedback shift register.

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Degree of polynomial modulus.");

    ulong c = 0;  // 0==> default primpoly
    c = lowbit_primpoly[n];
//    c = rand_primpoly[n];
//    c = (1UL<<n)+1+ (1UL<<(1));
//    c = minweight_primpoly[n];

    RESTARGS("Optionally supply nonzero coefficients of polynomial");
    if ( argc>2 )
    {
        c = 1UL<<n;
        for (ulong j=2; j<(ulong)argc; ++j)  c |= (1UL << strtoul(argv[j], 0, 10));
    }

//    ulong showprev = 0;
//    if ( argc>3 )  showprev = 1;


    lfsr srs(n, c);

    ulong pn  = n;

    print_bin("  c = ", srs.c_, pn+1);
    cout << " == 0x" << hex << srs.c_ << dec << " == " << srs.c_ ;
    cout << "  (deg = " << (srs.n_) << ")";
    cout << endl;

    ulong end = srs.max_period();
    ulong a = srs.get_a(), a1 = a;
    for (ulong k=0; k<end; ++k)
    {
        ulong w = srs.get_w();

        cout << setw(4) << k << "  ";
//        print_bin(" = ", k, pn);

        cout << "  w = " << setw(4) << w;
        print_bin("  = ", w, pn);
        cout << "  " << (a&1 ? '1' : '.');
        print_bin("  ", a, pn);
        cout << " = " << setw(4) << a;
        cout << " = a";

//        if ( showprev )
#if 0
        {
            srs.prev();
            ulong pw = srs.get_w();
            ulong pa = srs.get_a();

            print_bin("    pa= ", pa, pn);
            print_bin("  pw= ", pw, pn);

            srs.next();
            ulong w2 = srs.get_w();
            ulong a2 = srs.get_a();

            jjassert( a2==a );
            jjassert( w2==w );
        }
#endif

        srs.next();
        a = srs.get_a();


        if ( a==a1 )  jjassert( k+1==end );

        cout << endl;
    }

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/lfsr-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/lfsr-demo.cc DEMOFLAGS=-DTIMING"
/// End:

