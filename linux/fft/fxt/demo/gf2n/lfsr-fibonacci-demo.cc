
// demo-is-self-contained

#include "bpol/poly-tab.h"
#include "bits/parity.h"

#include "fxttypes.h"
#include "bits/revbin.h"
#include "bits/print-bin.h"
#include "jjassert.h"
#include "fxtio.h"
#include "nextarg.h"

#include <cstdlib>  // strtoul()


//% Linear feedback shift register: Fibonacci setup with
//% right and left shift, polynomial c and reversed polynomial r.

ulong fibonacci_left(ulong x, ulong c, ulong h)
{
    x <<= 1;
    ulong s = parity( x & c );
    if ( 0!=s )  x ^= 1;
    x &= ~(h<<1);  // remove excess bit at high end
    return x;
}
// -------------------------

ulong fibonacci_right(ulong x, ulong c, ulong h)
{
    ulong s = parity( x & c );
    x >>= 1;
    if ( s )  x ^= h;
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

    const ulong pn  = n + 1;
    const int pni  = (int)n + 1;

    print_bin("  c = ", c, pn+1);
    cout << " == 0x" << hex << c << dec << " == " << c ;
    cout << "  (deg = " << n << ")";
    cout << endl;
    print_bin("  r = ", r, pn+1);
    cout << " == 0x" << hex << r << dec << " == " << r ;
    cout << "  (deg = " << n << ")";
    cout << endl;

    char bstr[] = "   ";
    cout << endl;
    cout << setw(4) << "k" << ":  ";
    cout << bstr << setw(pni) << "Lc ";
    cout << bstr << setw(pni) << "Lr ";
    cout << bstr << setw(pni) << "Rc ";
    cout << bstr << setw(pni) << "Rr ";
    cout << endl;

    ulong glc = 1,  grc = 1;  // Fibonacci with c
    ulong glr = 1,  grr = 1;  // Fibonacci with r
    ulong end = (1UL<<n)+1;
    for (ulong k = 1; k<end; ++k)
    {
        cout << setw(4) << k << ":  ";
        print_bin(bstr, glc, pn);
        print_bin(bstr, glr, pn);
        print_bin(bstr, grc, pn);
        print_bin(bstr, grr, pn);
        cout << endl;

        glc = fibonacci_left(glc, c, h);
        glr = fibonacci_left(glr, r, h);
        grc = fibonacci_right(grc, c, h);
        grr = fibonacci_right(grr, r, h);
    }
    cout << endl;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/lfsr-fibonacci-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/lfsr-fibonacci-demo.cc DEMOFLAGS=-DTIMING"
/// End:

