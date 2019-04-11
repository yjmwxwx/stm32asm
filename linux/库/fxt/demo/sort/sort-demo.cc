
#include "sort/sort.h"
#include "sort/bsearch.h"

#include "fxttypes.h"
#include "aux0/randf.h"  // rnd01()

#include "jjassert.h"

#include "fxtio.h"

#include "nextarg.h"  // NXARG()

//% Demo of sort and search routines.

void
print(const char *bla, const double *f, ulong n)
{
    cout << endl;
    if ( bla )  cout << bla << endl;

    for (ulong k=0; k<n; ++k)
    {
        double r = f[k];

        cout.flags(ios::right);
        cout << setw(4) << k << ":  ";

        cout.precision(5);
        cout.flags(ios::left);
        cout << setw(8) << r;
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

    rnd01(f, n);
    print("random values:", f, n);

    double v = f[n/2];


//    ulong p = partition(f, n);
//    print("partitioned values:", f, n);
//    cout << "p=" << p << endl;
//    cout << "p-max=" << max(f, p) << endl;
//    cout << "p-min=" << min(f+p, n-p) << endl;


//    selection_sort(f, n);
    quick_sort(f, n);
    print("sorted values:", f, n);

    jjassert( is_sorted(f, n) );

    cout << "searching for v=" << v << endl;
    ulong i = bsearch(f, n, v);
    jjassert( i<n );
    cout << "found at index " << i << endl;

    delete [] f;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/sort"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/sort/sort-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/sort-demo.cc DEMOFLAGS=-DTIMING"
/// End:

