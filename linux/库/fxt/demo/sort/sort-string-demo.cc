
#include "sort/sortidxfunc.h"
#include "sort/minmaxidxfunc.h"

#include <cstring>  // strcmp()

#include "fxtio.h"
#include "jjassert.h"
#include "fxtalloca.h"
#include "fxttypes.h"  // ulong

//% index sorting with comparison function: string sorting.


typedef const char * Cstr;

Cstr strings[] = {
    "this",
    "is",
    "a",
    "little",
    "index",
    "sort",
    "demo:",
    "ah",
    "bee",
    "and",
    "zee.",
    "a deer.",
    "a beer.",
    "a dot.",
    0  // zero terminated
};
// -------------------------

void idx_print(const char *bla, const ulong *x, ulong n)
{
    cout << bla << endl;
    for (ulong k=0; k<n; ++k)
    {
        cout << setw(4) << x[k] << ":  ";
        cout << "\"" << strings[x[k]] << "\"" << endl;
    }
    cout << endl;
}
// -------------------------


int my_strcmp(const Cstr &a, const Cstr &b)
{
    return  strcmp(a, b);
}
// -------------------------

int
main()
{
    ulong n = 0;
    while ( strings[n] )  ++n;
    ALLOCA(ulong, x, n);
    for (ulong k=0; k<n; ++k)  x[k] = k;

    idx_print("--- Unsorted: ---", x, n);
//    idx_selection_sort<Cstr>(strings, n, x, my_strcmp);
    idx_quick_sort<Cstr>(strings, n, x, my_strcmp);
    idx_print("--- Sorted: ---", x, n);

    jjassert( is_idx_sorted(strings, n, x, my_strcmp) );

    cout << "------" << endl;
    cout << "Min: " << idx_min(strings, n, x, my_strcmp) << endl;
    cout << "Max: " << idx_max(strings, n, x, my_strcmp) << endl;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/sort"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/sort/sort-string-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/sort-string-demo.cc DEMOFLAGS=-DTIMING"
/// End:

