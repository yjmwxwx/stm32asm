#if !defined  HAVE_FACT2PERM_SWP_APPLY_H__
#define       HAVE_FACT2PERM_SWP_APPLY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "fxttypes.h"


template <typename Type>
void ffact2perm_swp_apply(const ulong *fc, ulong n, Type *x)
// Permute x by permutation corresponding to ffact2perm_swp().
{
    for (ulong k=0; k<n-1; ++k)
    {
        ulong i = fc[k];
        swap2( x[k], x[k+i] );
    }
}
// -------------------------


template <typename Type>
void ffact2invperm_swp_apply(const ulong *fc, ulong n, Type *x)
// Permute x by permutation corresponding to ffact2invperm_swp().
{
    if ( n<=1 )  return;
    ulong k = n-2;
    do
    {
        ulong i = fc[k];
        swap2( x[k], x[k+i] );
    }
    while ( k-- );
}
// -------------------------


template <typename Type>
void rfact2perm_swp_apply(const ulong *fc, ulong n, Type *x)
// Permute x by permutation corresponding to rfact2perm_swp().
{
    for (ulong k=0, j=n-2;  k<n-1;  ++k, --j)
    {
        ulong i = fc[k];
        swap2( x[j], x[j+i] );
    }
}
// -------------------------


template <typename Type>
void rfact2invperm_swp_apply(const ulong *fc, ulong n, Type *x)
// Permute x by permutation corresponding to rfact2invperm_swp().
{
    if ( n<=1 )  return;
    ulong k = n-2, j=0;
    do
    {
        ulong i = fc[k];
        swap2( x[j], x[j+i] );
        ++j;
    }
    while ( k-- );
}
// -------------------------


#endif  // !defined HAVE_FACT2PERM_SWP_APPLY_H__
