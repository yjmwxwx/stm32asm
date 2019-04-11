
// demo-is-self-contained

#include "bits/bit2pow.h"   // ld()
#include "bits/bitcount.h"
#include "bits/print-bin.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

//% Cost of binary exponentiation algorithm for full-precision numbers.


//#define TEX  // for TeX output

#ifdef TEX
#define SEP   " & "
#define ENDL  "  \\qquad \\\\\n"
#else
#define SEP   "   "
#define ENDL  "\n"
#endif

int
main(int argc, char **argv)
{
    ulong n = 40;
    NXARG(n, "List costs for exponents up to n");
    ulong pn = next_exp_of_2(n);

    cout << "   e   bin(e)   #S   #M     #F    #C" << endl;

    for (ulong e=1; e<=n; ++e)
    {
        ulong nm = bit_count(e) - 1;  // number of multiplications
        ulong ns = ld(e);            // number of squarings
        ulong nfft = 3*nm + 2*ns;    // number of FFTs
        // number of FFTs with left-to-right exponentiation and FFT caching:
        ulong ncfft = 2*nm + 2*ns + (nm!=0);
        cout << setw(4) << e;
        cout << SEP;
#ifdef TEX
        print_bin("{\\tt ", e, pn);
        cout << "}";
#else
        print_bin("", e, pn);
#endif
        cout << SEP;
        cout << setw(2) << ns;
        cout << SEP;
        cout << setw(2) << nm;
        cout << SEP;
        cout << setw(4) << nfft;
        cout << SEP;
        if ( ncfft!=nfft ) cout << setw(4) << ncfft;
        else               cout << "    ";
        cout << ENDL;
#ifdef TEX
        if ( (0==e%4) && (e!=n) )  cout << "\\hline" << endl;
#endif
    }

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/arith"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/arith/power-costs-demo.cc"
/// make-target2: "1demo DSRC=demo/arith/power-costs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

