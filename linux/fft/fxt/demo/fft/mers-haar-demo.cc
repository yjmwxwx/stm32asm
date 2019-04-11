
#include "haar/mers-haar.h"
#include "mod/mersenne.h"

#include "fxttypes.h"
//#include "aux1/aux1double.h"  // norm_l2()
#include <cmath>  // fabs()

#include "fxtio.h"

#include "nextarg.h"


//% Mersenne-Haar transform

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "length=M(n)=2**n-1");
    ulong f0;
    f0 = mersenne(n);
    cout << " M(n)=" << f0 << endl;

    double *a = new double[f0];

    for (ulong k=0; k<f0; ++k)
    {
        // delta function:
        for (ulong j=0; j<f0; ++j)  a[j] = 0;
        a[k] = 1;

        mersenne_haar_nn(a, f0);

        cout << setw(2) << k << ":";

        for (ulong j=0; j<f0; ++j)  cout << " " << setw(2) << a[j];
//        for (ulong j=0; j<f0; ++j)
//        {
////            cout << " ";
//            double aj = a[j];
//            if ( fabs(aj) < 1e-4 )  cout << " ";
//            else                    cout << (aj<0?'-':'+');
//        }
//        cout << "   norm=" << norm_l2(a,f0);
//        cout << endl;
        cout << endl;
    }

    cout << endl;

    delete [] a;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/fft"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/fft/mers-haar-demo.cc"
/// make-target2: "1demo DSRC=demo/fft/mers-haar-demo.cc DEMOFLAGS=-DTIMING"
/// End:
