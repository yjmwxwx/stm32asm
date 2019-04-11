// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "aux0/sincos.h"

#include <cmath>  // M_PI, M_SQRT1_2


void
cos_rot(const double *x, double *y, ulong n)
// Auxiliary routine for dcth() and dct4()
// x and y may be identical
// Self-inverse.
{
    ulong nh = (n>>1);
    y[0]  = x[0];
    y[nh] = x[nh];
    double phi0 = M_PI/(2.0*(double)n);
    double phi = 0.0;
    for (ulong k=1, j=n-1;  k<j;  ++k, --j)
    {
        phi += phi0;
        double c, s;
        SinCos(phi, &s, &c);
        // cos(x) +- sin(x) == sqrt(2) * cos( Pi/4 -+ x )
        double p = (c+s) * M_SQRT1_2;
        double m = (c-s) * M_SQRT1_2;
        double xk = x[k],  xj = x[j];
        y[k] = m * xk + p * xj;
        y[j] = p * xk - m * xj;
    }
}
// -------------------------
