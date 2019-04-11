#if !defined  HAVE_IS_NONSQUASHING_H__
#define       HAVE_IS_NONSQUASHING_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
inline bool is_nonsquashing(const Type *a, ulong m)
// Return whether a[k] >= sum(j=k+1..m-1, a[j] ).
{
    if ( m<=1 )  return true;
    Type w = 0;
    ulong j = m - 1;
    do
    {
        Type v = a[j];
        if ( w > v )  return false; // non-squashing, cf. A018819
        w += v;
    }
    while ( j-- );
    return true;
}
// -------------------------

template <typename Type>
inline bool is_strongly_decreasing(const Type *a, ulong m)
// Return whether a[k] > sum(j=k+1..m-1, a[j] )
{
    if ( m<=1 )  return true;
    Type w = 0;
    ulong j = m - 1;
    do
    {
        Type v = a[j];
        if ( w>=v )  return false; // strongly decreasing, cf. A040039
        w += v;
    }
    while ( j-- );
    return true;
}
// -------------------------


template <typename Type>
inline bool is_nonsquashing_asc(const Type *a, ulong m)
// Return whether a[k] >= sum(j=0..k-1, a[j] )
{
    if ( m<=1 )  return true;
    Type w = 0;
    ulong j = 0;
    do
    {
        Type v = a[j];
        if ( w > v )  return false; // non-squashing, cf. A018819
        w += v;
    }
    while ( ++j < m );
    return true;
}
// -------------------------

template <typename Type>
inline bool is_strongly_increasing(const Type *a, ulong m)
// Return whether a[k] > sum(j=0..k-1, a[j] )
{
    if ( m<=1 )  return true;
    Type w = 0;
    ulong j = 0;
    do
    {
        Type v = a[j];
        if ( w>=v )  return false; // strongly increasing, cf. A040039
        w += v;
    }
    while ( ++j < m );
    return true;
}
// -------------------------

#endif // !defined HAVE_IS_NONSQUASHING_H__
