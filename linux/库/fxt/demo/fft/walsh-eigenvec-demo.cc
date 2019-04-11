
#include "walsh/walsheigen.h"
// demo-include "walsh/walsheigen.cc"
#include "walsh/walsh-basis.h"
#include "walsh/walshwak.h"

#include "aux1/copy.h"

#include "walsh-all.h"  // for other transforms
#include "fxtio.h"
#include "fxttypes.h"  // ulong
#include "nextarg.h"

#include <cmath>  // fabs()

//% Eigenvectors of the Walsh transform (Walsh-Kronecker basis).

void
print_vec(double *v, ulong n)
{
    cout << "[ ";
    for (ulong j=0; j<n; ++j)
    {
        double vj = v[j];
        char s = (vj>=0 ? '+' : '-');
        vj = fabs(vj);
        cout << s << vj << " ";
    }
    cout << "]" << endl;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong ldn = 4;
    NXARG(ldn, "Length 2**ldn Walsh transform.");

    ulong tq = 0;
    NXARG(tq, "Whether to print transformed vectors.");

    ulong n = 1UL << ldn;
    double *v = new double[n];
    for (ulong k=0; k<n; ++k)
    {
        cout << setw(2) << k << ":  ";
        walsh_wak_eigen(v, ldn, k);
//        walsh_wal_eigen(v, ldn, k);
//        walsh_pal_eigen(v, ldn, k);
        print_vec(v, n);

        if ( tq )
        {
            walsh_wak(v, ldn);
//            walsh_wal(v, ldn);
//            walsh_pal(v, ldn);
            for (ulong j=0; j<n; ++j)  v[j] *= 1.0/sqrt((double)n);  // normalize
            cout << "  :  ";
            print_vec(v, n);
        }
        cout << endl;
    }

    delete [] v;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/fft"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/fft/walsh-eigenvec-demo.cc"
/// make-target2: "1demo DSRC=demo/fft/walsh-eigenvec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

