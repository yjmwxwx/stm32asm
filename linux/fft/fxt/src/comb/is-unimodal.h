#if !defined HAVE_IS_UNIMODAL_H__
#define      HAVE_IS_UNIMODAL_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

template <typename Type>
inline bool is_weakly_unimodal(const Type *f, ulong n)
// Return whether sequence is weakly unimodal.
{
    if ( n<=2 )  return true;

    ulong j = 1;
    while ( j < n )  // scan over weakly increasing part
    {
        if ( f[j-1] > f[j] )  break;
        ++j;
    }

    ++j;

    while ( j < n )  // scan over weakly decreasing part
    {
        if ( f[j-1] < f[j] )  break;
        ++j;
    }

    return ( j >= n );
}
// -------------------------


template <typename Type>
inline bool is_strongly_unimodal(const Type *f, ulong n)
// Return whether sequence is strongly unimodal.
{
    if ( n<=1 )  return true;

    ulong j = 1;

    while ( j < n )  // scan over strictly increasing part
    {
        if ( f[j-1] >= f[j] )  break;
        ++j;
    }

    while ( j < n )  // scan over strictly decreasing part
    {
        if ( f[j-1] <= f[j] )  break;
        ++j;
    }

    return ( j >= n );
}
// -------------------------


#endif  // !defined HAVE_IS_UNIMODAL_H__
