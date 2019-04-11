#if !defined  HAVE_SUBSET_CONVOLUTION_H__
#define       HAVE_SUBSET_CONVOLUTION_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "walsh/or-convolution.h"
#include "walsh/weighted-or-convolution.h"

#include "bits/bitsubsetq.h"
#include "aux0/csincos.h"

#include "aux1/copy.h"  // copy_cast(), acopy()

#include "complextype.h"
#include "fxttypes.h"

#include <cmath>  // M_PI



template <typename Type>
inline void slow_subset_convolution(const Type *f, const Type *g, ulong ldn, Type *h)
// Compute the subset convolution h[] of f[] and g[]:
//   h[k] = sum( j subset k,  f[j]*g[k-j] )
// Could iterate over subsets to make faster.
{
    const ulong n = 1UL << ldn;
    for (ulong k=0; k<n; ++k)
    {
        Type hk = 0;
        for (ulong j=0; j<n; ++j)  if ( is_subset(j, k) )  hk += f[j]*g[k-j];
        h[k] = hk;
    }
}
// -------------------------

template <typename Type>
inline void slow_subset_convolution(const Type *f, Type *g, ulong ldn)
// Result written to g[].
{
    const ulong n = 1UL << ldn;
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_subset_convolution(f, g, ldn, h);
    acopy(h, g, n);
}
// -------------------------

template <typename Type>
inline void slow_subset_auto_convolution(const Type *f, ulong ldn, Type *h)
// Compute the subset auto- convolution of f[]:
//   h[k] = sum( j subset k,  f[j]*f[k-j] )
{
    const ulong n = 1UL << ldn;
    for (ulong k=0; k<n; ++k)
    {
        Type hk = 0;
        for (ulong j=0; j<n; ++j)  if ( is_subset(j, k) )  h[k] += f[j]*f[k-j];
        h[k] = hk;
    }
}
// -------------------------

template <typename Type>
inline void slow_subset_auto_convolution(const Type *f, Type *g, ulong ldn)
// Result written to g[].
{
    const ulong n = 1UL << ldn;
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_subset_convolution(f, f, ldn, h);
    acopy(h, g, n);
}
// -------------------------

template <typename Type>
inline void subset_convolution(Type *f, Type *g, ulong ldn)
// Compute the subset convolution h[] of f[] and g[]:
//   h[k] = sum( j subset k,  f[j]*g[k-j] )
// Type must allow conversion to and from type Complex.
// Result written to g[].
{
    const ulong n = 1UL << ldn;
    Complex *fc, *gc, *hc;
    fc = new Complex[n];
    gc = new Complex[n];
    hc = new Complex[n];

    // w^0:
    copy_cast(f, fc, n);
    copy_cast(g, gc, n);
    or_convolution(fc, gc, ldn);
    acopy(gc, hc, n);

    // w^1, w^2, ... , w^(L-1):
    const ulong L = ldn + 1;
    const Complex w = SinCos( 2*M_PI/(double)L );
    Complex wp = 1.0;  // powers of w
    for (ulong j=1; j<L; ++j)
    {
        copy_cast(f, fc, n);
        copy_cast(g, gc, n);
        wp *= w;
        weighted_or_convolution(fc, gc, ldn, wp);
        for (ulong k=0; k<n; ++k)  hc[k] += gc[k];
    }

    const double x = 1.0/(double)L;
    for (ulong k=0; k<n; ++k)  hc[k] *= x;
    for (ulong k=0; k<n; ++k)  g[k] = (Type)hc[k].real();

    delete [] fc;
    delete [] gc;
    delete [] hc;
}
// -------------------------

template <typename Type>
inline void subset_auto_convolution(Type *f, ulong ldn)
// Compute the subset auto- convolution h[] of f[]:
//   h[k] = sum( j subset k,  f[j]*f[k-j] )
// Type must allow conversion to and from type Complex
// Result written to f[].
{
    const ulong n = 1UL << ldn;
    Complex *fc, *hc;
    fc = new Complex[n];
    hc = new Complex[n];

    // w^0:
    copy_cast(f, hc, n);
    or_auto_convolution(hc, ldn);

    // w^1, ... , w^(L-1):
    const ulong L = ldn + 1;
    const Complex w = SinCos( 2*M_PI/(double)L );
    Complex wp = 1.0;  // powers of w
    for (ulong j=1; j<L; ++j)
    {
        copy_cast(f, fc, n);
        wp *= w;
        weighted_or_auto_convolution(fc, ldn, wp);
        for (ulong k=0; k<n; ++k)  hc[k] += fc[k];
    }

    const double x = 1.0/(double)L;
    for (ulong k=0; k<n; ++k)  hc[k] *= x;
    for (ulong k=0; k<n; ++k)  f[k] = (Type)hc[k].real();

    delete [] fc;
    delete [] hc;
}
// -------------------------



#endif  // !defined HAVE_SUBSET_CONVOLUTION_H__
