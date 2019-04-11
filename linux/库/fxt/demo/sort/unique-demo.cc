
#include "sort/unique.h"

#include "sort/sort.h"
#include "sort/quantize.h"  // quantize()
#include "aux0/randf.h"  // rnd01()

#include "fxtalloca.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "fxtio.h"
#include "nextarg.h"  // NXARG()


//% The functions quantize() and unique().

void
print(const char *bla, const double *f, ulong n)
{
    cout << endl;
    if ( bla )  cout << bla << endl;

    for (ulong k=0; k<n; ++k)
    {
        double r = f[k];

        cout.flags(ios::right);
        cout.fill(' ');
        cout << setw(4) << k << ":  ";

        cout.precision(10);
        cout.flags(ios::left);
        cout.fill('0');
        cout << setw(12) << r;
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

    double q = 1.0/100;
    NXARGFL(q, "Parameter for quantization");

    ALLOCA(double, f, n);
    for (  ; n>2; n/=2)
    {
        cout << "---------------------------" << endl;

        rnd01(f, n);
        print("Random values:", f, n);

        cout << "Quantization with q=" << q << endl;
        quantize(f, n, q);
//        print("quantized values:", f, n);

        quick_sort(f, n);
        print("Quantized & sorted :", f, n);


        ulong u = test_unique(f, n);
        if ( 0==u )  cout << "all UNIQUE values" << endl;
        else
        {
            cout << "First REPEATED value at index " << u
                 << "  (and " << u-1 << ")" << endl;

            u = count_unique(f, n);
            cout << "There are " << u << " unique values (of " << n << ")." << endl;
            cout << "  i.e. " << (n-u) << " repeated value(s). " << endl;

            u = unique(f, n);
            print("Unique'd array:", f, u);
        }


        cout << endl;
        jjassert( is_unique(f, u) );
    }


    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/sort"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/sort/unique-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/unique-demo.cc DEMOFLAGS=-DTIMING"
/// End:

