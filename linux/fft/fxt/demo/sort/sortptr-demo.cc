
#include "sort/sortptr.h"
#include "sort/bsearchptr.h"

//#include "sort/minmaxptr.h"

#include "fxttypes.h"
#include "aux1/copy.h"  // set_seq()
#include "aux0/randf.h"  // rnd01()

#include "jjassert.h"

#include "fxtio.h"

#include "nextarg.h"  // NXARG()

//% Demo of pointer-sorting.

void
ptr_print(const char *bla, const double *f, ulong n, const double **x)
{
    cout << endl;
    if ( bla )  cout << bla << endl;

    for (ulong k=0; k<n; ++k)
    {
        double r = *x[k];

        cout.flags(ios::right);
        cout << setw(4) << k << ":  ";

        cout.precision(5);
        cout.flags(ios::left);
        cout << setw(8) << r;

        cout << "  x[" << k << "]=^=" << (x[k]-f);
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

    ulong *xx = new ulong[n];  // ! assume sizeof(ptr) == sizeof(ulong)
    const double **x = (const double **)xx;
    set_seq(xx, n, (ulong)f, sizeof(double));

    rnd01(f, n);
    ptr_print("random values:", f, n, x);

    double v = f[n/2];


//    cout << "ptr_min=" << ptr_min(/*f,*/ n, x) << endl;
//    cout << "ptr_max=" << ptr_max(/*f,*/ n, x) << endl;
//    ulong p = ptr_partition(/*f,*/ n, x);
//    ptr_print("partitioned values:", f, n, x);
//    cout << "p-ptr=" << p << endl;
//    cout << "p-max=" << ptr_max(/*f,*/ p, x) << endl;
//    cout << "p-min=" << ptr_min(/*f,*/ n-p, x+p) << endl;
//    jjassert( is_ptr_partitioned(/*f,*/ n, x, p) );


//    ptr_selection_sort(/*f,*/ n, x);
    ptr_quick_sort(/*f,*/ n, x);
    ptr_print("sorted values:", f, n, x);

    jjassert( is_ptr_sorted(/*f,*/ n, x) );

    cout << "searching for v=" << v << endl;
    ulong i = ptr_bsearch(/*f,*/ n, x, v);
    cout << "found at (ptr-)index " << (x[i]-f) << " == x[" << i << "]" << endl;

    delete [] f;
    delete [] xx;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/sort"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/sort/sortptr-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/sortptr-demo.cc DEMOFLAGS=-DTIMING"
/// End:

