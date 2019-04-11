#if !defined  HAVE_MSET_PERM_INVTAB_H__
#define       HAVE_MSET_PERM_INVTAB_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

template <typename Type>
void mset_perm_to_rinvtab(const Type *ms, ulong n, ulong *t)
// Compute (right) inversion table of multiset permutation ms[]:
// t[k] := number of elements ms[j] right of position k
// (i.e. j>k) and less than ms[k].
// Must have: n>=1.
{
    for (ulong k=0; k<n-1; ++k)
    {
        ulong ni = 0;  // number of (right) inversions
        const Type msk = ms[k];
        for (ulong j=k+1; j<n; ++j)  ni += ( ms[j] < msk );
        t[k] = ni;
    }
}
// -------------------------

template <typename Type>
void mset_perm_to_linvtab(const Type *ms, ulong n, ulong *t)
// Compute (left) inversion table of multiset permutation ms[]:
// t[k-1] := number of elements ms[j] left of position k
// (i.e. j<k) and greater than ms[k].
// Must have: n>=1.
{
    for (ulong k=n-1; k!=0; --k)
    {
        ulong ni = 0;  // number of (left) inversions
        const Type msk = ms[k];
        for (ulong j=0; j<k; ++j)  ni += ( ms[j] > msk );
        t[k-1] = ni;
    }
}
// -------------------------


#endif  // !defined HAVE_MSET_PERM_INVTAB_H__
