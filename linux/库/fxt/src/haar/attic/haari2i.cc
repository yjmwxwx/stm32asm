// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include <cmath>

#include "aux1/copy.h"


// to do useful things:
// 1) replace all 'double' by 'int'
// 2) replace '*0.5' by '/2
// 3) erase calls to 'floor()'

void
haar_i2i(double *f, ulong ldn, double *ws/*=0*/)
//
// transform wrt. to haar base
// integer input gives integer output
//
{
    ulong n = (1UL<<ldn);

    double *g = ws;
    if ( !ws )  g = new double[n];

    for (ulong m=n; m>1; m>>=1)
    {
        ulong mh = (m>>1);
        for (ulong j=0,k=0; j<m; j+=2,k++)
        {
            double x = f[j];
            double y = f[j+1];

            double d = x - y;
            double s = y + floor(0.5*d); // == floor(0.5*(x+y));

            g[k]    =  s;
            g[mh+k] =  d;
        }
        acopy(g, f, m);
    }

    if ( !ws )  delete [] g;
}
// -------------------------


void
inverse_haar_i2i(double *f, ulong ldn, double *ws/*=0*/)
//
// inverse transform wrt. to haar base
// integer input gives integer output
//
{
    ulong n = (1UL<<ldn);

    double *g = ws;
    if ( !ws )  g = new double[n];

    for (ulong m=2; m<=n; m<<=1)
    {
        ulong mh = (m>>1);
        for (ulong j=0,k=0; j<m; j+=2,k++)
        {
            double s = f[k];
            double d = f[mh+k];

            double y = s - floor(0.5*d);
            double x = d + y; // == s + floor(0.5*(d+1.0));

            g[j]    =  x;
            g[j+1]  =  y;
        }
        acopy(g, f, m);
    }

    if ( !ws )  delete [] g;
}
// -------------------------
