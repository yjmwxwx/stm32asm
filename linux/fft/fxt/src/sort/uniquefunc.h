#if !defined  HAVE_UNIQUEFUNC_H__
#define       HAVE_UNIQUEFUNC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template  <typename Type>
ulong test_unique(const Type *f, ulong n, int (*cmp)(const Type &, const Type &))
// For a sorted array test whether all values are unique
//   (i.e. whether no value is repeated).
// Return 0 if all values are unique else return index of the second
// element in the first pair found.
{
    for (ulong k=1; k<n; ++k)
        if ( cmp(f[k], f[k-1]) == 0 )  return  k;  // k != 0
    return  0;
}
// -------------------------

template  <typename Type>
bool is_unique(const Type *f, ulong n, int (*cmp)(const Type &, const Type &))
// For a sorted array test whether all values are unique
//
// Return true if all values are unique, else return false.
{
    return ( 0==test_unique(f, n, cmp) );
}
// -------------------------



template  <typename Type>
ulong count_unique(const Type *f, ulong n, int (*cmp)(const Type &, const Type &))
// For a sorted array return the number of unique values
// the number of (not necessarily distinct) repeated
//   values is n - unique_count(f, n);
{
    ulong ct = (n != 0);
    for (ulong k=1; k<n; ++k)
        if ( cmp(f[k], f[k-1]) != 0 )  ++ct;  // change detected

    return  ct;
}
// -------------------------


template  <typename Type>
ulong unique(Type *f, ulong n, int (*cmp)(const Type &, const Type &))
// For a sorted array squeeze all repeated values
// and return the number of unique values.
// Example:  [1, 3, 3, 4, 5, 8, 8] --> [1, 3, 4, 5, 8]
// The routine also works for unsorted arrays as long
// as identical elements only appear in contiguous blocks.
// Example: [4, 4, 3, 7, 7] --> [4, 3, 7]
// The order is preserved.
{
    if ( n<=1 )  return n;
    Type v = f[0];
    ulong w = 1;
    for (ulong r=1; r<n; ++r)  // r is read position, w is write position
    {
        Type x = f[r];
        if ( cmp(x, v) != 0 )  { v = x;  f[w] = x;  ++w; }
    }
    return w;
}
// -------------------------


#endif // !defined HAVE_UNIQUEFUNC_H__
