// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "dctdst/dctdst.h"
#include "aux1/arith1.h"
#include "perm/ziprev.h"
#include "fxttypes.h"  // ulong

#include <cmath>  // sqrt()

static void
coseno(double *x, ulong ldn)
// Auxiliary routine called by dct_zapata().
// Input:
//  x[k] = \sum_{m=0}^{n-1}{ \prod_{i=0}^{ldn-1}{ 2^{b_i} \cos(b_i 2^i \Theta_m) x(m)} }
//  where n=2^ldn, \Theta_m=\pi (1+4m)/(2n)
//  and  b_i is bit #i of k
// Output:
//  x[k] = \sum_{m=0}^{n-1}{ \cos(\Theta_m) x(m)}
{
    for (ulong ldm=ldn-1; ldm>0; --ldm)
    {
        ulong m = 1L<<ldm;
        ulong mh = m>>1;
        for (ulong j=(1L<<(ldn-ldm))-2; (long)j>=0; --j)  // jjcast
        {
            for (ulong k=1; k<mh; ++k)  x[(j+1)*m+k] += x[j*m+k];

            ulong j2 = 2*j;
            x[(j2+3)*mh] -= x[(j2+1)*mh];
        }
    }
}
// -------------------------


void
dcth_zapata(double *x, ulong ldn, double *tmp/*=0*/)
// Transform wrt. basis: cos(k*(i+0.5)*PI/n) * (k==0?1.0:sqrt(2))
// Algorithm as described in F.Arguello, E.L.Zapata:
// "Fast Cosine Transform on the Successive Doubling Method"
//
// If a (size-n) srcatch space is supplied (tmp!=0)
// then the slightly faster version of unzip_rev() is used.
//
// Note the unzip_rev() step is not mentioned in the paper!
{
    if ( ldn==0 )  return;

    const ulong n = 1UL<<ldn;

    double *y;
    if ( tmp )
    {
        y = tmp;
        unzip_rev(x, y, n);
    }
    else
    {
        y = x;
        unzip_rev(x, n);
    }

    const double phi0 = 0.5*M_PI/(double)n;
    for (ulong ldm=1; ldm<=ldn; ++ldm)
    {
        ulong m = 1UL<<ldm;
        ulong mh = m>>1;
        ulong nm = 1UL<<(ldn-ldm);  // == n/m

        double phi1 = (double)mh * phi0;
        double phi4 = 4.0 * phi1;
        for (ulong k=0; k<nm; ++k)
        {
            double c = 2 * cos(phi1+(double)k*phi4);  // ==2*cos(M_PI*(4*k+1)*mh/(2*n));

            for (ulong j=0; j<mh; ++j)
            {
                ulong t1 = k+j*2*nm;
                ulong t2 = t1+nm;

                double a = x[t1];
                double b = x[t2];
                x[t1] += b;
                x[t2] = (a-b)*c;
            }
        }
    }

    revbin_permute(x, n);

    coseno(x, ldn);

    multiply_val(x+1, n-1, 1.0/sqrt(2));
}
// -------------------------
