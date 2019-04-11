#if !defined  HAVE_USEARCH_H__
#define       HAVE_USEARCH_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
inline ulong first_eq_idx(const Type *f, ulong n, Type v)
// Return index of first element == v
// Return n if all !=v
{
    ulong k = 0;
    while ( (k<n) && (f[k]!=v) )  k++;
    return k;
}
// -------------------------

template <typename Type>
inline ulong first_eq_idx_large(const Type *f, ulong n, Type v)
// Return index of first element == v
// Return n if all !=v
// Unrolled version for large arrays.
{
    ulong k;
    for (k=0; k<(n&3); ++k)  if ( f[k]==v )  return k;

    while ( k!=n )  // 4-fold unrolled
    {
        Type t0 = f[k],  t1 = f[k+1],  t2 = f[k+2],  t3 = f[k+3];
        bool qa = ( (t0==v) | (t1==v) );  // note bit-wise OR to avoid branch
        bool qb = ( (t2==v) | (t3==v) );
        if ( qa | qb )  // element v found
        {
            while ( 1 )  { if ( f[k]==v )  return k;  else ++k; }
        }
        k += 4;
    }

    return n;
}
// -------------------------


template <typename Type>
inline ulong first_neq_idx(const Type *f, ulong n, Type v)
// Return index of first element != v
// Return n if all ==v
{
    ulong k = 0;
    while ( (k<n) && (f[k]==v) )  k++;
    return k;
}
// -------------------------


template <typename Type>
inline ulong first_geq_idx(const Type *f, ulong n, Type v)
// Return index of first element >=v
// Return n if no such element is found
{
    for (ulong i=0; i<n; ++i)  if ( f[i]>=v )  return i;
    return n;
}
// -------------------------


template <typename Type>
inline ulong first_leq_idx(const Type *f, ulong n, Type v)
// Return index of first element <=v
// Return n if no such element is found
{
    for (ulong i=0; i<n; ++i)  if ( f[i]<=v )  return i;
    return n;
}
// -------------------------



template <typename Type>
inline ulong last_eq_idx(const Type *f, ulong n, Type v)
// Return index of last element == v
// Return n if all !=v
{
    ulong k = n-1;
    while ( f[k]!=v )
    {
        k--;
        if ( 0==k )  return n;
    }
    return k;
}
// -------------------------


template <typename Type>
inline ulong last_neq_idx(const Type *f, ulong n, Type v)
// Return index of last element != v
// Return n if all ==v
{
    ulong k = n-1;
    while ( f[k]==v )
    {
        k--;
        if ( 0==k )  return n;
    }
    return k;
}
// -------------------------


template <typename Type>
inline ulong last_geq_idx(const Type *f, ulong n, Type v)
// Return index of last element >= v
// Return n if all <v
{
    ulong k = n-1;
    while ( f[k]<v )
    {
        k--;
        if ( 0==k )  return n;
    }
    return k;
}
// -------------------------


template <typename Type>
inline ulong last_leq_idx(const Type *f, ulong n, Type v)
// Return index of last element <= v
// Return n if all >v
{
    ulong k = n-1;
    while ( f[k]>v )  { k--;  if ( 0==k )  return n; }
    return k;
}
// -------------------------


template <typename Type>
bool u_unique(const Type *f, ulong n)
// Return whether elements in unordered array f[] are unique.
// Algorithm is O(n^2), so use for small n only.
{
    for (ulong j=0; j<n; ++j)
    {
        const Type fj = f[j];
        for (ulong k=j+1; k<n; ++k)
            if ( fj == f[k] )  return false;
    }
    return true;
}
// -------------------------


#endif  // !defined HAVE_USEARCH_H__
