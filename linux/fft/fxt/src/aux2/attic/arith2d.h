#if !defined HAVE_ARITH2D_H__
#define      HAVE_ARITH2D_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "aux1/arith1.h"


template <typename Type>
inline Type sum(const Type *const*f, ulong nr, ulong nc)
// return \sum_{k,j} {f[k][j]}
{
    Type s(0);
    while ( nr-- )  s += sum(f[nr], nc);
    return s;
}
// -------------------------


template <typename Type>
inline Type sum_of_squares(const Type *const*f, ulong nr, ulong nc)
// return \sum_{k,j} {f[k][j]*f[k][j]}
{
    Type s(0);
    while ( nr-- )  s += sum_of_squares(f[nr], nc);
    return  s;
}
// -------------------------


template <typename Type>
inline void negate(Type **f, ulong nr, ulong nc)
// negate every value of f[][]
{
    while ( nr-- )  negate(f[nr], nc);
}
// -------------------------

template <typename Type>
inline void add_val(Type **f, ulong nr, ulong nc, Type s)
// f[][] += g
{
    while ( nr-- )  add_val(f[nr], nc, s);
}
// -------------------------

template <typename Type>
inline void subtract_val(Type **f, ulong nr, ulong nc, Type s)
// f[][] -= g
{
    while ( nr-- )  subtract_val(f[nr], nc, s);
}
// -------------------------

template <typename Type>
inline void multiply_val(Type **f, ulong nr, ulong nc, Type s)
// f[][] *= s
{
    while ( nr-- )  multiply_val(f[nr], nc, s);
}
// -------------------------


template <typename Type>
inline void add(Type **f, ulong nr, ulong nc, const Type *const*g)
// f[][] += g[][] element-wise
{
    while ( nr-- )  add(f[nr], nc, g[nr]);
}
// -------------------------

template <typename Type>
inline void subtract(Type **f, ulong nr, ulong nc, const Type *const*g)
// f[][] -= g[][] element-wise
{
    while ( nr-- )  subtract(f[nr], nc, g[nr]);
}
// -------------------------

template <typename Type>
inline void multiply(Type **f, ulong nr, ulong nc, const Type *const*g)
// f[][] *= g[][] element-wise
{
    while ( nr-- )  multiply(f[nr], nc, g[nr]);
}
// -------------------------


template <typename Type>
inline void divide(Type **f, ulong nr, ulong nc, const Type *const*g)
// f[][] /= g[][]  (no check for overflow !)
{
    while ( nr-- )  divide(f[nr], nc, g[nr]);
}
// -------------------------




#endif // !defined HAVE_ARITH2D_H__
