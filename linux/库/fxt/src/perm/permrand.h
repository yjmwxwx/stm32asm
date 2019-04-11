#if !defined  HAVE_PERMRAND_H__
#define       HAVE_PERMRAND_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "aux0/rand-idx.h"
#include "fxttypes.h"


template <typename Type>
void random_permute(Type *f, ulong n)
// Randomly permute the elements of f[].
{
#if 1
    for (ulong k=n; k>1; --k)
    {
        const ulong i = rand_idx(k);
        swap2(f[k-1], f[i]);
    }

#else

    for (ulong k=1; k<n; ++k)
    {
        const ulong i = rand_idx(k+1);
        swap2(f[k], f[i]);
    }
#endif
}
// -------------------------

inline void random_permutation(ulong *f, ulong n)
// Create a random permutation.
{
    for (ulong k=0; k<n; ++k)  f[k] = k;
    random_permute(f, n);
}
// -------------------------


template <typename Type>
void random_permute_positions(Type *f, ulong np, const ulong *ps)
// Randomly permute the np elements f[ps[0]], f[ps[1], ..., f[ps[np-1]].
{
    for (ulong k=1; k<np; ++k)
    {
        const ulong i = rand_idx(k+1);
        swap2(f[ps[k]], f[ps[i]]);
    }
}
// -------------------------



#endif  // !defined HAVE_PERMRAND_H__
