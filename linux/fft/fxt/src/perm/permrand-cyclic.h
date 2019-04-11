#if !defined  HAVE_PERMRAND_CYCLIC_H__
#define       HAVE_PERMRAND_CYCLIC_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "aux0/rand-idx.h"
#include "fxttypes.h"


template <typename Type>
void random_permute_cyclic(Type *f, ulong n)
// Permute the elements of f by a random cyclic permutation.
{
#if 0
// Algorithm by S.Sattolo:
//   swap last with rand(first, ..., last-1)
//   swap second last with rand(first, ..., second last -1)
//     ...
//   swap second with first
    for (ulong k=n-1; k>0; --k)
    {
        const ulong i = rand_idx(k);
        swap2(f[k], f[i]);
    }
#else

    for (ulong k=1; k<n; ++k)
    {
        const ulong i = rand_idx(k);
        swap2(f[k], f[i]);
    }
#endif
}
// -------------------------

inline void random_cyclic_permutation(ulong *f, ulong n)
// Create a random permutation that is cyclic.
{
    for (ulong k=0; k<n; ++k)  f[k] = k;
    random_permute_cyclic(f, n);
}
// -------------------------


template <typename Type>
void random_permute_positions_cyclic(Type *f, ulong np, const ulong *ps)
// Randomly permute the np elements f[ps[0]], f[ps[1], ..., f[ps[np-1]]
// by a cyclic permutation.
{
    for (ulong k=1; k<np; ++k)
    {
        const ulong i = rand_idx(k);
        swap2(f[ps[k]], f[ps[i]]);
    }
}
// -------------------------


#endif  // !defined HAVE_PERMRAND_CYCLIC_H__
