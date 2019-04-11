// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux0/cmult.h"

#include "sort/minmax.h"
#include "aux1/arith1.h"

#include <cmath>  // sqrt()


//void
//chop(double *f, ulong n, double eps/*=1e-6*/)
//// set tiny elements to zero
//{
//    while ( n-- )  if ( fabs(f[n])<eps )  f[n] = 0.0;
//}
//// -------------------------


double
norm_l2(const double *f, ulong n)
// return sqrt(\sum_k{f[k]*f[k]})
{
    double v = 0.0;
    while ( n-- )  v += (f[n]*f[n]);
    return  sqrt(v);
}
// -------------------------


double
normalize(double *f, ulong n, double v/*=1.0*/)
// scale f[] to norm v
{
    double  a = norm_l2(f, n);
    if ( a!=0.0 )
    {
        v /= a;
        while ( n-- )  f[n] *= v;
    }
    return  a;
}
// -------------------------


//double
//sigma(const double *f, ulong n, double *mp/*=0*/)
//// return standard deviation
//// = sqrt(\sum_k{sqr(f[k]-mean(f[]))}/n)
//{
//    double m;
//    if ( 0!=mp )  m = *mp;
//    else          m = mean<double>(f,n);
//
//    double s = 0;
//    for (ulong i=0; i<n; ++i)
//    {
//        double t = f[i] - m;
//        s += t*t;
//    }
//    return  sqrt(s/(double)n);
//}
//// -------------------------
//
//void
//mean_sigma(const double *f, ulong n, double *mp, double *sp)
//// set *mp to mean, sp *to standard deviation of f[]
//{
//    *mp = mean<double>(f,n);
//    *sp = sigma(f,n,mp);
//}
//// -------------------------
//
//
//void
//smooth(double *f, ulong n, ulong m/*=1*/)
////  apply (1/4,1/2,1/4) - filter
//{
//    if ( n<=2 )  return;
//
//    for (ulong k=0; k<m; ++k)
//    {
//        double t1 = f[0], t2;
//        for (ulong i=1; i<=n-2; ++i)
//        {
//            t2 = t1;
//            t1 = 0.25*(f[i-1]+f[i+1]) + 0.5*f[i];
//            f[i-1] = t2;
//        }
//        f[n-2] = t1;
//    }
//}
//// -------------------------


double
rms_diff(const double *f, const double *g, ulong n)
// return sqrt(\sum_k{sqr(f[k]-g[k])})/n
{
    double err = 0;
    for (ulong i=0; i<n; ++i)
    {
        double d = f[i]-g[i];
        err += d*d;
    }

    return  sqrt(err)/(double)n;
}
// -------------------------


//ulong *
//histogram(const double *f, ulong n, ulong nbox, ulong *hh/*=0*/)
//// put histogram of f[] (with nbox boxes) into hh[]
//{
//    ulong *h = hh;
//    if ( 0==hh )  h = new ulong[nbox];
//
//    for (ulong i=0; i<nbox; ++i)  h[i] = 0;
//
//    double mi,ma;
//    min_max(f, n, &mi, &ma);
//    if ( ma==mi )
//    {
//        h[0] = n;
//    }
//    else // ( ma != mi )
//    {
//        const double dmi = (double)mi;
//        const double dma = (double)ma;
//        const double dnb = (double)nbox;
//        const double v = dnb / (dma-dmi);
//        for (ulong i=0; i<n; ++i)  ++h[(ulong)floor(v*(f[i]-dmi))];
//    }
//
//    return  h;
//}
//// -------------------------


//void
//welch_win(double *f, ulong n)
//// multiply f[] with a welch window
//// Note: should use trig recursion here
//{
//    const double pin = M_PI/(double)n;
//    double ph = 0.0;
//    for (ulong i=0; i<n; i++, ph+=pin)  f[i] *= (M_SQRT2*sin(ph));
//}
//// -------------------------


//void
//ri_multiply(const double *fr, const double *fi,
//            double *gr, double *gi, ulong n)
//// complex multiply array g[] by f[]:
////  Complex(gr[],gi[]) *= Complex(fr[],fi[])
//{
//    while ( n-- )  cmult(fr[n], fi[n], gr[n], gi[n]);
//}
//// -------------------------

