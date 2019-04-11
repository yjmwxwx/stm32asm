
#include "walsh/fib-walsh.h"
#include "aux0/fibonacci.h"

#include "fxttypes.h"
//#include "aux1/aux1double.h"  // norm_l2()
#include <cmath>  // fabs()

#include "fxtio.h"

#include "nextarg.h"


//% Fibonacci-Walsh transform

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "length=Fib(n)");
    ulong f0, f1;
    fibonacci_pair(n, f0, f1);
    cout << " Fib(n)=" << f0 << endl;
//    cout << " Fib(n-1)=" << f1 << endl;

    double *a = new double[f0];

    for (ulong k=0; k<f0; ++k)
    {
        // delta function:
        for (ulong j=0; j<f0; ++j)  a[j] = 0;
        a[k] = 1;

        fibonacci_walsh_nn(a, f0, f1);
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
/// make-target: "1demo DSRC=demo/fft/fib-walsh-demo.cc"
/// make-target2: "1demo DSRC=demo/fft/fib-walsh-demo.cc DEMOFLAGS=-DTIMING"
/// End:
