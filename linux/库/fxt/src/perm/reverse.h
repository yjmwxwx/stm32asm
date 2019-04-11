#if !defined HAVE_REVERSE_H__
#define      HAVE_REVERSE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "fxttypes.h"


template <typename Type>
inline void reverse(Type *f, ulong n)
// Reverse order of array f.
{
    if ( n>=2 )
    {
        for (ulong k=0, i=n-1;  k<i;  ++k, --i)
            swap2(f[k], f[i]);
    }
}
// -------------------------


template <typename Type>
inline void reverse_0(Type *f, ulong n)
// Reverse array around index zero.
{
    if ( n>2 )  reverse(f+1, n-1);
}
// -------------------------



#endif  // !defined HAVE_REVERSE_H__
