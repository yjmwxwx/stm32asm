
#include "sort/sortfunc.h"

#include "sort/bsearchfunc.h"
#include "sort/quantize.h"  // quantize()

#include "fxttypes.h"
#include "complextype.h"
#include "aux0/randf.h"  // rnd01()

#include "jjassert.h"

#include "fxtio.h"

#include "nextarg.h"  // NXARG()

//% Demo of sort for complex numbers.
//% Major order wrt. real part, minor order wrt. imag part.


static inline int
cmp_complex(const Complex &f, const Complex &g)
// Comparison function used for sorting complex numbers.
// Major order by real part, minor order by imaginary part.
{
    const double fr = f.real(),  gr = g.real();
    if ( fr!=gr )  return  (fr>gr ? +1 : -1);

    const double fi = f.imag(),  gi = g.imag();
    if ( fi!=gi )  return  (fi>gi ? +1 : -1);

    return  0;
}
// -------------------------

void
complex_sort(Complex *f, ulong n)
// major order wrt. real part
// minor order wrt. imag part
{
    quick_sort(f, n, cmp_complex);
}
// -------------------------

void
print(const char *bla, const Complex *f, ulong n)
{
    cout << endl;
    if ( bla )  cout << bla << endl;

    for (ulong k=0; k<n; ++k)
    {
        Complex r = f[k];

        cout.flags(ios::right);
        cout << setw(4) << k << ":  ";
//        cout.flags(ios::left);

        cout.precision(5);
        cout << "(";
        cout.width(5);
        cout << r.real();
        cout << ", ";
        cout.width(5);
        cout << r.imag();
        cout << ")";
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

    Complex *f = new Complex[n];

    rnd01((double *)f, 2*n);
    quantize((double *)f, 2*n, 1.0/10);  // we want repeated real parts

    print("random values:", f, n);

    Complex v = f[n/2];

    complex_sort(f, n);
    print("sorted values:", f, n);

    jjassert( is_sorted(f, n, cmp_complex) );

    cout << "searching for v=" << v << endl;
    ulong i = bsearch(f, n, v, cmp_complex);
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
/// make-target: "1demo DSRC=demo/sort/sort-complex-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/sort-complex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

