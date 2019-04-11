#if !defined  HAVE_HEAP_H__
#define       HAVE_HEAP_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "aux0/swap.h"


template <typename Type>
ulong test_heap(const Type *x, ulong n)
// Return 0 if x[] has heap property
// else index of node found to be greater than its parent.
{
    const Type *p = x - 1;  // make one-based
    for (ulong k=n; k>1; --k)
    {
        ulong t = (k>>1);  // parent(k)
        if ( p[t]<p[k] )  return k-1;  // in {1, 2, ..., n}
    }
    return 0;  // has heap property
}
// -------------------------


template <typename Type>
void heapify(Type *z, ulong n, ulong k)
// Subject to the condition that the trees below the children of node
// k are heaps, move the element z[k] (down) until the tree below node k is a heap.
// Data expected in z[1,2,...,n].
{
    ulong m = k;  // index of max of k, left(k), and right(k)

    const ulong l = (k<<1);  // left(k);
    if ( (l <= n) && (z[l] > z[k]) )  m = l;  // left child (exists and) greater than k

    const ulong r = (k<<1) + 1;  // right(k);
    if ( (r <= n) && (z[r] > z[m]) )  m = r;  // right child (exists and) greater than max(k,l)

    if ( m != k )  // need to swap
    {
        swap2(z[k], z[m]);
        heapify(z, n, m);
    }
}
// -------------------------

template <typename Type>
void build_heap(Type *x, ulong n)
// Reorder data to a heap.
// Data expected in x[0,1,...,n-1].
{
    Type *z = x - 1;   // make one-based
    ulong j = (n>>1);  // max index such that node has at least one child
    while ( j > 0 )
    {
        heapify(z, n, j);
        --j;
    }
//    for (ulong j=(n>>1); j>0; --j)  heapify(z, n, j);
}
// -------------------------


template <typename Type>
bool heap_insert(Type *x, ulong n, ulong s, Type t)
// With x[] a heap of current size n
// and max size s (i.e. space for s elements allocated),
// insert t and restore heap-property.
// Return true if successful, else (i.e. if space exhausted) false.
// Complexity is O(log(n)).
{
    if ( n > s )  return false;
    ++n;
    Type *x1 = x - 1;  // make one-based
    ulong j = n;
    while ( j > 1 )  // move towards root as needed
    {
        ulong k = (j>>1);  // k==parent(j)
        if ( x1[k] >= t )  break;
        x1[j] = x1[k];
        j = k;
    }
    x1[j] = t;
    return true;
}
// -------------------------

template <typename Type>
Type heap_extract_max(Type *x, ulong n)
// Return maximal element of heap and restore heap structure.
// Return value is undefined for 0==n.
{
    Type m = x[0];
    if ( 0 != n )
    {
        Type *x1 = x - 1;
        x1[1] = x1[n];
        --n;
        heapify(x1, n, 1);
    }
    return m;
}
// -------------------------


#endif  // !defined HAVE_HEAP_H__
