
#include "sort/merge-sort.h"  // merge()  // merge-sort duplicated here

#include "sort/sort.h"  // selection_sort(), is_sorted()

#include "aux1/copy.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "jjassert.h"
#include "nextarg.h"  // NXARGSTR()

//% Demo of the 4-way merge sort algorithm.


char *ff;
ulong nn;
static void PRINT(const char *f, ulong i, ulong n)
{
    ulong d = (ulong)(f - ff);
    f = ff;
//    cout << "  range0[" << i << ", " << n << "] : ";
    i += d;  n += d;

//    cout << "  range[" << i << ", " << n << "] : ";
    cout << "[";
    for (ulong k=0; k<i; ++k)  cout << "  ";
    for (ulong k=i; k<n; ++k)  cout << " " << f[k] << "";
    for (ulong k=n; k<nn; ++k)  cout << "  ";
    cout << " ]";
    cout << endl;
}
// -------------------------



template <typename Type>
void demo_merge_sort_rec4(Type *f, ulong n, Type *t)
{
    if ( n<8 )  // threshold must be at least 8
    {
        selection_sort(f, n);
        return;
    }

    // left and right half:
    const ulong na = n>>1;
    const ulong nb = n - na;

    // left quarters:
    const ulong na1 = na>>1;
    const ulong na2 = na - na1;
    demo_merge_sort_rec4(f, na1, t);
    demo_merge_sort_rec4(f+na1, na2, t);

    // right quarters:
    const ulong nb1 = nb>>1;
    const ulong nb2 = nb - nb1;
    demo_merge_sort_rec4(f+na, nb1, t);
    demo_merge_sort_rec4(f+na+nb1, nb2, t);


    cout << "F: ";  PRINT(f, 0, na1);
    cout << "F: ";  PRINT(f+na1, 0, na2);

    // merge quarters (F-->T):
    merge(f, na1, na2, t);
    for (ulong j=0; j<na; ++j)  f[j] = t[j];  // cheat for printing
    cout << "T: ";  PRINT(f, 0, na);
    for (ulong j=0; j<na; ++j)  f[j] = '@';  // undo cheat

    cout << "F: ";  PRINT(f+na, 0, nb1);
    cout << "F: ";  PRINT(f+na+nb1, 0, nb2);
    merge(f+na, nb1, nb2, t+na);

    for (ulong j=na; j<n; ++j)  f[j] = t[j];  // cheat for printing
    cout << "T: ";  PRINT(f+na, 0, nb);
    for (ulong j=na; j<n; ++j)  f[j] = '@';  // undo cheat

    // merge halves (T-->F):
    merge(t, na, nb, f);
    cout << "F: ";  PRINT(f, 0, n);
    cout << endl;

    jjassert( is_sorted(f, n) );
}
// -------------------------


template <typename Type>
void demo_merge_sort4(Type *f, ulong n, Type *tmp=0)
{
    Type *t = tmp;
    if ( tmp==0 )  t = new Type[n];
    demo_merge_sort_rec4(f, n, t);
    if ( tmp==0 )  delete [] t;
}
// -------------------------



int
main(int argc, char **argv)
{
    char *str;
    NXARGSTR(str, "String to sort", "nowsortmeADBACD54321");
//    NXARGSTR(str, "String to sort", "nowsortme");
//    NXARGSTR(str, "String to sort", "hgfedcba");
//    NXARGSTR(str, "String to sort", "TheBinarySplittingSchemeForProductsOrSo");
//    NXARGSTR(str, "String to sort", "2705520349807111576968325245272272053880818086");

    ulong n = strlen(str);
    char *f = new char[n+1];
    ff = f;  nn = n;
    acopy(str, f, n);

    cout << "F: ";  PRINT(f, 0, n);  cout << endl;
    demo_merge_sort4(f, n);
    jjassert( is_sorted(f, n) );


    // test routine in merge-sort.h:
    acopy(str, f, n);
    merge_sort4(f, n);
    jjassert( is_sorted(f, n) );


    delete [] f;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/sort"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/sort/merge-sort4-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/merge-sort4-demo.cc DEMOFLAGS=-DTIMING"
/// End:
