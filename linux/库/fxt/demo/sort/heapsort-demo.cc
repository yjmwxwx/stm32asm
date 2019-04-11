
#include "sort/heapsort.h"
#include "sort/sort.h"
#include "sort/bsearch.h"

#include "aux0/randf.h"  // rnd01()
#include "perm/reverse.h"

#include <cmath>

#include "fxttypes.h"
#include "jjassert.h"
#include "fxtio.h"

#include "nextarg.h"  // NXARG()

//% Demo of the heap sort algorithm.

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


//#define RSEED
#define SHOW_HEAP

int
main(int argc, char **argv)
{
#ifdef  RSEED
    cout << " rseed=" << rseed() << endl;
#endif

    ulong n = 25;
    NXARG(n, "Number of elements");

    double *f = new double[n];

    rnd01(f, n);
//    for (ulong k=0; k<n; ++k)  f[k] = floor(100.0*f[k]);  // quantize
    print("random values:", f, n);

    double v = f[n/2];

#ifdef SHOW_HEAP
    build_heap(f, n);
    print("heapified values:", f, n);
    jjassert( 0==test_heap(f, n) );
#endif  // SHOW_HEAP

    heap_sort(f, n);
    print("sorted values:", f, n);

    jjassert( is_sorted(f, n) );
//    jjassert( 0==test_heap(f, n) );  // not the case in general

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
/// make-target: "1demo DSRC=demo/sort/heapsort-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/heapsort-demo.cc DEMOFLAGS=-DTIMING"
/// End:

