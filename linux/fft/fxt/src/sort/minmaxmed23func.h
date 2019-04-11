#if !defined  HAVE_MINMAXMED23FUNC_H__
#define       HAVE_MINMAXMED23FUNC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

//: minimum and maximum of 2 or 3 elements, with comparison function
//: minimum, maximum and median of 3 elements, with comparison function


template <typename Type>
static inline Type  min2(const Type &x, const Type &y,
                         int (*cmp)(const Type &, const Type &))
// Return minimum of the input values wrt. cmp()
{ int q=cmp(x, y);  return q<0 ? x : y; }

template <typename Type>
static inline Type  max2(const Type &x, const Type &y,
                         int (*cmp)(const Type &, const Type &))
// Return maximum of the input values wrt. cmp()
{ int q=cmp(x, y);  return q<0 ? x : y; }


template <typename Type>
Type  min3(const Type &x, const Type &y, const Type &z,
           int (*cmp)(const Type &, const Type &))
// Return minimum of the input values wrt. cmp()
{ return  min2( min2(x, y, cmp), z, cmp); }

template <typename Type>
Type  max3(const Type &x, const Type &y, const Type &z,
           int (*cmp)(const Type &, const Type &))
// Return maximum of the input values wrt. cmp()
{ return  max2( max2(x, y, cmp), z, cmp); }


template <typename Type>
Type  median3(const Type &x, const Type &y, const Type &z,
              int (*cmp)(const Type &, const Type &))
// Return median of the input values wrt. cmp()
{
    if ( cmp(x, y)<0 )  // return (y<z ? y : (x<z ? z : x))
    {
        if ( cmp(y, z)<0 )  return y;
        else                return ( cmp(x, z)<0 ? z : x);
    }
    else  // return (z<y ? y : (z<x ? z : x))
    {
        if ( cmp(z, y)<0 )  return y;
        else                return ( cmp(z, x)<0 ? z : x);
    }
}
// -------------------------


template <typename Type>
const Type *median3_ptr(const Type *x, const Type *y, const Type *z,
                        int (*cmp)(const Type &, const Type &))
// Return (pointer to) median of the input values wrt. cmp()
{
    if ( cmp(*x, *y)<0 )  // return (y<z ? y : (x<z ? z : x))
    {
        if ( cmp(*y, *z)<0 )  return y;
        else                  return ( cmp(*x, *z)<0 ? z : x);
    }
    else  // return (z<y ? y : (z<x ? z : x))
    {
        if ( cmp(*z, *y)<0 )  return y;
        else                  return ( cmp(*z, *x)<0 ? z : x);
    }
}
// -------------------------


#endif  // !defined HAVE_MINMAXMED23FUNC_H__
