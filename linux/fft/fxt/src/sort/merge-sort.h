#if !defined HAVE_MERGE_SORT_H__
#define      HAVE_MERGE_SORT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "sort/sort.h"  // selection_sort()

#include "restrict.h"
#include "fxttypes.h"


template  <typename Type>
void merge(const Type * const restrict f, ulong na, ulong nb, Type * const restrict t)
// Merge the (sorted) arrays
//   A[] := f[0], f[1], ..., f[na-1]  and  B[] := f[na], f[na+1], ..., f[na+nb-1]
// into  t[] := t[0], t[1], ..., t[na+nb-1]  such that t[] is sorted.
// Must have: na >= 1 and nb >= 1
{
    const Type * const A = f;
    const Type * const B = f + na;
    ulong nt = na + nb;
    Type ta = A[--na],  tb = B[--nb];

    while ( true )
    {
        if ( ta > tb )  // copy ta
        {
            t[--nt] = ta;
            if ( na==0 )  // A[] empty?
            {
                for (ulong j=0; j<=nb; ++j)  t[j] = B[j];  // copy rest of B[]
                return;
            }

            ta = A[--na];  // read next element of A[]
        }
        else  // copy tb
        {
            t[--nt] = tb;
            if ( nb==0 )  // B[] empty?
            {
                for (ulong j=0; j<=na; ++j)  t[j] = A[j];  // copy rest of A[]
                return;
            }

            tb = B[--nb];  // read next element of B[]
        }
    }
}
// -------------------------


template <typename Type>
void merge_sort_rec(Type *f, ulong n, Type *t)
{
    if ( n<8 )
    {
        selection_sort(f, n);
        return;
    }

    const ulong na = n>>1;
    const ulong nb = n - na;

    merge_sort_rec(f, na, t);
    merge_sort_rec(f+na, nb, t);

    merge(f, na, nb, t);
    for (ulong j=0; j<n; ++j)  f[j] = t[j];   // copy back
}
// -------------------------

template <typename Type>
void merge_sort(Type *f, ulong n, Type *tmp=0)
{
    Type *t = tmp;
    if ( tmp==0 )  t = new Type[n];
    merge_sort_rec(f, n, t);
    if ( tmp==0 )  delete [] t;
}
// -------------------------


template <typename Type>
void merge_sort_rec4(Type *f, ulong n, Type *t)
{
    if ( n<8 )  // threshold must be at least 8
    {
        selection_sort(f, n);
        return;
    }

    // left and right half:
    const ulong na = n>>1;
    const ulong nb = n - na;

    // left quarters:
    const ulong na1 = na>>1;
    const ulong na2 = na - na1;
    merge_sort_rec4(f, na1, t);
    merge_sort_rec4(f+na1, na2, t);

    // right quarters:
    const ulong nb1 = nb>>1;
    const ulong nb2 = nb - nb1;
    merge_sort_rec4(f+na, nb1, t);
    merge_sort_rec4(f+na+nb1, nb2, t);

    // merge quarters (F-->T):
    merge(f, na1, na2, t);
    merge(f+na, nb1, nb2, t+na);

    // merge halves (T-->F):
    merge(t, na, nb, f);
}
// -------------------------


template <typename Type>
void merge_sort4(Type *f, ulong n, Type *tmp=0)
{
    Type *t = tmp;
    if ( tmp==0 )  t = new Type[n];
    merge_sort_rec4(f, n, t);
    if ( tmp==0 )  delete [] t;
}
// -------------------------




#endif  // !defined HAVE_MERGE_SORT_H__
