#if !defined  HAVE_MINMAXMED23_H__
#define       HAVE_MINMAXMED23_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

//: minimum and maximum of 2 or 3 elements
//: minimum, maximum and median of 3 elements


template <typename Type>
static inline Type  min2(const Type &x, const Type &y)
// Return minimum of the input values
{ return  x<y ? x : y; }

template <typename Type>
static inline Type  max2(const Type &x, const Type &y)
// Return maximum of the input values
{ return  x>y ? x : y; }



template <typename Type>
static inline Type  min3(const Type &x, const Type &y, const Type &z)
// Return minimum of the input values
{ return  min2( min2(x, y), z ); }

template <typename Type>
static inline Type  max3(const Type &x, const Type &y, const Type &z)
// Return maximum of the input values
{ return  max2( max2(x, y), z ); }

template <typename Type>
static inline Type  median3(const Type &x, const Type &y, const Type &z)
// Return median of the input values
{ return  x<y ? (y<z ? y : (x<z ? z : x)) : (z<y ? y : (z<x ? z : x)); }


#endif  // !defined HAVE_MINMAXMED23_H__
