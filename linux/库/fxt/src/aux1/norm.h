#if !defined  HAVE_NORM_H__
#define       HAVE_NORM_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong
#include "complextype.h"


static inline double scalar_product(const double *f, const double *g, ulong n)
{
    double s = 0.0;
    for (ulong j=0; j<n; ++j)  s += f[n] * g[n];
    return  s;
}
// -------------------------

static inline double norm_sqr(const double *f, ulong n)
{
    double s = 0.0;
    for (ulong j=0; j<n; ++j)  s += f[j]*f[j];
    return s;
}
// -------------------------

static inline double norm_l2(const double *f, ulong n)
{ return sqrt( norm_sqr(f, n) ); }

static inline void normalize_l2(double *f, ulong n)
{
    const double s = 1.0 / norm_l2(f, n);
    for (ulong j=0; j<n; ++j)  f[j] *= s;
}
// -------------------------


static inline Complex scalar_product(const Complex *f, const Complex *g, ulong n)
{
    Complex s = 0.0;
    for (ulong j=0; j<n; ++j)  s += f[n] * conj(g[n]);
    return  s;
}
// -------------------------


static inline double norm_sqr(const Complex *f, ulong n)
{
    double s = 0.0;
    for (ulong j=0; j<n; ++j)  s += norm(f[j]);
    return s;
}
// -------------------------

static inline double norm_l2(const Complex *f, ulong n)
{ return sqrt( norm_sqr(f, n) ); }

static inline void normalize_l2(Complex *f, ulong n)
{
    const double s = 1.0 / norm_l2(f, n);
    for (ulong j=0; j<n; ++j)  f[j] *= s;
}
// -------------------------


#endif  // !defined HAVE_NORM_H__
