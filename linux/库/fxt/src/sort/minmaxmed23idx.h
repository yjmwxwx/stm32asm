#if !defined  HAVE_MINMAXMED23IDX_H__
#define       HAVE_MINMAXMED23IDX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

//: minimum and maximum of 2 or 3 elements, index versions
//: minimum, maximum and median of 3 elements, index versions

template <typename Type>
static inline ulong  idx_min2(const Type &x, const Type &y)
// Return index (0 or 1) of minimum of the input values
{ return  x<y ? 0 : 1; }

template <typename Type>
static inline ulong  idx_max2(const Type &x, const Type &y)
// Return index (0 or 1) of maximum of the input values
{ return  x>y ? 0 : 1; }

template <typename Type>
static inline ulong  idx_min3(const Type &x, const Type &y, const Type &z)
// Return index (0,1, or 2) of minimum of the input values
{ return  x<z ? (x<y ? 0 : 1 ) : (y<z ? 1 : 2); }

template <typename Type>
static inline ulong  idx_max3(const Type &x, const Type &y, const Type &z)
// Return index (0,1, or 2) of maximum of the input values
{ return  x>z ? (x>y ? 0 : 1 ) : (y>z ? 1 : 2); }

template <typename Type>
static inline void  idx_minmax3(Type x0, Type x1, Type x2, ulong &i, ulong &a)
// set i, a to index (0,1, or 2) of min and max, resp.
//.
// todo: optimize
{ i = idx_min3(x0, x1, x2);  a = idx_max3(x0, x1, x2); }

template <typename Type>
static inline ulong  idx_median3(const Type &x, const Type &y, const Type &z)
// Return index (0,1, or 2) of median of the input values
{ return  x<y ? (y<z ? 1 : (x<z ? 2 : 0)) : (z<y ? 1 : (z<x ? 2 : 0)); }


#endif  // !defined HAVE_MINMAXMED23IDX_H__
