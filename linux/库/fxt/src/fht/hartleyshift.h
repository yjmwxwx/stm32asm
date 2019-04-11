#if !defined  HAVE_HARTLEYSHIFT_H__
#define       HAVE_HARTLEYSHIFT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/sincos.h"  // SinCos()
#include "aux0/sumdiff.h"  // sumdiff()
#include "aux0/constants.h"  // SQRT1_2

#include "fxttypes.h"

#include <cmath>  // sin()

// for trig recursions:
#define Tdouble long double
#define Sin     sinl
// use long double, else loss of precision with fht_loc_*()

template <typename Type>
inline void hartley_shift_05_v1(Type *f, ulong n)
// Hartley transform analogue to fourier_shift(f, n, 0.5)
// n := length of array
// Used for negacyclic convolution and recursive FHTs.
// Self-inverse.
{
    const double phi0 = PI/n;
    double phi = 0.0;
    for (ulong i=1, j=n-1;  i<j;  ++i, --j)
    {
        phi += phi0;
        double s, c;
        SinCos(phi, &s, &c);

        Type fi = f[i],  fj = f[j];
        f[i] = fi * c + fj * s;
        f[j] = fi * s - fj * c;
    }
}
// -------------------------

template <typename Type>
inline void hartley_shift_05_v1rec(Type *f, ulong n)
// Same as hartley_shift_05_v1() but with trigonometric recursion.
{
    const double phi0 = PI/n;
    Tdouble s = 0.0,  c = 1.0;
    Tdouble be = Sin(phi0),  al = Sin(0.5*phi0);  al *= (2.0*al);
    for (ulong i=1, j=n-1;  i<j;  ++i, --j)
    {
        { Tdouble tt = c;  c -= (al*tt+be*s);  s -= (al*s-be*tt); }

        Type fi = f[i],  fj = f[j];
        f[i] = fi * (double)c + fj * (double)s;  // jjcast
        f[j] = fi * (double)s - fj * (double)c;  // jjcast
    }
}
// -------------------------

template <typename Type>
inline void hartley_shift_05_v2(Type *f, ulong n)
// Optimized version,  n must be a power of 2.
{
    const double phi0 = PI/n;
    double phi = 0.0;
    const ulong nh = n/2;
    if ( n>=4 )
    {
        ulong im=nh/2, jm=3*im;
        Type fi = f[im],  fj = f[jm];
        double cs = SQRT1_2;
        f[im] = (fi + fj) * cs;
        f[jm] = (fi - fj) * cs;

        if ( n>=8 )
        {
            for (ulong i=1, j=n-1, k=nh-1, l=nh+1;  i<k;  ++i, --j, --k, ++l)
            {
                phi += phi0;
                double s, c;
                SinCos(phi, &s, &c);

                fi = f[i];
                fj = f[j];
                f[i] = fi * c + fj * s;
                f[j] = fi * s - fj * c;

                // l == i + nh;   k == j - nh;  swap2(c, s);
                fi = f[k];
                fj = f[l];
                f[k] = fi * s + fj * c;
                f[l] = fi * c - fj * s;
            }
        }
    }
}
// -------------------------

template <typename Type>
inline void hartley_shift_05_v2rec(Type *f, ulong n)
// Optimized version,  n must be a power of 2.
// Same as hartley_shift_05_v2() but with trigonometric recursion.
{
    const ulong nh = n/2;
    if ( n>=4 )
    {
        ulong im=nh/2, jm=3*im;
        Type fi = f[im],  fj = f[jm];
        double cs = SQRT1_2;
        f[im] = (fi + fj) * cs;
        f[jm] = (fi - fj) * cs;

        if ( n>=8 )
        {
            const Tdouble phi0 = PI/(double)n;
            Tdouble be = Sin(phi0),  al = Sin(0.5*phi0);  al *= (2.0*al);
            Tdouble s = 0.0,  c = 1.0;
            for (ulong i=1, j=n-1, k=nh-1, l=nh+1;  i<k;  ++i, --j, --k, ++l)
            {
                { Tdouble tt = c;  c -= (al*tt+be*s);  s -= (al*s-be*tt); }

                fi = f[i];
                fj = f[j];
                f[i] = fi * (double)c + fj * (double)s;  // jjcast
                f[j] = fi * (double)s - fj * (double)c;  // jjcast

                // l = i + nh;  k = j - nh;
                fi = f[k];
                fj = f[l];
                f[k] = fi * (double)s + fj * (double)c;  // jjcast
                f[l] = fi * (double)c - fj * (double)s;  // jjcast
            }
        }
    }
}
// -------------------------




//: inlines give default implementation:
template <typename Type>
inline void hartley_shift_05(Type *a, ulong n)
{ hartley_shift_05_v2rec(a, n); }


#undef Tdouble
#undef Sin

#endif  // !defined HAVE_HARTLEYSHIFT_H__
