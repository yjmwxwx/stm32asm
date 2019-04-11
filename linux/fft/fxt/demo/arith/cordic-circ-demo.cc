
// demo-is-self-contained

#include "aux0/print-fixed.h"  // print_fixed()
#include "nextarg.h"

#include "fxttypes.h"  // ulong
#include <cmath>

//% CORDIC computation of sine and cosine.


double *cordic_ctab;
//const double cordic_K = 1.646760258121065648366051222282298435652376725701027409;
// == prod(j=0,200,sqrt(1+2.0^(-2*j)))
const double cordic_1K = 0.6072529350088812561694467525049282631123908521500897724;


void
make_cordic_ctab(ulong na)
{
    double s = 1.0;
    for (ulong k=0; k<na; ++k)
    {
        cordic_ctab[k] = atan(s);
        s *= 0.5;
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
cordic_circ(double theta, double &s, double &c, ulong n)
{
    double x = cordic_1K;
    double y = 0;
    double z = theta;
    double v = 1.0;
    print_xyza(-1, x, y, z, 0);

    for (ulong k=0; k<n; ++k)
    {
        double d = ( z>=0 ? +1 : -1 );
        double tx = x - d * v * y;
        double ty = y + d * v * x;
        double tz = z - d * cordic_ctab[k];
        x = tx;  y = ty;  z = tz;
        v *= 0.5;

        print_xyza((long)k, x, y, z, -d*cordic_ctab[k]);
    }
    c = x;
    s = y;
}
// -------------------------


int
main(int argc, char **argv)
{
    double t = M_PI/3.0;
    NXARGFL(t, "Argument for CORDIC sin/cos computation");

    ulong n = 16;
    NXARG(n, "Number of iterations");

    ulong na = 64;
    cordic_ctab = new double[na];
    make_cordic_ctab(na);

    double s, c;

    cordic_circ(t, s, c, n);

    cout << endl;
    double zs = sin(t), zc = cos(t);
    print_xyza(9999, zc, zs, 0.0, 0.0);

    cout << endl;
    cout << setprecision(19);
    cout << "dc = " << setw(12) << c-zc << endl;
    cout << "ds = " << setw(12) << s-zs << endl;
    cout << "2**(-n) = " << pow(2.0, -(double)n) << endl;
    cout << endl;

    delete [] cordic_ctab;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/arith"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/arith/cordic-circ-demo.cc"
/// make-target2: "1demo DSRC=demo/arith/cordic-circ-demo.cc DEMOFLAGS=-DTIMING"
/// End:

