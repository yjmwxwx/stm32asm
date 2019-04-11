#if !defined HAVE_SWAPBLOCKS_H__
#define      HAVE_SWAPBLOCKS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "perm/reverse.h"

#include "aux0/swap.h"


template <typename Type>
void swap_blocks(Type *f, ulong x1, ulong n1, ulong x2, ulong n2)
// Swap the blocks starting at indices x1 and x2,
// n1 and n2 are the block lengths.
{
    if ( x1>x2 ) { swap2(x1, x2); swap2(n1, n2); }
    f += x1;
    x2 -= x1;
    ulong n = x2 + n2;
    reverse(f, n1);
    reverse(f+n1, n-n1-n2);
    reverse(f+x2, n2);
    reverse(f, n);
}
// -------------------------


template <typename Type>
void inverse_swap_blocks(Type *f, ulong x1, ulong n1, ulong x2, ulong n2)
// Inverse of swap_blocks(f, x1, n1, x2, n2).
// Same effect as  swap_blocks(f, x1, n2, x2+n2-n1, n1).
{
    if ( x1>x2 ) { swap2(x1, x2); swap2(n1, n2); }
    f += x1;
    x2 -= x1;
    ulong n = x2 + n2;
    reverse(f, n);
    reverse(f+x2, n2);
    reverse(f+n1, n-n1-n2);
    reverse(f, n1);
}
// -------------------------

#endif  // !defined HAVE_SWAPBLOCKS_H__
