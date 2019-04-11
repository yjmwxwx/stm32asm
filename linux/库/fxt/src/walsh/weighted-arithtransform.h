#if !defined  HAVE_WEIGHTED_ARITHTRANSFORM_H__
#define       HAVE_WEIGHTED_ARITHTRANSFORM_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "walsh/arithtransform.h"
#include "walsh/bitcount-weight.h"

#include "fxttypes.h"


template <typename Type>
void arith_transform_plus(Type *f, ulong ldn, Type w)
// Weighted arithmetic transform (positive sign).
{
    if ( w!=(Type)1 )  bit_count_weight(f, ldn, w);
    arith_transform_plus(f, ldn);
}
// -------------------------

template <typename Type>
void arith_transform_minus(Type *f, ulong ldn, Type w)
// Weighted arithmetic transform (negative sign).
// Inverse of (weighted) arith_transform_plus().
{
    arith_transform_minus(f, ldn);
    if ( w!=(Type)1 )  bit_count_weight(f, ldn, 1.0/w);
}
// -------------------------


template <typename Type>
void rev_arith_transform_plus(Type *f, ulong ldn, Type w)
// Weighted reversed arithmetic transform (positive sign).
{
    if ( w!=(Type)1 )  rev_bit_count_weight(f, ldn, w);
    rev_arith_transform_plus(f, ldn);
}
// -------------------------

template <typename Type>
void rev_arith_transform_minus(Type *f, ulong ldn, Type w)
// Weighted reversed arithmetic transform (negative sign).
// Inverse of (weighted) rev_arith_transform_plus().
{
    rev_arith_transform_minus(f, ldn);
    if ( w!=(Type)1 )  rev_bit_count_weight(f, ldn, 1.0/w);
}
// -------------------------


#endif  // !defined HAVE_WEIGHTED_ARITHTRANSFORM_H__
