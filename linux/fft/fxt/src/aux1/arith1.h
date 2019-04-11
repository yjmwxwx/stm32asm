#if !defined HAVE_ARITH1_H__
#define      HAVE_ARITH1_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


//template <typename Type>
//inline Type sum(const Type *f, ulong n)
//// return \sum_k {f[k]}
//{
//    Type s(0);
//    while ( n-- )  s += f[n];
//    return  s;
//}
//// -------------------------

//template <typename Type>
//inline Type mean(const Type *f, ulong n)
//// return (\sum_k{f[k]})/n
//{
//    return  sum(f, n) / (Type)n;
//}
//// -------------------------
//
//template <typename Type>
//inline Type subtract_mean(Type *f, ulong n)
//// subtract from f[] its mean value
//// return mean value
//{
//    Type m = mean(f, n);
//    for (ulong i=0; i<n; ++i)  f[i] -= m;
//    return  m;
//}
//// -------------------------
//
//
//template <typename Type>
//inline Type scalar_product(const Type *f, ulong n)
//// return \sum_k {f[k]*f[k]}
//{
//    Type s(0);
//    while ( n-- )  s += f[n] * f[n];
//    return  s;
//}
//// -------------------------
//
//template <typename Type>
//inline Type scalar_product(const Type *f, const Type *g, ulong n)
//// return \sum_k {f[k]*g[k]}
//{
//    Type s(0);
//    while ( n-- )  s += f[n] * g[n];
//    return  s;
//}
//// -------------------------
//
//
//template <typename Type>
//inline Type sum_of_squares(const Type *f, ulong n)
//// return \sum_k {f[k]*f[k]}
//{
//    Type s(0);
//    while ( n-- )  s += f[n] * f[n];
//    return  s;
//}
//// -------------------------
//
//template <typename Type>
//inline Type sqr_diff(const Type *f, const Type *g, ulong n)
//// return \sum_k { (f[k]-g[k])^2 }
//{
//    Type s(0);
//    while ( n-- ) { Type d = f[n] - g[n];  s += d * d; }
//    return  s;
//}
//// -------------------------


//template <typename Type>
//inline Type delta_sqr_diff(const Type *f, ulong n, ulong d0, Type v=1)
//// return \sum { (f[]-delta(d0) )^2 }
//{
//    Type s(0);
//    for (ulong k=0; k<d0; ++k)  { Type d = f[k];  s += d * d; }
//    if ( d0<n )  { Type d = f[d0] - v;  s += d * d; }
//    for (ulong k=d0+1; k<n; ++k)  { Type d = f[k];  s += d * d; }
//    return  s;
//}
//// -------------------------



template <typename Type>
inline void negate(Type *f, ulong n)
// negate every element of f[]
{
    while ( n-- )  f[n] = -f[n];
}
// -------------------------

//template <typename Type>
//inline void add_val(Type *f, ulong n, Type s)
//// f[] += g
//{
//    while ( n-- )  f[n] += s;
//}
//// -------------------------
//
//template <typename Type>
//inline void subtract_val(Type *f, ulong n, Type s)
//// f[] -= g
//{
//    while ( n-- )  f[n] -= s;
//}
//// -------------------------


template <typename Type>
inline void multiply_val(Type *f, ulong n, Type s)
// f[] *= s
{
    while ( n-- )  f[n] *= s;
}
// -------------------------

template <typename Type>
inline void add(Type *f, ulong n, const Type *g)
// f[] += g[] element-wise
{
    while ( n-- )  f[n] += g[n];
}
// -------------------------

template <typename Type>
inline void subtract(Type *f, ulong n, const Type *g)
// f[] -= g[] element-wise
{
    while ( n-- )  f[n] -= g[n];
}
// -------------------------


template <typename Type>
inline void multiply(Type *f, ulong n, const Type *g)
//  f[] *= g[] element-wise
{
    while ( n-- )  f[n] *= g[n];
}
// -------------------------

//template <typename Type>
//inline void divide(Type *f, ulong n, const Type *g)
////  f[] /= g[] element-wise  (no check for overflow !)
//{
//    while ( n-- )  f[n] /= g[n];
//}
//// -------------------------


#endif  // !defined HAVE_ARITH1_H__
