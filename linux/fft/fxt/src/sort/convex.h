#if !defined HAVE_CONVEX_H__
#define      HAVE_CONVEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template <typename Type>
ulong test_strictly_convex(const Type *f, ulong n)
// Return index of maximum for strictly convex sequence,
//   otherwise return 0.
// "strictly convex" means "strongly unimodal" and there
// is at least one upstep and downstep in the sequence.
{
    if ( n<=2 )  return 0;

    // the following two lines make sure the searches below stop:
    if ( f[0] >= f[1] ) return 0;
    if ( f[n-2] <= f[n-1] ) return 0;

    ulong i = 0;
    do  { ++i; }  while ( f[i-1] < f[i] );
    --i;
    // i is second index of last rising pair from start

    ulong j = n - 1;
    do  { --j; }  while ( f[j] > f[j+1] );
    ++j;
    // j is first index of last falling pair from end (going backwards)

    if ( i!=j )  return 0;
    return i;
}
// -------------------------


template <typename Type>
ulong test_strictly_concave(const Type *f, ulong n)
// Return index of minimum for strictly concave sequence,
//   otherwise return 0
{
    if ( n<=2 )  return 0;

    // the following two lines make sure the searches below stop:
    if ( f[0] <= f[1] ) return 0;
    if ( f[n-2] >= f[n-1] ) return 0;

    ulong i = 0;
    do  { ++i; }  while ( f[i-1] > f[i] );
    --i;
    // i is second index of last falling pair from start

    ulong j = n - 1;
    do  { --j; }  while ( f[j] < f[j+1] );
    ++j;
    // j is first index of last rising pair from end (going backwards)

    if ( i!=j )  return 0;
    return i;
}
// -------------------------

template <typename Type>
bool is_strictly_convex(const Type *f, ulong n)
{ return (0 != test_strictly_convex(f, n)); }

template <typename Type>
bool is_strictly_concave(const Type *f, ulong n)
{ return (0 != test_strictly_concave(f, n)); }


template <typename Type>
bool is_weakly_convex(const Type *f, ulong n)
// Return whether sequence is weakly convex (weakly unimodal).
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
bool is_weakly_concave(const Type *f, ulong n)
// Return whether sequence is weakly concave.
{
    if ( n<=2 )  return true;
    ulong j = 1;
    while ( j < n )  // scan over weakly decreasing part
    {
        if ( f[j-1] < f[j] )  break;
        ++j;
    }
    ++j;
    while ( j < n )  // scan over weakly increasing part
    {
        if ( f[j-1] > f[j] )  break;
        ++j;
    }
    return ( j >= n );
}
// -------------------------



#endif  // !defined HAVE_CONVEX_H__
