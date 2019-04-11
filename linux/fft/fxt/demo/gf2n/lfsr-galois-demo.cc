
// demo-is-self-contained

#include "bpol/poly-tab.h"

#include "fxttypes.h"
#include "bits/revbin.h"
#include "bits/print-bin.h"
#include "jjassert.h"
#include "fxtio.h"
#include "nextarg.h"

#include <cstdlib>  // strtoul()


//% Linear feedback shift register: Galois setup with
//% right and left shift, polynomial c and reversed polynomial r.

ulong galois_left(ulong x, ulong c, ulong h)
{
    ulong s = x & h;
    x <<= 1;
    if ( 0!=s )  x ^= c;
    return x;
}
// -------------------------

ulong galois_right(ulong x, ulong c)
{
    ulong s =  ( x & 1UL );
    x >>= 1;
    if ( s )  x ^= (c>>1);
    return x;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Degree of polynomial modulus.");

    ulong c = 0;  // 0==> default primpoly
//    c = lowbit_primpoly[n];
    c = rand_primpoly[n];
//    c = (1UL<<n)+1+ (1UL<<(1));
//    c = minweight_primpoly[n];

    ulong h = 1UL << (n-1);  // auxiliary variable for shift register

    RESTARGS("Optionally supply nonzero coefficients of polynomial");
    if ( argc>2 )
    {
        c = 1UL<<n;
        for (ulong j=2; j<(ulong)argc; ++j)  c |= (1UL << strtoul(argv[j], 0, 10));
    }

    ulong r = revbin(c, n+1);  // reversed polynomial

    const ulong pnu  = n + 1;
    const int pn  = (int)pnu;  // jjcast

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
    cout << bstr << setw(pn) << "Lc ";
    cout << bstr << setw(pn) << "Lr ";
    cout << bstr << setw(pn) << "Rc ";
    cout << bstr << setw(pn) << "Rr ";
    cout << endl;

    ulong glc = 1,  grc = 1;  // Galois with c
    ulong glr = 1,  grr = 1;  // Galois with r
    ulong end = (1UL<<n)+1;
    for (ulong k = 1; k<end; ++k)
    {
        cout << setw(4) << k << ":  ";
        print_bin(bstr, glc, pnu);
        print_bin(bstr, glr, pnu);
        print_bin(bstr, grc, pnu);
        print_bin(bstr, grr, pnu);
        cout << endl;

        glc = galois_left(glc, c, h);
        glr = galois_left(glr, r, h);
        grc = galois_right(grc, c);
        grr = galois_right(grr, r);
    }
    cout << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/lfsr-galois-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/lfsr-galois-demo.cc DEMOFLAGS=-DTIMING"
/// End:

