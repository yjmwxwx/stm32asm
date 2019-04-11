// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "dctdst/dctdst.h"

#include "fxttypes.h"  // ulong

#include <cmath>  // cos(), M_PI


//void
//dct(double *f, ulong ldn, double *tmp/*=0*/)
//// basis: cos((k+0.5)*(i+0.5)*M_PI/n)
//// ldn := base-2 logarithm of the array length
//// tmp := (optional) pointer to scratch space
//{
//
//}
//// -------------------------

void
dct_basis(double *f, ulong n, ulong k)
{
//    double vv = 1.0;
    const double ph = M_PI * ((double)k+0.5) / (double)n;
    for (ulong i=0; i<n; ++i)
    {
        // f[i] = vv * cos( M_PI * (k+0.5) * (i+0.5) / n );
        f[i] = cos( ((double)i+0.5) * ph );
    }
}
// -------------------------
