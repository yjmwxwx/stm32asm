#if !defined  HAVE_UNIQUEAPPROX_H__
#define       HAVE_UNIQUEAPPROX_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

template  <typename Type>
inline bool approx_equal(Type x1, Type x2, Type da)
// Return whether abs(x2-x1) <= da
// Must have da>=0
{
    Type d = x2 - x1;
    if ( d<=0 )  d = -d;
    if ( d < da )  return true;
    else           return false;
}
// -------------------------

template  <typename Type>
ulong test_unique_approx(const Type *f, ulong n, Type da)
// For a sorted array test whether all values are
// unique within some tolerance (i.e. whether no value is repeated).
// Return 0 if all values are unique,
// else return index of the second element in the first pair found.
// Makes mostly sense with inexact types (float or double)
{
    if ( da<=0 )  da = -da;  // want positive tolerance

    for (ulong k=1; k<n; ++k)
    {
        if ( approx_equal(f[k], f[k-1], da) )  return k;  // k != 0
    }

    return  0;
}
// -------------------------

template  <typename Type>
ulong is_unique_approx(const Type *f, ulong n, Type da)
// For a sorted array test whether all values are unique
// within some tolerance.
//
// Return true if all values are unique, else return false.
{
    return ( 0==test_unique_approx(f, n, da) );
}
// -------------------------


template  <typename Type>
ulong count_unique_approx(const Type *f, ulong n, Type da)
// For a sorted array return the number of unique values
// the number of (not necessarily distinct) repeated
//   values is n - count_unique_approx(f, n, da);
{
    if ( da<=0 )  da = -da;  // Must have positive tolerance
    ulong ct = (n!=0);
    for (ulong k=1; k<n; ++k)
    {
        if ( approx_equal(f[k], f[k-1], da) )  ++ct;
    }
    return  ct;
}
// -------------------------


template  <typename Type>
ulong unique_approx(Type *f, ulong n, Type da)
// For a sorted array squeeze all repeated (within tolerance da) values
// and return the number of unique values.
// Example:  [1, 3, 3, 4, 5, 8, 8] --> [1, 3, 4, 5, 8]
// The routine also works for unsorted arrays as long
// as identical elements only appear in contiguous blocks.
// Example: [4, 4, 3, 7, 7] --> [4, 3, 7]
// The order is preserved.
//.
// Note that the inner while-loop does never access an element out of
// bounds as it is executed only as long as there is at least one
// remaining change of value inside the array.
{
#if 1
    if ( n==0 )  return 0;
    Type v = f[0];
    ulong w = 1;
    for (ulong r=1; r<n; ++r)  // r is read position, w is write position
    {
        Type x = f[r];
        if ( ! approx_equal(x, v, da) )  { v = x;  f[w] = x;  ++w; }
        else    v = x;  // avoid problem with slowly drifting values

    }
    return w;

#else

    ulong u = count_unique_approx(f, n, da);

    if ( u==n )  return n;  // nothing to do

    if ( da<=0 )  da = -da;  // Must have positive tolerance
    Type v = f[0];
    for (ulong j=1, k=1;  j<u;  ++j)
    {
        // search next different element:
        while ( approx_equal(f[k], v, da) )
        {
            v = f[k];  // avoid problem with slowly drifting values
            ++k;
        }
        v = f[j] = f[k];
    }

    return u;
#endif
}
// -------------------------


#endif  // !defined HAVE_UNIQUEAPPROX_H__
