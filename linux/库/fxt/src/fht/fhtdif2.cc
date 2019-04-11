// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux0/sincos.h"
#include "perm/revbinpermute.h"
#include "aux0/sumdiff.h"

#include <cmath>  // M_PI


void
fht_depth_first_dif2(double *f, ulong ldn)
// Radix-2 decimation in frequency (DIF) FHT
// Depth-first version.
// Compared to usual FHT this one
// - does more trig computations
// - is (far) better memory local
{
    const ulong n = (1UL<<ldn);
    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        const ulong m4 = (mh>>1);
        const double phi0 = M_PI / (double)mh;
        for (ulong r=0; r<n; r+=m)
        {
            for (ulong j=0; j<mh; ++j)
            {
                ulong t1 = r+j;
                ulong t2 = t1+mh;

                double u = f[t1];
                double v = f[t2];

                f[t1] = u + v;
                f[t2] = u - v;
            }

            double *p = f + r + mh;
            // hartley_shift_05(p, mh):
            double ph = 0.0;
            for (ulong j=1, k=mh-1;  j<m4;  ++j, --k)
            {
                double s, c;
//                SinCos(phi0*j, &s, &c);
                ph += phi0;
                SinCos(ph, &s, &c);

                double pj = p[j];
                double pk = p[k];
                p[j] = pj * c + pk * s;
                p[k] = pj * s - pk * c;
            }
        }
    }

    revbin_permute(f, n);
}
// -------------------------

void
fht_dif2(double *f, ulong ldn)
// Radix-2 decimation in frequency (DIF) FHT
{
    const ulong n = (1UL<<ldn);
    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        const ulong m4 = (mh>>1);
        const double phi0 = M_PI / (double)mh;

        for (ulong r=0; r<n; r+=m)
        {
            {  // j == 0:
                ulong t1 = r;
                ulong t2 = t1 + mh;
                sumdiff(f[t1], f[t2]);
            }

            if ( m4 )
            {
                ulong t1 = r + m4;
                ulong t2 = t1 + mh;
                sumdiff(f[t1], f[t2]);
            }
        }

        double ph = 0.0;
        for (ulong j=1, k=mh-1;  j<k;  ++j, --k)
        {
            double s, c;
//            SinCos(phi0*j, &s, &c);
            ph += phi0;
            SinCos(ph, &s, &c);

            for (ulong r=0; r<n; r+=m)
            {
                ulong tj = r + mh + j;
                ulong tk = r + mh + k;

                ulong t1 = r + j;
                ulong t2 = tj;  // == t1 + mh;
                sumdiff(f[t1], f[t2]);

                t1 = r + k;
                t2 = tk;  // == t1 + mh;
                sumdiff(f[t1], f[t2]);

                double fj = f[tj];
                double fk = f[tk];
                f[tj] = fj * c + fk * s;
                f[tk] = fj * s - fk * c;
            }
        }
    }

    revbin_permute(f, n);
}
// -------------------------
