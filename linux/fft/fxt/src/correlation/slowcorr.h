#if !defined  HAVE_SLOWCORR_H__
#define       HAVE_SLOWCORR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "fxtalloca.h"
#include "restrict.h"

#include "aux1/copy.h"


template <typename Type>
void slow_correlation(const Type *f, const Type *g, Type * restrict h, ulong n)
// Cyclic correlation of f[], g[], both real-valued sequences.
// n := array length
// slow_correlation(f, g, h, n)  =^=
// { reverse_0(g, n); slow_convolution(f, g, h, n); reverse_0(g, n); }
{
#if 0
    for (ulong tau=0;  tau<n;  ++tau)
    {
        Type s = 0;
        for (ulong k=0; k<n; ++k)
        {
             ulong k2 = k + tau;
             if ( k2>=n )  k2 -= n;
             s += (g[k]*f[k2]);
        }
        h[tau] = s;
    }
#else  // 0
    // avoid if in inner loop:
    for (ulong tau=0;  tau<n;  ++tau)
    {
        Type s = 0;
        ulong k = 0;
        for (ulong k2=tau;  k2<n;  ++k, ++k2)  s += (g[k]*f[k2]);
        for (ulong k2=0;     k<n;  ++k, ++k2)  s += (g[k]*f[k2]);
        h[tau] = s;
    }
#endif  // 0
}
// -------------------------


template <typename Type>
void slow_correlation0(const Type *f, const Type *g, Type * restrict h, ulong n)
// Linear correlation of f[], g[], both real-valued sequences.
// n := array length
// Version for zero padded data:
//   f[k],g[k] == 0 for k=n/2 ... n-1
// n must be >=2
{
    const ulong nh = n/2;
    for (ulong tau=0; tau<nh; ++tau)  // k2 == tau + k
    {
        Type s = 0;
        for (ulong k=0, k2=tau;  k2<nh;  ++k, ++k2)  s += (f[k]*g[k2]);
        h[tau] = s;
    }

    for (ulong tau=nh; tau<n; ++tau)  // k2 == tau + k - n
    {
        Type s = 0;
        for (ulong k=n-tau, k2=0;  k<nh;  ++k, ++k2)  s += (f[k]*g[k2]);
        h[tau] = s;
    }
}
// -------------------------



template <typename Type>
void slow_auto_correlation(const Type *f, Type * restrict g, ulong n)
// Cyclic self-correlation of f[], a real-valued sequence.
// Result is written to g[].
// n := array length
{
    slow_correlation(f, f, g, n);
}
// -------------------------

template <typename Type>
void slow_auto_correlation0(const Type *f, Type * restrict g, ulong n)
// Linear self-correlation of f[], a real-valued sequence.
// n := array length
// Result is written to g[].
// Input data must be zero padded:
//   f[n/2] .. f[n-1] == 0 and g[n/2] .. g[n-1] == 0
// n  must be >=2
{
    slow_correlation0(f, f, g, n);
}
// -------------------------


template <typename Type>
void slow_correlation(const Type *f, Type * restrict g, ulong n)
// Cyclic correlation of f[], g[], two real-valued sequences.
// n := array length
{
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_correlation(f, g, h, n);
    acopy(h, g, n);
}
// -------------------------

template <typename Type>
void slow_correlation0(const Type *f, Type * restrict g, ulong n)
// Linear correlation of f[], g[], two real-valued sequences.
// Result is written to g[].
// n := array length
// Input data must be zero padded:
//   f[n/2] .. f[n-1] == 0 and g[n/2] .. g[n-1] == 0
// n  must be >=2
{
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_correlation0(f, g, h, n);
    acopy(h, g, n);
}
// -------------------------


template <typename Type>
void slow_auto_correlation(Type *f, ulong n)
// Cyclic self-correlation of f[], a real-valued sequence.
// n := array length
{
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_correlation(f, f, h, n);
    acopy(h, f, n);
}
// -------------------------

template <typename Type>
void slow_auto_correlation0(Type *f, ulong n)
// Linear self-correlation of f[], a real-valued sequence.
// n := array length
// Input data must be zero padded:
//   f[n/2] .. f[n-1] == 0
// n  must be >=2
{
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_correlation0(f, f, h, n);
    acopy(h, f, n);
}
// -------------------------


#endif  // !defined HAVE_SLOWCORR_H__
