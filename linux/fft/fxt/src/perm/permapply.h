#if !defined HAVE_PERMAPPLY_H__
#define      HAVE_PERMAPPLY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "ds/bitarray.h"
#include "restrict.h"



template <typename Type>
void apply_permutation(const ulong *x, const Type *f, Type * restrict g, ulong n)
// Apply the permutation x[] to the array f[],
// i.e. set g[x[k]] <-- f[k]  for all k
{
    for (ulong k=0; k<n; ++k)  g[x[k]] = f[k];
}
// -------------------------


template <typename Type>
void apply_permutation(const ulong *x, Type * restrict f, ulong n, bitarray *bp=0)
// Apply the permutation x[] to the array f[]
// i.e. set f[x[k]] <-- f[k]  for all k
// In-place version.
{
    bitarray *tp = bp;
    if ( 0==bp )  tp = new bitarray(n);  // tags
    tp->clear_all();

    for (ulong k=0; k<n; ++k)
    {
        if ( tp->test_clear(k) )  continue;  // already processed
        tp->set(k);

        // --- do cycle: ---
        ulong i = k;  // start of cycle
        Type t = f[i];
        ulong g = x[i];
        while ( 0==(tp->test_set(g)) )  // cf. gray_permute()
        {
            Type tt = f[g];
            f[g] = t;
            t = tt;
            g = x[g];
        }
        f[g] = t;
        // --- end (do cycle) ---
    }

    if ( 0==bp )  delete tp;
}
// -------------------------


template <typename Type>
void apply_inverse_permutation(const ulong *x, const Type *f, Type * restrict g, ulong n)
// Apply the inverse permutation of x[] to the array f[]
// i.e. set g[k] <-- f[x[k]]  for all k
//
// E.g. after
// idx_quick_sort(f, n, x);  apply(x, f, g, n);
//  g[] == sorted( f[] )
//.
// If  f[] is a permutation, then after sort_idx()
// x[] is its inverse and
// idx_quick_sort(f, n, x);  apply_inverse_permutation(f, x, g, n);
// (note that x, f are swapped in apply_inverse_permutation())
//  will make x[] == sorted( f[] )
// ... i.e.  x * f == f * x
//
{
    for (ulong k=0; k<n; ++k)  g[k] = f[x[k]];
}
// -------------------------


template <typename Type>
void apply_inverse_permutation(const ulong *x, Type * restrict f, ulong n, bitarray *bp=0)
// Apply the inverse permutation of x[] to the array f[]
// i.e. set f[k] <-- f[x[k]]  for all k
// In-place version.
{
    bitarray *tp = bp;
    if ( 0==bp )  tp = new bitarray(n);  // tags
    tp->clear_all();

    for (ulong k=0; k<n; ++k)
    {
        if ( tp->test_clear(k) )  continue;  // already processed
        tp->set(k);

        // --- do cycle: ---
        ulong i = k;  // start of cycle
        Type t = f[i];
        ulong g = x[i];
        while ( 0==(tp->test_set(g)) )  // cf. inverse_gray_permute()
        {
            f[i] = f[g];
            i = g;
            g = x[i];
        }
        f[i] = t;
        // --- end (do cycle) ---
    }

    if ( 0==bp )  delete tp;
}
// -------------------------




#endif  // !defined HAVE_PERMAPPLY_H__
