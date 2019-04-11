// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>

#include "aux0/cmult.h"

#include "aux0/sincos.h"

#include "aux1/copy.h"

#include "fxtalloca.h"
#include "fxttypes.h"
#include "complextype.h"


void
slow_fract_ft(double *fr, double *fi, ulong n, double v)
// (slow) fractional Fourier transform.
// (for v=+-1 this is the usual Fourier transform)
{
    ALLOCA(double, hr, n);
    ALLOCA(double, hi, n);
    const double ph0 = v * 2.0*M_PI/(double)n;
    for (ulong w=0; w<n; ++w)
    {
        double sr=0.0, si=0.0;
        for (ulong k=0; k<n; ++k)
        {
            double c, s;
            SinCos(ph0*(double)k*(double)w, &s, &c);

            double r, i;
            cmult(c, s, fr[k], fi[k], r, i);

            sr += r;
            si += i;
        }
        hr[w] = sr;
        hi[w] = si;
    }
    acopy(hr, fr, n);
    acopy(hi, fi, n);
}
// -------------------------


void
slow_fract_ft(Complex *f, ulong n, double v)
// (slow) fractional Fourier transform.
// (for v=+-1 this is the usual Fourier transform)
{
    ALLOCA(Complex, h, n);
    const double ph0 = v * 2.0*M_PI/(double)n;
    for (ulong w=0; w<n; ++w)
    {
        Complex sum = 0.0;
        for (ulong k=0; k<n; ++k)
        {
            double c, s;
            SinCos(ph0*(double)k*(double)w, &s, &c);
            sum += f[k] * Complex(c, s);
        }
        h[w] = sum;
    }
    acopy(h, f, n);
}
// -------------------------
