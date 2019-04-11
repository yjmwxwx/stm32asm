
// demo-include "mod/modarith.h"

#include "bits/bithigh.h"  // highest_one()
#include "bits/bit2pow.h"  // ld()
#include "bits/print-bin.h"  // print_bin()

#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include <cmath>  // pow()


//% Left-to-right powering algorithm.


double
power_l2r(double a, ulong e)
{
    if ( 0==e )  return 1;
    double s = a;
    ulong b = highest_one(e);

    cout << ( e & b ?  '1' : '0') << "  ";
    cout << setw(25) << s;
    cout << endl;

    while ( b>1 )
    {
        b >>= 1;
        s *= s;
        cout << ( e & b ?  '1' : '0') << "  ";
        cout << setw(25) << s;

        if ( e & b )  s *= a;

        cout << setw(25) << s;
        cout << endl;
    }
    return s;
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

    double p = power_l2r(a, e);
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
/// make-target: "1demo DSRC=demo/arith/power-l2r-demo.cc"
/// make-target2: "1demo DSRC=demo/arith/power-l2r-demo.cc DEMOFLAGS=-DTIMING"
/// End:

