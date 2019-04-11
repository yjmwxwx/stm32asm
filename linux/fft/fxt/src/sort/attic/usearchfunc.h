#if !defined  HAVE_USEARCHFUNC_H__
#define       HAVE_USEARCHFUNC_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template <typename Type>
inline ulong first_idx(const Type *f, ulong n, bool (* func)(Type))
// Return index of first element for which func() returns true.
// Return n if there is no such element.
{
    ulong k = 0;
    while ( (k<n) && (!func(f[k])) )  k++;
    return k;
}
// -------------------------

template <typename Type>
inline ulong next_idx(const Type *f, ulong n, bool (* func)(Type), ulong k0)
// Like first_idx() but start from k0.
{
    ulong k = k0;
    while ( (k<n) && (!func(f[k])) )  k++;
    return k;
}
// -------------------------


template <typename Type>
inline ulong last_idx(const Type *f, ulong n, bool (* func)(Type))
// Return index of last element for which func() returns true.
// Return n if there is no such element.
{
    ulong k = n-1;
    while ( ! func(f[k]) )
    {
        k--;
        if ( 0==k )  return n;
    }
    return k;
}
// -------------------------

template <typename Type>
inline ulong previous_idx(const Type *f, ulong n, bool (* func)(Type), ulong k0)
// Like last_idx() but start from k0.
// Initial call with n-1, _not_ n !
{
    ulong k = k0;
    while ( ! func(f[k]) )
    {
        k--;
        if ( 0==k )  return n;
    }
    return k;
}
// -------------------------


#endif  // !defined HAVE_USEARCHFUNC_H__
