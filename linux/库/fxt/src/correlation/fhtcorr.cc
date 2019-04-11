// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "correlation/correlation.h"
#include "convolution/realconvolution.h"
#include "fht/fht-default.h"
#include "aux0/cmult.h"
#include "aux0/sumdiff.h"
#include "restrict.h"

#include "aux1/arith1.h"
#include "perm/reverse.h"

#include "fxttypes.h"  // ulong


void
fht_correlation(double * restrict f, double * restrict g, ulong ldn)
// compute the (real, cyclic) correlation of f[], g[]
// result is in g[]
// ldn := base-2 logarithm of the array length
// version for zero padded data:
//   f[k], g[k] == 0 for k=n/2 ... n-1
// n = 2**ldn  must be >=2
{
    fht(f, ldn);
    fht(g, ldn);

    reverse_0(f, 1UL<<ldn);
    fht_convolution_core(f, g, ldn);

    fht(g, ldn);
}
// -------------------------


void
fht_auto_correlation(double *f, ulong ldn)
// compute the (real, cyclic) self-correlation of f[]
// ldn := base-2 logarithm of the array length
// version for zero padded data:
//   f[k] == 0 for k=n/2 ... n-1
// n = 2**ldn  must be >=2
{
    fht(f, ldn);
    fht_auto_correlation_core(f, ldn);
    fht(f, ldn);
}
// -------------------------

void
fht_correlation0(double * restrict f, double * restrict g, ulong ldn)
// compute the (real, linear) correlation of f[], g[]
// result is in g[]
// ldn := base-2 logarithm of the array length
// version for zero padded data:
//   f[k], g[k] == 0 for k=n/2 ... n-1
// n = 2**ldn  must be >=2
{
    fht0(f, ldn);
    fht0(g, ldn);

    reverse_0(f, 1UL<<ldn);
    fht_convolution_core(f, g, ldn);

    fht(g, ldn);
}
// -------------------------


void
fht_auto_correlation0(double *f, ulong ldn)
// compute the (real, linear) self-correlation of f[]
// ldn := base-2 logarithm of the array length
// version for zero padded data:
//   f[k] == 0 for k=n/2 ... n-1
// n = 2**ldn  must be >=2
{
    fht0(f, ldn);
    fht_auto_correlation_core(f, ldn);
    fht(f, ldn);
}
// -------------------------



void
fht_auto_correlation_core(double *f, ulong ldn,
                          double v/*=0.0*/)  // jjkeep
// auxiliary routine for the computation of self-correlations
//   via Fast Hartley Transforms
// ldn := base-2 logarithm of the array length
// v!=0.0 chooses alternative normalization
{
    const ulong  n  = (1UL<<ldn);
    if ( v==0.0 )  v = 1.0/(double)n;

    f[0]  *= (v * f[0]);

    const ulong  nh = (n>>1);
    if ( nh>0 )
    {
        f[nh] *= (v * f[nh]);
        v *= 0.25;
        for (ulong i=1, j=n-1;  i<j;  ++i, --j)
        {
            double t1, t2;
            sumdiff(f[i], f[j], t1, t2);
            t1 = t1 * t1 + t2 * t2;
            f[i] = f[j] = t1 * v;
        }
    }
}
// -------------------------
