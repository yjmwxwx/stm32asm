
// demo-is-self-contained

#include "bits/print-bin.h"

#include "fxttypes.h"
#include "nextarg.h"
#include "jjassert.h"
#include "fxtio.h"


//% Multiplication of binary polynomials.

static ulong str2bpol(const char *str, ulong &deg)
{
    for (deg=0; str[deg]; ++deg) {;}
    --deg;

    ulong a = 0, m=1UL;
    for (ulong k=0; k<=deg; ++k) { if (str[deg-k]=='1') a|=m; m<<=1; }

    return a;
}
// -------------------------

static void printsp(ulong n)
{
    for (ulong k=0; k<n; ++k)  cout << " ";
}
// -------------------------

int
main(int argc, char **argv)
{
    char *sa;
    NXARGSTR(sa, "Multiplier", "1..11.111");
    char *sb;
    NXARGSTR(sb, "Multiplicand", "11.1.1");
//    bool q=1;
//    NXARG(q,"0=>ordinary prod. (with carry), else prod. as binary polynomials");

    ulong da, db;
    ulong a = str2bpol(sa, da);
    ulong b = str2bpol(sb, db);
    ulong t = 0;  // product of binary polynomials
    ulong c = 0;  // ordinary product

    cout << endl;
    print_bin(" a= ", a, da+1);
    print_bin("  *  b= ", b, db+1);
    cout << endl;
    cout << endl;

    ulong s = 0;
    while ( b )
    {
        if ( b & 1 )
        {
            t ^= a;  // product of binary polynomials
            c += a;  // ordinary product
        }

        printsp(db-s);
        if ( b&1 )  print_bin("    ", a, da+1+s);
        else  printsp(4+da+1+s);
        cout << "   "  << (b&1) ;
        if ( b&1 )  // omit no-ops
        {
            print_bin("    t= ", t, da+db+1);
            print_bin("   c= ", c, da+db+2);
        }
        cout << endl;
        ++s;


        b >>= 1;
        a <<= 1;
    }

    cout << endl;
    print_bin("Without carries:   t= ", t, da+db+1);
    cout << endl;
    print_bin("With carries:      c=", c, da+db+1+1);
    cout << endl;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/bitpolmult-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/bitpolmult-demo.cc DEMOFLAGS=-DTIMING"
/// End:

