
// demo-is-self-contained

#include "aux0/print-fixed.h"  // print_fixed()
#include "fxtio.h"
#include "nextarg.h"

#include "fxttypes.h"  // ulong

#include <cmath>

//% Shift-add algorithm for computing b^x

// Output dependent on FPU

double *shiftadd_ltab;
ulong ltab_n;

void
make_shiftadd_ltab(double b)
{
    double l1b = 1.0 / log(b);
    double s = 1.0;
//    cout << "ltab_n= " << ltab_n << endl;
    for (ulong k=0; k<ltab_n; ++k)
    {
        shiftadd_ltab[k] = log(1.0+s) * l1b;  // == log_b(1+1/2^k)
        s *= 0.5;
//        cout << shiftadd_ltab[k] << endl;
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
print_utea(long n, double x, double y, double z, double a)
{
    cout << setw(3) << n;
    print_fixed(COLSEP, x, nd, 0);
    print_fixed(COLSEP, y, nd, 0);
    print_fixed(COLSEP, z, nd, 1);
    print_fixed(COLSEP, a, nd, 1);
    cout << ENDL << endl;
}
// -------------------------


double
shiftadd_exp(double x, ulong n)
{
    if ( n>=ltab_n )  n = ltab_n;
    double t = 0.0;
    double e = 1.0;
    double v = 1.0;
    print_utea(-1, 0.0, t, e, 0.0);  cout << endl;
    for (ulong k=1; k<n; ++k)
    {
        v *= 0.5;  // v == (1>>k)

        double u;
        bool d;
        while ( 1 )
        {
            u = t + shiftadd_ltab[k];
            d = ( u<=x );
            print_utea((long)k, u, t, e, shiftadd_ltab[k]);
            if ( d==false )  break;

            t = u;
            e += e * v;  // e+=(e>>k);
        }
    }
    return  e;
}
// -------------------------

int
main(int argc, char **argv)
{
    double x = 0.5;
    NXARGFL(x, "Argument for shift-add b^x computation");

    double b = 2;
    NXARGFL(b, "Base of the logarithm");

    ulong n = 16;
    NXARG(n, "Number of iterations");

    ltab_n = 64;
    shiftadd_ltab = new double[ltab_n];
    make_shiftadd_ltab(b);


    cout << endl;
    double l = shiftadd_exp(x, n);


    cout << endl;
    double zl = exp(x*log(b));
    print_utea(99, x, x, zl, 0.0);

    cout << endl;
    cout << setprecision(19);
    cout << "dl = " << setw(12) << l-zl << endl;
    cout << "2**(-n) = " << pow(2.0, -(double)n) << endl;
    cout << endl;

    delete [] shiftadd_ltab;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/arith"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/arith/shiftadd-exp-demo.cc"
/// make-target2: "1demo DSRC=demo/arith/shiftadd-exp-demo.cc DEMOFLAGS=-DTIMING"
/// End:

