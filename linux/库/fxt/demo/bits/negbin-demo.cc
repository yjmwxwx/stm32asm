
#include "bits/negbin.h"
#include "bits/graycode.h"

#include "bits/bitlow.h"
#include "bits/print-bin.h"
#include "perm/permq.h"  // is_valid_permutation()

#include "fxtio.h"
#include "jjassert.h"
#include "fxttypes.h"  // ulong

#include "nextarg.h"



//% Representation in radix(-2).
// see HAKMEM item 128.


int
main(int argc, char **argv)
{
    ulong ldn = 5;
    NXARG(ldn, "Number of bits");
    ulong n = 1UL<<ldn;
    const ulong pn = ldn + 2;
    const int pni = (int)ldn + 2;
    ulong *f = new ulong[n];

//    ulong gg = 0;
    cout << setw(3) << "  k :";
    cout << setw(pni+2) << "bin(k)";
    cout << "  ";
    cout << setw(pni+2) << "m=bin2neg(k)";
    cout << "  ";
    cout << setw(pni+2) << "g=gray(m)";
    cout << setw(3+2) << "   dec(g)";
    cout << endl;

    for (ulong k=0; k<n; ++k)
    {
        ulong m = bin2neg(k);   // A005351
        ulong g = gray_code(m);
        ulong bg = neg2bin(g);
        f[k] = bg;
//        if ( g & (g>>1) )  continue;  // Gray code for Fibonacci words

        cout << setw(3) << k;
        print_bin(":  ", k, pn);
        print_bin("    ", m, pn);
        print_bin("    ", g, pn);

//        print_bin("  ", g^gg, pn);  // Ruler function
//        cout << "%" << 1+lowest_one_idx(g^gg) << "%";

//        print_bin("    ", bg, pn);
        cout << "    " << setw(4) << bg;  // A000000

        if ( is_valid_permutation(f, k+1) )  cout << " <= " << k;

        cout << endl;

        jjassert( neg2bin(m) == k );
//        gg = g;
    }

    // sequence of fixed points:
//    for (ulong k=0; k<n/2; ++k)
//    {
//        ulong fx = negbin_fixed_point(k);
//        cout << setw(4) << k << ": ";
//        print_bin("    ", fx, pn);
//        cout << " == " << setw(4) << fx;
//        cout << endl;
//    }

//    for (ulong a=-n; (long)a<(long)n; ++a)
//    {
////        cout << " a=" << a << endl;
//        for (ulong b=-n; (long)b<(long)n; ++b)
//        {
////            cout << " b=" << b << endl;
//            ulong t = negbin_add(a, b);
////            print_bin("    ", t , pn);
//            jjassert( neg2bin(t) == neg2bin(a)+neg2bin(b) );
//        }
//    }


    cout << endl;

    delete [] f;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/negbin-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/negbin-demo.cc DEMOFLAGS=-DTIMING"
/// End:

