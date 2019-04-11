#if !defined HAVE_SCANBOX_H__
#define      HAVE_SCANBOX_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "aux1/arith1.h"  // sum()


template <typename Type>
ulong first_geq_sumbox_idx(const Type *f, ulong n, Type v, ulong boxlen)
// Find first box of length boxlen for which sum of the elements is >=v.
// Return index of first element of that box.
// Return n if no such box is found.
{
    if ( 1==boxlen )  return first_geq_idx(f,n,v);

    if ( boxlen>=n )
    {
        if ( sum(f,n)>=v )  return 0;
        else                    return n;
    }

    ulong i;
    double bv = 0;
    for (i=0; i<boxlen; ++i)  bv += f[i];
    if ( bv>=v )  return i;

    for (  ; i<=n-boxlen; ++i)
    {
        bv = bv - f[i-1] + f[i+boxlen-1];  // value of box[i]
        if ( bv>=v )  return i;
    }

    return n;
}
// -------------------------


template <typename Type>
ulong last_geq_sumbox_idx(const Type *f, ulong n, Type v, ulong boxlen)
// Find last box of length boxlen for which sum of the elements is >=v.
// Return index of first element of that box.
// Return n if no such box is found.
// Add boxlen-1 to the result to get end of the box.
{
    if ( boxlen==1 )  return last_geq_idx(f,n,v);

    if ( boxlen>=n )
    {
        if ( sum(f,n)>=v )  return 0;
        else                    return n;
    }

    ulong i;
    double bv = 0;
    for (i=n-1; i>=n-boxlen; --i)  bv += f[i];
    if ( bv>=v )  return i;

    do
    {
        bv = bv + f[i] - f[i+boxlen];  // value of box[i]
        if ( bv>=v )  return i;
        --i;
    }
    while ( i );

    return n;
}
// -------------------------


template <typename Type>
ulong first_leq_sumbox_idx(const Type *f, ulong n, Type v, ulong boxlen)
// Find first box of length boxlen for which sum of the elements is <=v.
// Return index of first element of that box.
// Return n if no such box is found.
{
    if ( boxlen==1 )  return first_leq_idx(f,n,v);

    if ( boxlen>=n )
    {
        if ( sum(f,n)<=v )  return 0;
        else                    return n;
    }

    ulong i;
    double bv = 0;
    for (i=0; i<boxlen; ++i)  bv += f[i];
    if ( bv<=v )  return i;

    for (  ; i<=n-boxlen; ++i)
    {
        bv = bv - f[i-1] + f[i+boxlen-1];  // value of box[i]
        if ( bv<=v )  return i;
    }

    return n;
}
// -------------------------

template <typename Type>
ulong last_leq_sumbox_idx(const Type *f, ulong n, Type v, ulong boxlen)
// Find last box of length boxlen for which sum of the elements is <=v.
// Return index of first element of that box.
// Return n if no such box is found.
// Add boxlen-1 to the result to get end of the box.
{
    if ( boxlen==1 )  return last_geq_idx(f,n,v);

    if ( boxlen>=n )
    {
        if ( sum(f,n)<=v )  return 0;
        else                    return n;
    }

    ulong i;
    double bv = 0;
    for (i=n-1; i>=n-boxlen; --i)  bv += f[i];
    if ( bv<=v )  return i;

    do
    {
        bv = bv + f[i] - f[i+boxlen];  // value of box[i]
        if ( bv<=v )  return i;
        --i;
    }
    while ( i );

    return n;
}
// -------------------------


#endif // !defined HAVE_SCANBOX_H__
