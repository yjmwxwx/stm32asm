// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

//#include "jjassert.h"

#include <cmath>

static inline double sinc(double x)
// return sin(pi*x)/(pi*x)
{
    if ( x==0 )  return  1.0;
    else
    {
        x *= M_PI;
        return  sin(x) / x;
    }
}
// -------------------------

ulong
resample_sinc(const double *a, ulong an, double af, double *b, double bf, ulong bn)
// Input: an samples with freq af.
// Output: bn samples with freq bf.
// Return number of samples produced (<=bn).
// Must have: v>0
{
    const double v = af/bf;  // freq ratio
//    jjassert( v>0 );

    const double dan = (double)an;
    ulong  n = 1 + (ulong)floor(dan/v);  // # of samples produced  ??? correct
    if ( n>bn )  n = bn;

    for (ulong j=0; j<n; j++)
    {
        double s = (double)j * v;
        ulong  i = (ulong)s;
        double r = s - (double)i;
//        const double r = frac( j*v ); // ??

        b[j]=
            (a[i]  *sinc(2+r)+
             a[i+1]*sinc(1+r)+
             a[i+2]*sinc(r)+
             a[i+3]*sinc(1-r)+
             a[i+4]*sinc(2-r)+
             a[i+5]*sinc(3-r));   //*0.5;
    }

    return n;
}
// -------------------------


ulong
sample_up_linear(const double *f, ulong nf, double v, double *g, ulong ng)
//
// Uses linear interpolation (if noninteger v).
// Return number of values produced.
// Must have: v<=1.0
//
{
//    jjassert( v<=1.0 );

    ulong n = (ulong)floor( (double)nf / v);  // n values will be produced
    if ( n>ng )  n = ng;

    ulong gi,fi;
    if ( v==floor(0.5+v) )  // ----- integer value
    {
        const ulong vi=ulong(floor(0.5+v));
        for (fi=0,gi=0; gi<n; gi++,fi+=vi)  g[gi] = f[fi];
    }
    else  // ----- non integer value
    {
        double dfi, frac;
        for (dfi=0,gi=0; gi<n; gi++,dfi+=v)
        {
            fi = ulong(dfi);
            frac = dfi-double(fi);

            // linear interpolation:
            g[gi] = f[fi] + (f[fi+1]-f[fi])*frac;
        }
    }

    return n;
}
// -------------------------


ulong
sample_down_linear(const double *f, ulong nf, double v, double *g, ulong ng)
//
// Uses linear interpolation (if noninteger v).
// Return number of values produced.
// Must have: v>=1.0
//
{
//    jjassert( v>=1.0 );

    ulong n = (ulong)floor( (double)nf / v );  // n values will be produced
    if ( n>ng )  n = ng;

    ulong gi,fi;
    if ( v==floor(0.5+v) )  // ----- integer value
    {
        const ulong vi = ulong(floor(0.5+v));
        for (fi=0,gi=0; gi<n; gi++,fi+=vi)  g[gi] = f[fi];
    }
    else  // ----- non integer value
    {
        double dfi, frac;
        for (dfi=0,gi=0; gi<n; gi++,dfi+=v)
        {
            fi = ulong(dfi);
            frac = dfi-double(fi);

            // linear interpolation:
            g[gi] = f[fi] + (f[fi+1]-f[fi])*frac;
        }
    }

    return n;
}
// -------------------------


ulong
resample_linear(const double *f, ulong nf, double v, double *g, ulong ng)
//
// Use linear interpolation (if noninteger v).
// Return number of values produced.
//
{
    if ( v>=1.0 )  return sample_down_linear(f,nf,v,g,ng);
    else           return sample_up_linear(f,nf,v,g,ng);
}
// -------------------------
