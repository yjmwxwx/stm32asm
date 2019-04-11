
// demo-include "mod/modarith.h"

#include "bits/print-bin.h"  // print_bin()
#include "bits/bit2pow.h"  // ld()

#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include <cmath>  // pow()


//% Right-to-left powering algorithm.

double
power_r2l(double a, ulong e)
{
    if ( 0==e )  return 1;

    double s = a;
    cout << ( e & 1 ?  '1' : '0') << "  ";
    cout << setw(25) << s;
    cout << setw(25) << a;
    cout << endl;

    while ( 0==(e&1) )
    {
        s *= s;
        e /= 2;

        cout << ( e & 1 ?  '1' : '0') << "  ";
        cout << setw(25) << s;
        cout << setw(25) << a;
        cout << endl;
    }

    a = s;
    while ( 0!=(e/=2) )
    {
        s *= s;
        if ( e & 1 )  a *= s;

        cout << ( e & 1 ?  '1' : '0') << "  ";
        cout << setw(25) << s;
        cout << setw(25) << a;
        cout << endl;
    }
    return  a;
}
// -------------------------



int
main(int argc, char **argv)
{
    double a = 2.0;
    NXARGFL(a, "number to exponentiate");
    ulong e = 38;
    NXARG(e, "exponent");
    print_bin(" e = ", e, ld(e)+1 );
    cout << endl;

    cout.precision(21);

    double p = power_r2l(a, e);
    cout << "p=a**e = " << p << endl;

    double pm = pow(a, (double)e);
//    cout << "       = " << pm << endl;
    jjassert( fabs(p-pm) < 1e-6 );

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/arith"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/arith/power-r2l-demo.cc"
/// make-target2: "1demo DSRC=demo/arith/power-r2l-demo.cc DEMOFLAGS=-DTIMING"
/// End:

