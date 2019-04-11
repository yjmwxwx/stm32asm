// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>  // pow()

#include "fxtalloca.h"
#include "fxttypes.h"
#include "complextype.h"

#include "aux1/copy.h"


void
slow_zt(Complex *f, ulong n, Complex z)
// (slow) z-transform.
{
    ALLOCA(Complex, res, n);
    for (ulong w=0; w<n; ++w)
    {
        Complex sum = 0.0;
        Complex t = 1.0;  // == z**0
        Complex m = pow(z, (double)w);
        for (ulong k=0; k<n; ++k)
        {
            sum += f[k] * t;  // t == pow(z, k*w);
            t *= m;
        }
        res[w] = sum;
    }
    acopy(res, f, n);
}
// -------------------------


void
slow_zt(double *f, ulong n, double z)
// (slow) z-transform.
{
    ALLOCA(double, res, n);
    for (ulong w=0; w<n; ++w)
    {
        double sum = 0.0;
        double t = 1.0;  // == z**0
        double m = pow(z, (double)w);
        for (ulong k=0; k<n; ++k)
        {
            sum += f[k] * t;  // t == pow(z, k*w);
            t *= m;
        }
        res[w] = sum;
    }
    acopy(res, f, n);
}
// -------------------------
