
#include "fxttypes.h"

void
dit2_walsh_wak_slow(double *f, ulong ldn)  // nonlocal ==> SLOW!
//
// transform wrt. to walsh-kronecker basis (wak-functions)
// same result as dit2_walsh_wak() but the loops
//  with loop variables j and r are swapped (as in ffts)
// ==> nonlocal ==> SLOW!
//
{
    ulong n = (1<<(ulong)ldn);
    for (ulong ldm=1; ldm<=ldn; ++ldm)
    {
        const ulong m = (1<<ldm);
        const ulong mh = (m>>1);
        for (ulong j=0; j<mh; ++j)
        {
            for (ulong r=0; r<n; r+=m)
            {
                const ulong t1 = r+j;
                const ulong t2 = t1+mh;
                double v = f[t2];
                double u = f[t1];
                f[t1] = u+v;
                f[t2] = u-v;
            }
        }
    }
}
// -------------------------


void
dif2_walsh_wak_slow(double *f, ulong ldn)
//
// transform wrt. to walsh-kronecker basis (wak-functions)
// same result as dif2_walsh_wak() but the loops
//  with loop variables j and r are swapped (as in ffts)
// ==> nonlocal ==> SLOW!
//
{
    const ulong n = (1<<ldn);
    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong m = (1<<ldm);
        const ulong mh = (m>>1);
        for (ulong j=0; j<mh; ++j)
        {
            for (ulong r=0; r<n; r+=m)
            {
                const ulong t1 = r+j;
                const ulong t2 = t1+mh;
                double u = f[t1];
                double v = f[t2];
                f[t1] = u+v;
                f[t2] = u-v;
            }
        }
    }
}
// -------------------------
