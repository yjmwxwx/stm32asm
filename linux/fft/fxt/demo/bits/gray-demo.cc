
#include "bits/graycode.h"
#include "bits/parity.h"
#include "bits/print-bin.h"

#include "fxtalloca.h"
#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Binary Gray code.

ulong
print_bitset_as_set(const char *bla, ulong x, ulong n, int eq=0)
{
    ALLOCA(ulong, f, n);
    for (ulong j=0; j<n; ++j)
    {
        f[j] = x & 1;
        x >>= 1;
    }

    return  print_deltaset_as_set(bla, f, n, eq);
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n =5;
    NXARG(n, "Number of bits");

    ulong nn = 1UL << n;
    const int pdi = (int)n + 2;
    const ulong pd = n + 2;

    cout << setw(4) << "k" << ":  ";
    cout << setw(pdi+4) << "bin(k) ";
    cout << setw(pdi+4) << "g(k) ";
//    cout << setw(pd+4) << "g(g(k))";
    cout << setw(pdi+4) << "g^-1(k)";
    cout << setw(pdi+4) << "g(2*k)";
    cout << setw(pdi+4) << "g(2*k+1)";
    cout << "    ";
    cout << setw(pdi+4) << "diff(g(k),g(k-1))";
    cout << endl;

    for (ulong k=0; k<nn; ++k)
    {
        cout << setw(4) << k << ":  ";
        print_bin("    ", k, pd);
        print_bin("    ", gray_code(k), pd);
//        print_bin("    ", gray_code( gray_code (k) ) , pd);
        print_bin("    ", inverse_gray_code (k) , pd);
        print_bin("    ", gray_code(2*k), pd);
        print_bin("    ", gray_code(2*k+1), pd);

        print_bin_diff("    ", gray_code(k-1), gray_code(k), pd);
        cout << " " << ".1"[k&1];
        print_bitset_as_set("    ", gray_code(k), n);

        cout << endl;
    }

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/gray-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

