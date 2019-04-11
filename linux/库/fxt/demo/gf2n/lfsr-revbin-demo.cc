
// demo-is-self-contained

#include "bpol/poly-tab.h"

#include "fxttypes.h"
#include "bits/revbin.h"
#include "bits/print-bin.h"
#include "jjassert.h"
#include "fxtio.h"
#include "nextarg.h"

#include <cstdlib>  // strtoul()


//% Generate all revbin pairs via a linear feedback shift register.


inline void revbin_next(ulong &x, ulong c, ulong &xr, ulong cr)
// if x and xr are (nonzero) n-bit words that are a revbin pair
// compute the next revbin pair.
// c must be a primitive polynomial, cr its reverse (the reciprocal polynomial).
{
    ulong s =  ( x & 1UL );
    x >>= 1;
    xr <<= 1;
    if ( s )
    {
        x ^= (c>>1);
        xr ^= (cr);
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Degree of polynomial modulus.");

    ulong c = 0;  // 0==> default primpoly
//    c = lowbit_primpoly[n];
    c = rand_primpoly[n];
//    c = (1UL<<n)+1+ (1UL<<(1));
//    c = minweight_primpoly[n];


    RESTARGS("Optionally supply nonzero coefficients of polynomial");
    if ( argc>2 )
    {
        c = 1UL<<n;
        for (ulong j=2; j<(ulong)argc; ++j)  c |= (1UL << strtoul(argv[j], 0, 10));
    }

    ulong r = revbin(c, n+1);  // reversed polynomial

    const ulong pnu  = n;
    const int pn  = (int)pnu;

    print_bin("  c = ", c, pnu+1);
    cout << " == 0x" << hex << c << dec << " == " << c ;
    cout << "  (deg = " << n << ")";
    cout << endl;
    print_bin("  r = ", r, pnu+1);
    cout << " == 0x" << hex << r << dec << " == " << r ;
    cout << "  (deg = " << n << ")";
    cout << endl;

    char bstr[] = "   ";
    cout << endl;
    cout << setw(4) << "k" << ":  ";
    cout << bstr << setw(pn) << "c ";
    cout << bstr << setw(pn) << "r ";
    cout << endl;

    ulong end = (1UL<<n)+1;

    ulong x = 1;
    ulong xr = 1 << (n-1);  // == revbin(x, n);
    ulong cr = r;
    for (ulong k = 1; k<end; ++k)
    {
        cout << setw(4) << k << ":  ";

        print_bin(bstr, x, pnu);
        print_bin(bstr, xr, pnu);
        revbin_next(x, c, xr, cr);

        cout << endl;
    }
    cout << endl;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/lfsr-revbin-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/lfsr-revbin-demo.cc DEMOFLAGS=-DTIMING"
/// End:

