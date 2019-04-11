
// demo-is-self-contained

#include "aux0/print-fixed.h"  // print_fixed()
#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "fxtio.h"

#include <cmath>

//% Computation of the logarithm using a method similar to the shift-and-add algorithm.

// Output dependent on FPU

double *briggs_ltab;
ulong  ltab_len;

void
make_briggs_ltab(ulong na, double b)
{
    double l1b = 1.0 / log(b);
    double s = 2.0;  // == 2^k
    briggs_ltab[0] = -1.0;  // unused
    for (ulong k=1; k<na; ++k)
    {
        briggs_ltab[k] = log(s/(s-1.0)) * l1b;
        // == log_b(1+1/(2^k-1)) = log_b(2^k/(2^k-1))
        s *= 2.0;
    }
}
// -------------------------

//#define TEX
#ifdef TEX
#define COLSEP " &   "
#define ENDL " \\\\"
#else  // TEX
#define COLSEP "  "
#define ENDL ""
#endif  // TEX
const long nd = 9;  // Number of Digits displayed

void
print_xyza(long n, double x, double y, double z, double a)
{
    cout << setw(2) << n;
    print_fixed(COLSEP, x, nd, 0);
    print_fixed(COLSEP, y, nd, 0);
    print_fixed(COLSEP, z, nd, 1);
    print_fixed(COLSEP, a, nd, 1);
    cout << ENDL << endl;
}
// -------------------------

double bb;

double
briggs_log(double x, double eps)
{
    double y = 0;
    double z = x * 0.5;
    print_xyza(-1, x, y, z, 0.0);

    ulong k = 1;
    double v = 0.5;  // v == 2^(-k)
    while ( fabs(x-1.0)>=eps )
    {
        while ( fabs(x-z)<1.0 )
        {
            z *= 0.5;
            ++k;  v *= 0.5;
            if ( k >= ltab_len )  goto done;  // no more table entries
            print_xyza((long)k, x, y, z, briggs_ltab[k]);
        }

        x -= z;
        y += briggs_ltab[k];
        z = x * v;  // z=(x>>k)
        // invariant:  y_k + log_b(x_k) == log_b(x_0)
//        print_fixed("  iiii=", y+log(x)/log(bb), nd, 0);  cout << endl;

        print_xyza((long)k, x, y, z, briggs_ltab[k]);
    }

 done:
    return  y;
}
// -------------------------

int
main(int argc, char **argv)
{
    double x = sqrt(2.0);
//    double x = 1.33333333333;
//    double x = 1.9;
    NXARGFL(x, "Argument for log(x) computation x>=1");

    double b = 2.0;
    NXARGFL(b, "Base of logarithm: b>0 and b!=1");
    bb = b;

    double eps = 1e-5;
    NXARGFL(eps, "Precision of the result");
    cout << endl;

    ltab_len = 64;
    briggs_ltab = new double[ltab_len];
    make_briggs_ltab(ltab_len, b);

    double l = briggs_log(x, eps);

//    cout << "log(x)=" << log(x) << endl;
//    cout << "log(b)=" << log(b) << endl;
    cout << endl;
    double zl = log(x)/log(b);
    print_xyza(99, 1.0, zl, 0.0, 0.0);

    cout << endl;
    cout << setprecision(19);
    cout << "dl = " << setw(12) << l-zl << endl;
//    cout << "2**(-n) = " << pow(2.0, -(double)n) << endl;
    cout << endl;

    delete [] briggs_ltab;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/arith"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/arith/briggs-log-demo.cc"
/// make-target2: "1demo DSRC=demo/arith/briggs-log-demo.cc DEMOFLAGS=-DTIMING"
/// End:

