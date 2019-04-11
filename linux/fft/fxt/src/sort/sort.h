#if !defined HAVE_SORT_H__
#define      HAVE_SORT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "sort/minmaxmed23.h"
#include "aux0/swap.h"
#include "fxttypes.h"


template  <typename Type>
bool is_sorted(const Type *f, ulong n)
// Return whether the sequence f[0], f[1], ..., f[n-1] is sorted in
// ascending (indeed non-decreasing) order.
{
    for (ulong k=1; k<n; ++k)  if ( f[k-1] > f[k] )  return false;
    return  true;
}
// -------------------------


template  <typename Type>
bool is_sorted_desc(const Type *f, ulong n)
// Return whether the sequence f[0], f[1], ..., f[n-1] is sorted in
// descending (indeed non-increasing) order.
{
    for (ulong k=1; k<n; ++k)  if ( f[k-1] < f[k] )  return false;
    return  true;
}
// -------------------------


template <typename Type>
void selection_sort(Type *f, ulong n)
// Sort f[] (ascending order).
// Algorithm is O(n*n), use for short arrays only.
{
    for (ulong i=0; i<n; ++i)
    {
        Type v = f[i];
        ulong m = i;  // position of minimum
        ulong j = n;
        while ( --j > i )  // search (index of) minimum
        {
            if ( f[j] < v )
            {
                m = j;
                v = f[m];
            }
        }

        swap2(f[i], f[m]);
    }
}
// -------------------------


template  <typename Type>
bool is_partitioned(const Type *f, ulong n, ulong k)
// Return whether
//  max(f[0], ..., f[p]) <= min(f[p+1], ..., f[n-1])
{
    ++k;
    Type lmax = max(f,   k);
    Type rmin = min(f+k, n-k);

    return  ( lmax <= rmin );
}
// -------------------------


template <typename Type>
ulong partition(Type *f, ulong n)
// Rearrange array, so that for some index p
// max(f[0], ..., f[p]) <= min(f[p+1], ..., f[n-1])
{
    // Avoid worst case with already sorted input:
    const Type v = median3(f[0], f[n/2], f[n-1]);

    ulong i = 0UL - 1;
    ulong j = n;
    while ( 1 )
    {
        do  { ++i; }  while ( f[i]<v );
        do  { --j; }  while ( f[j]>v );

        if ( i < j )  swap2(f[i], f[j]);
        else          return j;
    }
}
// -------------------------


template <typename Type>
void quick_sort(Type *f, ulong n)
// Sort f[] (ascending order).
{
 start:
    if ( n < 8 )  // parameter: threshold for nonrecursive algorithm
    {
        selection_sort(f, n);
        return;
    }

    ulong p = partition(f, n);
    ulong ln = p + 1;
    ulong rn = n - ln;

    if ( ln > rn )  // recursion for shorter sub-array
    {
        quick_sort(f+ln, rn);  // f[ln] ... f[n-1]   right
        n = ln;
    }
    else
    {
        quick_sort(f, ln);  // f[0]  ... f[ln-1]  left
        n = rn;
        f += ln;
    }

    goto start;
}
// -------------------------


#endif  // !defined HAVE_SORT_H__
