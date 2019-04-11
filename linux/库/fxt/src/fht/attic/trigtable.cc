
#include "aux0/sincos.h"  // for SinCos()
#include "fxttypes.h"

#include <cmath>    // for M_PI


static double *ct = 0;
static double *st = 0;


void
make_sincos_table(ulong n, ulong m, double **s, double **c)
//
// make m-element arrays s[m],c[m]
// with s[k]=sin(2*Pi*k/n)
// with c[k]=cos(2*Pi*k/n)
//
// reallocs at each call,
// call with n=0 to delete the table
//
{
    if ( ct )  delete [] ct;
    if ( st )  delete [] st;

    if ( 0==n )  return;

    ct = new double[m];
    st = new double[m];

    const double p0 = 2.0*M_PI/n;
    for (ulong k=0; k<m; ++k)
    {
        double phi = p0*k;
        SinCos(phi, st+k, ct+k);
    }

    *s = st;
    *c = ct;
}
// -------------------------

