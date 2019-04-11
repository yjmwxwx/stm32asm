

#include "sort/radixsort.h"  // counting_sort()
// demo-include "sort/radixsort.cc"

#include "sort/sort.h"  // is_sorted()
#include "nextarg.h"  // NXARG()
#include "bits/print-bin.h"  // print_bin()

#include "jjassert.h"
#include "fxtio.h"
#include "fxtalloca.h"
#include "restrict.h"
#include "fxttypes.h"  // ulong

//% Radix sort and counting sort.

static void
vec_print_bin(const char *bla, const ulong *f, ulong n, ulong pn)
{
    if ( bla )  cout << bla << endl;
    for (ulong k=0; k<n; ++k)
    {
//        cout << setw(3) << k << ": ";
        cout << "     ";
        print_bin("  ", f[k], pn);
        cout << endl;
    }
    cout << endl;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "Number of elements.");

    ulong nb = 2;
    NXARG(nb, "Number of bits sorted with each step.");

    ulong tnb = 6;
    NXARG(tnb, "Total number of bits.");
    ulong tm = (1UL<<tnb)-1;  // mask

    ulong *f = new ulong[n];
    ulong *g = new ulong[n];
    for (ulong k=0; k<n; ++k)  f[k] = ((k<<4)-3*k-5) & tm;

//    for (ulong k=0; k<n; ++k)  g[k]=f[k];
//    radix_sort(g,n);
//    jjassert( is_sorted(g,n) );

    ulong pn = tnb;

    vec_print_bin("  Input: ", f, n, pn);

    ulong m = (1UL<<nb) - 1;
    for (ulong k=1, b0=0;  b0<tnb;  ++k, b0+=nb)
    {
        counting_sort_core(f, n, g, b0, m);
        swap2(f, g);
        cout << "  Stage " << k << ": " << endl;
        print_bin("   m = ", m<<b0, pn);
        cout << endl;
        vec_print_bin(0, f, n, pn);
        jjassert( is_counting_sorted(f, n, b0, m) );
    }
    jjassert( is_sorted(f, n) );

    delete [] f;
    delete [] g;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/sort"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/sort/radixsort-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/radixsort-demo.cc DEMOFLAGS=-DTIMING"
/// End:

