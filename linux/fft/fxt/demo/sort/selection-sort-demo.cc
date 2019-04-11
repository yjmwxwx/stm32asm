
#include "sort/sort.h"

#include "aux1/copy.h"
#include "fxttypes.h"
#include "jjassert.h"
#include "fxtio.h"
#include "nextarg.h"  // NXARGSTR()

//% Demo of the selection sort algorithm.

static void print_str(const char *f, ulong i, ulong n)
{
//    i = 0;
    cout << "[";
    for (ulong k=0; k<i; ++k)  cout << "  ";
    for (ulong k=i; k<n; ++k)  cout << " " << f[k];
    cout << " ]";
    cout << endl;

//    for (ulong k=0; k<i; ++k)  cout << "  ";
//    cout << "^" << endl;
}
// -------------------------

void demo_selection_sort(char *f, ulong n)
{
    print_str(f, 0, n);
    for (ulong i=0; i<n; ++i)
    {
        char v = f[i];
        ulong m = i;  // position of minimum
        ulong j = n;
        while ( --j > i )  // search (index of) minimum
        {
            if ( f[j]<v )
            {
                m = j;
                v = f[m];
            }
        }

//        cout << "swap2( #" << i << ", #" << m << ")" << endl;
//        cout << "swap2( " << f[i] << ", " << f[m] << ")" << endl;
        swap2(f[i], f[m]);
        print_str(f, i, n);
    }
    print_str(f, 0, n);
}
// -------------------------


int
main(int argc, char **argv)
{
    char *str;
    NXARGSTR(str, "String to sort", "nowsortme");
    ulong n = strlen(str);
    char *f = new char[n+1];
    acopy(str, f, n);

    demo_selection_sort(f, n);

    jjassert( is_sorted(f, n) );

    delete [] f;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/sort"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/sort/selection-sort-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/selection-sort-demo.cc DEMOFLAGS=-DTIMING"
/// End:

