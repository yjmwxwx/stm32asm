#if !defined HAVE_MINMAX2D_H__
#define      HAVE_MINMAX2D_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "sort/minmax.h"


template <typename Type>
Type min(const Type **f, ulong nr, ulong nc)
// find min and max
{
    Type i = min(f[0], nc);
    for (ulong r=1; r<nr; ++r)
    {
        Type t = min(f[r], nc);
        if ( t<i )  i = t;
    }
    return  i;
}
// -------------------------

template <typename Type>
Type max(const Type **f, ulong nr, ulong nc)
// find min and max
{
    Type a = max(f[0], nc);
    for (ulong r=1; r<nr; ++r)
    {
        Type t = max(f[r], nc);
        if ( t>a )  a = t;
    }
    return  a;
}
// -------------------------


template <typename Type>
void min_max(const Type **f, ulong nr, ulong nc, Type *mi, Type *ma)
// find min and max
{
    Type i, a;
    min_max(f[0], nc, &i, &a);
    for (ulong r=1; r<nr; ++r)  update_min_max(f[r], nc, &i, &a);
    *mi = i;
    *ma = a;
}
// -------------------------


#endif // !defined HAVE_MINMAX2D_H__
