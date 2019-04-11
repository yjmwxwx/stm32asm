#if !defined HAVE_COPY2D_H__
#define      HAVE_COPY2D_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "aux1/copy.h"
#include "sort/minmaxmed23.h"


template <typename Type>
void null(Type **f, ulong nr, ulong nc)
// set values to zero
{
    while ( nr-- )  null(f[nr], nc);
}
// -------------------------


template <typename Type>
void fill(Type **f, ulong nr, ulong nc, Type v)
// set values to v
{
    while ( nr-- )  fill(f[nr], nc, v);
}
// -------------------------

template <typename Type1, typename Type2>
void copy(const Type1 *const*src, Type2 **dst, ulong nr, ulong nc)
{
    while ( nr-- )  acopy(src[nr], dst[nr], nc);
}
// -------------------------


template <typename Type1, typename Type2>
void offset_copy(const Type1 *const*src, ulong nrs, ulong ncs,
                 Type2 **dst, ulong nrd, ulong ncd,
                 ulong coff=0,
                 ulong roff=0)
//
// Copy (as much data as possible)
// src[r+roff][c+coff] --> dst[r][c]
//
{
    if ( roff>=nrs )  return;
    if ( coff>=ncs )  return;

    ulong clen = min2(ncs-coff, ncd);  // > 0
    ulong rlen = min2(nrs-roff, nrd);  // > 0
    for (ulong r=0;  r<rlen;  ++r)
    {
        copy_cast(src[r+roff]+coff, dst[r], clen);
    }
}
// -------------------------



#endif  // !defined HAVE_COPY2D_H__
