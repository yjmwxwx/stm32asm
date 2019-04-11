
#include "sort/sortidx.h"
#include "sort/bsearchidx.h"

#include "fxttypes.h"
#include "aux1/copy.h"  // set_seq()
#include "aux0/randf.h"  // rnd01()

#include "jjassert.h"

#include "fxtio.h"

#include "nextarg.h"  // NXARG()

//% Demo of index-sorting.

void
idx_print(const char *bla, const double *f, ulong n, ulong *x)
{
    cout << endl;
    if ( bla )  cout << bla << endl;

    for (ulong k=0; k<n; ++k)
    {
        double r = f[x[k]];

        cout.flags(ios::right);
        cout << setw(4) << k << ":  ";

        cout.precision(5);
        cout.flags(ios::left);
        cout << setw(8) << r;

        cout << "  x[k]=" << x[k];
        cout << endl;
    }
    cout << endl;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 25;
    NXARG(n, "Number of elements");

    double *f = new double[n];

    ulong  *x = new ulong[n];
    set_seq(x, n);

    rnd01(f, n);
    idx_print("random values:", f, n, x);

    double v = f[n/2];


//    cout << "idx_min=" << idx_min(f, n, x) << endl;
//    cout << "idx_max=" << idx_max(f, n, x) << endl;

//    ulong p = idx_partition(f, n, x);
//    idx_print("partitioned values:", f, n, x);
//    cout << "p-idx=" << p << endl;
//    cout << "p-max=" << idx_max(f, p, x) << endl;
//    cout << "p-min=" << idx_min(f, n-p, x+p) << endl;
//    jjassert( is_idx_partitioned(f, n, x, p) );


//    idx_selection_sort(f, n, x);
    idx_quick_sort(f, n, x);
    idx_print("sorted values:", f, n, x);

    jjassert( is_idx_sorted(f, n, x) );

    cout << "searching for v=" << v << endl;
    ulong i = idx_bsearch(f, n, x, v);
    cout << "found at index " << x[i] << " == x[" << i << "]" << endl;

    delete [] f;
    delete [] x;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/sort"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/sort/sortidx-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/sortidx-demo.cc DEMOFLAGS=-DTIMING"
/// End:

