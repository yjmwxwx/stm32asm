
#include "bpol/bitpolmod-arith.h"
#include "bpol/poly-tab.h"

#include "bits/bitcyclic-minmax.h"
#include "bpol/bitpol-print.h"

#include "fxttypes.h"
#include "bits/print-bin.h"
#include "nextarg.h"
#include "jjassert.h"
#include "fxtio.h"


//% Modular multiplication of binary polynomials.


//       deg mult  mod-poly
//        n  p       c
// ./bin  9  7     0 9 1
// ./bin  6  3     0 6 3

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "degree of polynomial modulus");

    ulong c = 0;
    c = lowbit_primpoly[n];
    NXARG(c, "polynomial modulus");

    ulong p = 2;  // max period with c primitive
    NXARG(p, "multiplier");


    const ulong pn  = n;

    bitpol_print("modulus = ", c);
    print_bin(" = ", c, pn+1);
    cout << " == 0x" << hex << c << dec;
    cout << "  (deg = " << (n) << ")";
    cout << endl;

    bitpol_print("multiplier = ", p);
    print_bin(" = ", p, pn+1);
    cout << " == 0x" << hex << p << dec;
    cout << endl;
    cout << endl;

    const ulong h = 1UL << (n-1);
    ulong w = 0;
    ulong a = 1;
    ulong a1 = a;
    ulong ct = 0;
    do
    {
        cout << setw(6) << ct << "  ";
        print_bin("  a= ", a, pn);
        cout << "    ";
        cout << (a&1 ? '1' : '.');  // SRS
        w <<= 1;  w |= (a&1);

        a = bitpolmod_mult(a, p, c, h);
        ++ct;

        cout << endl;
    }
    while ( (a!=0) && (a!=a1) );

    ulong nn = 1UL << n;
    w = bit_cyclic_min(w, nn-1);
    print_bin("  w= ", w, nn-1);

    cout << "   period = " << ct;
    if ( ct==(1UL<<n)-1 )  cout << "  [maximal]";
    cout << endl;

    return 0;
}
// -------------------------

// for m in $(seq 2 63); do ./bin 5 37 $m; done | g w= | sort | uniq
//  w= ..............................1 period = 1
//  w= ....1..1.11..11111...11.111.1.1 period = 31  [maximal]
//  w= ....1.1.111.11...11111..11.1..1 period = 31  [maximal]
//  w= ....1.11.1.1...111.11111..1..11 period = 31  [maximal]
//  w= ....11..1..11111.111...1.1.11.1 period = 31  [maximal]
//  w= ....11.1.1..1...1.11111.11..111 period = 31  [maximal]
//  w= ....111..11.11111.1...1..1.1.11 period = 31  [maximal]

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/bitpolmodmult-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/bitpolmodmult-demo.cc DEMOFLAGS=-DTIMING"
/// End:

