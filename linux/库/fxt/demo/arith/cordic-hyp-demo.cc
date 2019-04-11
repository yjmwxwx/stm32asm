
// demo-is-self-contained

#include "aux0/print-fixed.h"  // print_fixed()
#include "nextarg.h"

#include "fxttypes.h"  // ulong
#include <cmath>

//% CORDIC computation of hyperbolic sine and cosine.

double *cordic_htab;
//const double cordic_Kp = 0.8281593609602156270761983277591751468694538376908425291;
const double cordic_1Kp = 1.207497067763072128877721011310915836812783221769813422;


void
make_cordic_htab(ulong na)
{
    double s = 1.0;
    cordic_htab[0] = 0;
    for (ulong k=1; k<na; ++k)
    {
        s *= 0.5;
        cordic_htab[k] = atanh(s);  // cordic_htab[0] unused
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


void
cordic_hyp(double theta, double &s, double &c, ulong n)
{
    double x = cordic_1Kp;
    double y = 0;
    double z = theta;
    double v = 1.0;
    print_xyza(-1, x, y, z, 0.0);
    ulong i = 4;
    for (ulong k=1; k<n; ++k)
    {
        v *= 0.5;
    again:
        double d = ( z>=0 ? +1 : -1 );
        double tx = x + d * v * y;
        double ty = y + d * v * x;
        double tz = z - d * cordic_htab[k];
        x = tx;  y = ty;  z = tz;
        print_xyza((long)k, x, y, z, -d*cordic_htab[k]);
        if ( k==i )  { i=3*i+1; goto again; }
    }
    c = x;
    s = y;
}
// -------------------------

int
main(int argc, char **argv)
{
    double t = 1.0;
    NXARGFL(t, "Argument for CORDIC sinh/cosh computation");

    ulong n = 16;
    NXARG(n, "Number of iterations");

    ulong na = 64;
//    cordic_ctab = new double[na];
//    make_cordic_ctab(na);
    cordic_htab = new double[na];
    make_cordic_htab(na);

    double s, c;

    cordic_hyp(t, s, c, n);


    double zs = sinh(t), zc = cosh(t);
    print_xyza(99, zc, zs, 0.0, 0.0);

    cout << endl;
    cout << setprecision(19);
    cout << "dc = " << setw(12) << c-zc << endl;
    cout << "ds = " << setw(12) << s-zs << endl;
    cout << "2**(-n) = " << pow(2.0, -(double)n) << endl;
    cout << endl;

    delete [] cordic_htab;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/arith"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/arith/cordic-hyp-demo.cc"
/// make-target2: "1demo DSRC=demo/arith/cordic-hyp-demo.cc DEMOFLAGS=-DTIMING"
/// End:

