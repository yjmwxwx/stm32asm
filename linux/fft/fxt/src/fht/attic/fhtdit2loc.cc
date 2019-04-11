
#include "complextype.h"
#include "sincos.h"
#include "revbinpermute.h"
#include "sumdiff.h"

#include <cmath> // M_PI


void
dit2_fht_localized(double *f, ulong ldn)
// decimation in time radix 2 fht
// depth-first version
// compared to usual fht this one
// - does more trig computations
// - is (far) better memory local
{
    const ulong n = 1<<ldn;

    revbin_permute(f, n);

    for (ulong ldm=1; ldm<=ldn; ++ldm)
    {
        const ulong m = (1<<ldm);
        const ulong mh = (m>>1);
        const ulong m4 = (mh>>1);
        const double phi0 = M_PI/mh;
        for (ulong r=0; r<n; r+=m)
        {
            double *p = f + r + mh;
            // hartley_shift_05(p, mh):
            for (ulong j=1, k=mh-1; j<m4; ++j,--k)
            {
                double s, c;
                SinCos(phi0*j, &s, &c);

                double pj = p[j];
                double pk = p[k];

                p[j] = pj * c + pk * s;
                p[k] = pj * s - pk * c;
            }

            for (ulong j=0; j<mh; ++j)
            {
                ulong t1 = r + j;
                ulong t2 = t1 + mh;

                double u = f[t1];
                double v = f[t2];

                f[t1] = u + v;
                f[t2] = u - v;
            }
        }
    }
}
// -------------------------
